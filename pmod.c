/*
* Filename: pmod.c
* Author: Sebastian Pacocha 
* Section: CPE 2600 - 112
* Date: 10/31/2025
* Description: Learn the usages of nice and nanosleep system calls.
* Compilation: gcc -o pmod pmod.c
* Usage: ./pmod
*/

// pmod.c
#define _POSIX_C_SOURCE 199309L
#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>
#include <time.h>
int main(int argc, char* argv[])
{
    int reduce_priority = nice(10);
    int priority = getpriority(PRIO_PROCESS, 0);
    if (priority != -1) {
        printf("Current process priority: %d\n", priority);
        printf("Reduced priority: %d\n", reduce_priority);
    } else {
        printf("Failed to get process priority\n");
    }
    printf("Sleeping for 1,837,272,638 nano seconds\n");
    struct timespec time_request;
    struct timespec time_remaining;
    time_request.tv_sec = 1; //1 sec
    time_request.tv_nsec = 837272638; //remaining nanoseconds
    nanosleep(&time_request, &time_remaining);
    printf("goodbye\n");
    return 0;
}