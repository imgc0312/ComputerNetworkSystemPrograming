/*
 * parse.c : use whitespace to tokenise a line
 * Initialise a vector big enough
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "shell.h"

/* Parse a commandline string into an argv array. */
char ** parse(char *line) {

  	static char delim[] = " \t\n"; /* SPACE or TAB or NL */
  	int count = 0;
  	char * token;
  	char **newArgv;

  	/* Nothing entered. */
  	if (line == NULL || strcmp(line,"\n")==0) {
    	return NULL;
  	}

  	/* Init strtok with commandline, then get first token.
     * Return NULL if no tokens in line.
	 *
	 * Fill in code.
     */
	if((token = strtok(line,delim)) == NULL){
		return NULL;
	}

  	/* Create array with room for first token.
  	 *
	 * Fill in code.
	 */
	newArgv = (char**)malloc(2*sizeof(char*));
	newArgv[0] = strdup(token);

  	/* While there are more tokens...
	 *
	 *  - Get next token.
	 *	- Resize array.
	 *  - Give token its own memory, then install it.
	 * 
  	 * Fill in code.
	 */
	int i = 1;
	while((token = strtok(NULL,delim) )!= NULL){

		newArgv = (char ** )realloc(newArgv,(i+2)*sizeof(char*));
		newArgv[i] = strdup(token);
		i++;
	}

  	/* Null terminate the array and return it.
	 *
  	 * Fill in code.
	 */
	//newArgv = (char ** )realloc(newArgv,(i+2)*sizeof(char*));
	newArgv[i] = NULL;

  	return newArgv;
}


/*
 * Free memory associated with argv array passed in.
 * Argv array is assumed created with parse() above.
 */
void free_argv(char **oldArgv) {

	int i = 0;

	/* Free each string hanging off the array.
	 * Free the oldArgv array itself.
	 *
	 * Fill in code.
	 */
	for(i=0 ; oldArgv[i] != NULL ; i++){
		free(oldArgv[i]);
	}
	free(oldArgv[i]);
	free(oldArgv);
}
