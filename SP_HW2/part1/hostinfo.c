#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <unistd.h>

#define SIZE 1024

int main(){
	struct utsname uts;
	char buf[SIZE];	
	long int hostid;
	if(uname(&uts) == -1){
		perror("hostinfo.c:main:uname");
		exit(1);
	}

	if((hostid = gethostid()) == -1){
		perror("hostinfo.c:main:sysinfo");
		exit(1);
	}
	
	printf("hostname: %s\n",uts.nodename);
	printf("%s %s\n",uts.sysname,uts.release);
	printf("hostid: %ld\n",hostid);
	return;
}
