/*
 *  pipe_present.c :  check for |
 */

#include <stdio.h>
#include "shell.h"

/*
 * Return index offset into argv of where "|" is,
 * -1 if in an illegal position (first or last index in the array),
 * or 0 if not present.
 */
int pipe_present(char ** myCurrentArgv) {
	int index = -1;

  	/* Search through myCurrentArgv for a match on "|". */
	int i;
	for (i = 0; myCurrentArgv[i] != NULL;i++){
		if(strcmp(myCurrentArgv[i],"|") == 0){
			index = i;
			for (;myCurrentArgv[i] != NULL;i++)
				;
			break;
		}
	}

  	if ((index == 0) || (index == (i-1) ))/* At the beginning or at the end. */ {
		return -1;

  	} else if (index == -1)/* Off the end. */ {
    	return 0;

    } else {
    	/* In the middle. */
    	return index;
  	}
}
