#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define SIZE 1024

int main(int argc,char** argv){
	int fd,n;	
	char buf[SIZE] = "";
	if (argc != 2){
		perror("Usage: mycat filename\n");
		exit(1);	
	}

	fd = open(argv[1],O_RDONLY);
	if (fd == -1){
		perror("mycat.c: open().\n");
		exit(1);	
	}

	while( (n = read(fd,buf,SIZE)) > 0){
		printf("%s",buf);
	}
	if(n == -1){
		perror("mycat.c: read().\n");
		exit(1);
	}
	close(fd);
	

	return 0;
}
