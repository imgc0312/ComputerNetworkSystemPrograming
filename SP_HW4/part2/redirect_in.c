/*
 * redirect_in.c  :  check for <
 */

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "shell.h"
#define STD_OUTPUT 1
#define STD_INPUT  0

/*
 * Look for "<" in myArgv, then redirect input to the file.
 * Returns 0 on success, sets errno and returns -1 on error.
 */
int redirect_in(char ** myArgv) {
  	int i = 0;
  	int fd;

  	/* search forward for <
  	 *
	 * Fill in code. */
	for (i = 0; myArgv[i] != NULL;i++){
		if(strcmp(myArgv[i],"<") == 0){
			break;
		}
	}

  	if (myArgv[i]) {	/* found "<" in vector. */

    	/* 1) Open file.
     	 * 2) Redirect stdin to use file for input.
   		 * 3) Cleanup / close unneeded file descriptors.
   		 * 4) Remove the "<" and the filename from myArgv.
		 *
   		 * Fill in code. */
		fd = open(myArgv[i+1],O_RDONLY);
		if(fd <= 0){
			perror("redirect_in.c: open().\n");
			return -1;
		}

		close(STD_INPUT);
		if(dup(fd) != STD_INPUT){
			perror("redirect_in.c: dup failed to return STD_INPUT.\n");
			return -1;
		}
		close(fd);
		
		free(myArgv[i]);
		free(myArgv[i+1]);
		for(;myArgv[i+2]!=NULL;i++){
			myArgv[i]=myArgv[i+2];
			//free(myArgv[i+2]);
		}
		myArgv[i]=NULL;
  	}
  	return 0;
}
