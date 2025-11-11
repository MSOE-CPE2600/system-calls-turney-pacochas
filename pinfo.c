/*
* Filename: info.c
* Author: Sebastian Pacocha 
* Section: CPE 2600 - 112
* Date: 10/30/2025
* Description: use getpid, getpriority, sched_getscheduler, getcpu
*              getrusage, getrlimit and print the information from 
*              a single command line parameter which is a process identifier
* Compilation: gcc -o pinfo pinfo.c
* Usage: ./pinfo
*/

// pinfo.c
#define _POSIX_C_SOURCE 199309L
#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>
int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Expected a process ID as an argument.\n");
        return 1;
    }
    pid_t pid = (pid_t)atoi(argv[1]);
    int policy = sched_getscheduler(pid); 
    if (policy != -1) {
        printf("Scheduling policy for PID %d is %d\n", pid, policy);
    } else {
        printf("Failed to get scheduling policy for PID %d\n", pid);
    }
    int priority = getpriority(PRIO_PROCESS, pid);
    if (priority != -1) {
        printf("Priority for PID %d is %d\n", pid, priority);
    } else {
        printf("Failed to get priority for PID %d\n", pid);
    }
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0) {
        printf("CPU usage time: %ld sec, %ld usec\n", usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
    }
    struct rlimit limit;
    if (getrlimit(RLIMIT_CPU, &limit) == 0) {
        printf("CPU time limit: %lu\n", limit.rlim_cur);
    }
    return 0;
}