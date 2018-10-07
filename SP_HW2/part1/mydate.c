#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SIZE 1024

int main(){
	const char month[12][4] = {"Dec","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov"};
	const char Date[7][4] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
	const char daylight[2][3] = {"AM","PM"};

	time_t t;
	struct tm *t_ptr;

	if((int)time(&t) == -1){
		perror("mydate.c:main:time()");
		exit(1);
	}
	
	t_ptr = localtime(&t);
	
	printf("%s %d(%s), %d %d:%d %s\n",month[t_ptr->tm_mon]
										,t_ptr->tm_mday
										,Date[t_ptr->tm_wday]
										,1900 + t_ptr->tm_year
										,t_ptr->tm_min
										,t_ptr->tm_sec
										,daylight[t_ptr->tm_isdst]
															);
	return 0;
}
