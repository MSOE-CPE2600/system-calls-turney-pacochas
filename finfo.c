/*
* Filename: finfo.c
* Author: Sebastian Pacocha 
* Section: CPE 2600 - 112
* Date: 10/31/2025
* Description: displays the file information about a given file
*              provided via the command line. The file name MUST be specified via the command line.
*              The owner of the file - printing the user identifier
*              (number) is enough - The size of the file IN BYTES - The date and time of last modification. 
*              - If at any point,
there is an error print an error and exit
* Compilation: gcc -o finfo finfo.c
* Usage: ./finfo
*/

// finfo.c
#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <string.h>
#include <errno.h>

void print_file_type(mode_t mode);
void print_permissions(mode_t mode);
int main(int argc, char* argv[]){
    if (argc != 2) {
        fprintf(stderr, "Error, missing file name\nUsage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *filename = argv[1];
    struct stat file_info;

    if (lstat(filename, &file_info) == -1) {
        fprintf(stderr, "Error: cannot access '%s' : %s\n", filename, strerror(errno));
    }

    print_file_type(file_info.st_mode);
    print_permissions(file_info.st_mode);

    printf("Owner UID: %u\n", file_info.st_uid);

    printf("File size: %lld bytes\n", (long long)file_info.st_size);

    char time_buffer[64];
    struct tm *timeinfo = localtime(&file_info.st_mtime);
    if (timeinfo == NULL) {
        perror("localtime");
        exit(EXIT_FAILURE);
    }
    if (strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", timeinfo) == 0) {
        fprintf(stderr, "Error formatting time\n");
        exit(EXIT_FAILURE);
    }

    printf("Last modified: %s\n", time_buffer);
    return 0;
}

void print_permissions(mode_t mode) {
    char perms[11];
     perms[0] = S_ISDIR(mode) ? 'd' :
               S_ISLNK(mode) ? 'l' : '-';
    perms[1] = (mode & S_IRUSR) ? 'r' : '-';
    perms[2] = (mode & S_IWUSR) ? 'w' : '-';
    perms[3] = (mode & S_IXUSR) ? 'x' : '-';
    perms[4] = (mode & S_IRGRP) ? 'r' : '-';
    perms[5] = (mode & S_IWGRP) ? 'w' : '-';
    perms[6] = (mode & S_IXGRP) ? 'x' : '-';
    perms[7] = (mode & S_IROTH) ? 'r' : '-';
    perms[8] = (mode & S_IWOTH) ? 'w' : '-';
    perms[9] = (mode & S_IXOTH) ? 'x' : '-';
    perms[10] = '\0';

    printf("Permissions: %s\n", perms);
}

void print_file_type(mode_t mode) {
    if (S_ISREG(mode)) {
        printf("File type: Regular file\n");
    } else if (S_ISDIR(mode)) {
        printf("File type: Directory\n");
    } else if (S_ISCHR(mode)) {
        printf("File type: Character device\n");
    } else if (S_ISBLK(mode)) {
        printf("File type: Block device\n");
    } else if (S_ISFIFO(mode)) {
        printf("File type: FIFO/pipe\n");
    } else if (S_ISLNK(mode)) {
        printf("File type: Symlink\n");
    } else if (S_ISSOCK(mode)) {
        printf("File type: Socket\n");
    } else {
        printf("File type: Unknown\n");
    }
}