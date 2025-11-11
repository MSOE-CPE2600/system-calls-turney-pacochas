/*
* Filename: info.c
* Author: Sebastian Pacocha 
* Section: CPE 2600 - 112
* Date: 10/30/2025
* Description: Finds the current time of day in nanoseconds, the system's network name
*              The OS name, OS release and version, system's hardware type, number of CPUs,
*              total amount of physical memory in bytes, and amount of free memory in bytes.
* Compilation: gcc -o info info.c
* Usage: ./info
*/

#define _POSIX_C_SOURCE 199309L
#define GNU_SOURCE

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>
#include <sys/utsname.h>   
#include <sys/sysinfo.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
    // current time in nanoseconds
    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts) == 0) {
        long long nanoseconds = (long long)ts.tv_sec * 1000000000LL + ts.tv_nsec;
        printf("Current time (ns): %lld\n", nanoseconds);
    }
    // system info
    struct utsname uname_info;
    if (uname(&uname_info) == 0) {
        printf("Network name: %s\n", uname_info.nodename);
        printf("OS name: %s\n", uname_info.sysname);
        printf("OS release: %s\n", uname_info.release);
        printf("OS version: %s\n", uname_info.version);
        printf("Hardware type: %s\n", uname_info.machine);
    }
    // find total number of cores
    long num_cpu = sysconf(_SC_NPROCESSORS_ONLN);
    if (num_cpu != -1) {
        printf("Number of CPUs: %ld\n", num_cpu);
    }
    // find total memory and free memory
    struct sysinfo meminfo;
    if (sysinfo(&meminfo) == 0) {
        unsigned long long total_mem = meminfo.totalram;
        unsigned long long free_mem  = meminfo.freeram;

        // Multiply by mem_unit if provided
        if (meminfo.mem_unit != 0) {
            total_mem *= meminfo.mem_unit;
            free_mem  *= meminfo.mem_unit;
            printf("Total physical memory (bytes): %llu\n", total_mem);
            printf("Free memory (bytes): %llu\n", free_mem);
        }
        
    return 0;
    }
}