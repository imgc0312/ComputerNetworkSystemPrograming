#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

int main( int argc, char* argv[] ) {
	
	struct stat buf;
    char * tar;
	char get;


	if (argc < 3){
		printf("too few Argument: ./mymv [file1] [file2/dir]\n");
		exit(1);
	}

	if(stat(argv[1],&buf) == -1){
		printf("%s is not existed\n",argv[1]);
		exit(1);
	}	

	stat(argv[2], &buf);

	if (! S_ISDIR(buf.st_mode)) {// rename
		  tar = strdup(argv[2]);
	}
	else{// move to dir
		tar = (char*)malloc((strlen(argv[2]) + strlen(argv[1]) + 1)*sizeof(char));
		strcpy(tar,argv[2]);
		strcat(tar,"/");
		strcat(tar,argv[1]);
		
	}
	
		
	
	if(link(argv[1],tar) == -1){
		printf("mymv: overwrite '%s'?",argv[1]);
		scanf("%c",&get);
		if((get == 'Y') || (get == 'y')){
			unlink(tar);
			if(link(argv[1],tar) == -1){
				perror("link");
				free(tar);
				exit(1);
			}
			unlink(argv[1]);
		}
	}
	else
		unlink(argv[1]);

	free(tar);
	return 0;
}
