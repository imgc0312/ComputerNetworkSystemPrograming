#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 1024

int main(){
	char* buf;
	buf = getcwd((char*)NULL,SIZE);
	if(buf == 0){
		perror("printdir.c: getcwd().\n");
		exit(1);
	}
	printf("%s\n",buf);
	return 0;
}
