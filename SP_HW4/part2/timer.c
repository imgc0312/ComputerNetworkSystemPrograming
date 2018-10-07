/*
 *  timer.c : contains two timing functions to measure process time
 */

#include <sys/times.h>
#include <unistd.h>
#include <stdio.h>
#include "shell.h"

/* Storage for baseline times. */
static clock_t start_time;

/* Save a baseline of user and system CPU times, plus wallclock time. */
void set_timer(void) {
	struct tms tmbuf;
	/* Fill in code. */

	if((start_time = times(&tmbuf)) == -1){
		perror("times");
		exit(1);
	}
	tms_o = tmbuf;
}


/* Get second set of times, and take delta to get wallclock time.  Display. */
void stop_timer(void) {
	struct tms tmbuf;
	clock_t end_time;
	double ticks;

	ticks = sysconf(_SC_CLK_TCK);

	/* Get delta times and print them out.
	 *
	 * Fill in code. */
	if((end_time = times(&tmbuf)) == -1){
		printf("end error\n");
		perror("times");
		exit(1);
	}
	printf("Sys: %f \t",(( tmbuf.tms_stime - tms_o.tms_stime ) / ticks ));
	printf("User: %f \t",(( tmbuf.tms_utime - tms_o.tms_utime ) / ticks ));
	printf("Real: %f \n",( end_time - start_time ) / ticks );
	
	
}

