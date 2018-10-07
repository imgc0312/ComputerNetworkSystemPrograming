#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define SIZE 1024

int main(){
	int n;
	int fd[2];
	char buf[SIZE]="";
	if(pipe(fd) == -1){
		perror("pipe_ls.c: pipe().\n");
		exit(1);
	}

	switch(fork()){
		case -1://error
			perror("pipe_ls.c: fork().\n");
			exit(1);
			break;

		case 0://child
			close(1);
			dup(fd[1]);
			close(fd[0]);
			char* argv[] = {"ls","-al",".",0};
			execvp("ls",argv);
			break;
		default: //parent
			close(0);
			dup(fd[0]);
			close(fd[1]);
			while(n = read(fd[0],buf,SIZE) > 0){
				printf("%s",buf);
			}
			if(n == -1){
				perror("pipe_ls.c: read().\n");
				exit(1);
			}
	}
	return 0;
}
