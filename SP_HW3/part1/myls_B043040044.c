#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

#define TRUE 1
#define FALSE 0
#define STR_SIZE 1024

void list_directory( char *dir_path );

int r;
int f;

int main( int argc, char* argv[] ) {
    
	struct stat buf;
    char * dir;
    int dir_i = 1;
    int flag;
    
    r=FALSE;
    f=FALSE;

    dir = getcwd((char* )NULL,STR_SIZE);
    if(dir == NULL){
        perror("getcwd");
        exit(1);
    }

    if(argc >1){
        if(argv[1][0] == '-'){
            
            dir_i = 2;
            
            while((flag = getopt(argc,argv,"FR")) != -1){
		        switch(flag){
		        	case 'F':
		        		f = 1;
		        		break;
		        	case 'R':
		        		r = 1;
        				break;
        		}	
        	}
        }   
        
        if (stat(argv[dir_i], &buf) == -1) {
             //perror("stat");
             //exit(1);
        }
        else if (! S_ISDIR(buf.st_mode)) {
            fprintf(stderr, "%s is not a directory.\n", argv[dir_i]);
            exit(1);  
        }
        else{
            strcat(dir,"/");
            strcat(dir,argv[dir_i]);
        }
    
    }
      
    list_directory(dir);
    
	return 0;
}

void list_directory( char *dir_path ) {
    //printf("\n%d: %d\n",r,f );
    DIR *dirp;
    struct stat buf;
    struct dirent *dent;
    char** dir =  (char**)malloc(sizeof(char*));
    int i=0;
    int j=0;
	char* str_t;
    char str[STR_SIZE];


    if ((dirp = opendir(dir_path)) == NULL) {
        perror("opendir");
        printf("%s\n",dir_path);
        exit(1);
    }

    printf("\n%s :\n",dir_path );

    while (dent = readdir(dirp)) {
        str_t = dent->d_name;
        if((strcmp(str_t,".") == 0) || (strcmp(str_t,"..") ==0)){
            continue;
        }
		
		strcpy(str,dir_path);
		strcat(str,"/");
		strcat(str,str_t);
	
		if (stat(str, &buf) == -1) {//dir open error
			perror("stat");
			printf("%s\n",str);
			exit(1);
		}

		if(S_ISDIR(buf.st_mode)){// is dir
			printf("%s%s\n",str_t, f?"/":"" );
			if (r){//if r == true
				i++;	
				dir = realloc(dir,sizeof(char*)*i);
				dir[i-1] = malloc((strlen(str))*sizeof(char));
				strcpy(dir[i-1],str);
			}	
			//printf("make:%s\n",dir[i-1]);			
		}
		else if(S_ISLNK(buf.st_mode) && f){// is link
			printf("%s@\n", str_t);
		}
		else if(S_ISSOCK(buf.st_mode) && f){// is socket
			printf("%s=\n", str_t);
		}
		else if(S_ISFIFO(buf.st_mode) && f){// is pipe
			printf("%s|\n", str_t);
		}
		else if ( buf.st_mode & S_IXUSR && f){// is excuate
			printf("%s*\n", str_t);
		}
		else{// default f == FALSE
			printf("%s\n", str_t);
		}

    }

    if(r){
        for(j=0;j<i;j++){
			chdir(dir[j]);
			list_directory(dir[j]);
			free(dir[j]);
			chdir(dir_path);
		}
    }

    free(dir);
	closedir(dirp);

}
