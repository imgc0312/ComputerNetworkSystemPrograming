
#include <sys/shm.h>

#include <stdio.h>

#include <errno.h>

#include <string.h>

#include <stdlib.h>

#include <unistd.h>

#include <sys/types.h>

#include <sys/wait.h>

#include <stdbool.h>

#include <sys/sem.h>

#define SIZE 1024

#define STACK_SIZE 3 /* Define a small stack size to cause contention. */

//void push(char oneChar);
//char pop();


#define BASE "\e[0m"
#define GREEN "\e[0;32m"
#define YELLO "\e[0;33m"
#define BLUE "\e[0;34m"

#define DIE(x) perror(x),exit(0)
#define PRINT(x) printf("%s%s\n", process, x)
#define SLEEP(x) sleep(1 + (double)rand() / RAND_MAX * x)

pid_t pid;
int shm_id;
const key_t key = 0x43040044;
char process[SIZE] ;
char *shm_addr;
static int sem_id;//semephore

union sem {
	int val;
	struct semid_ds* buf;
	unsigned short* array;
	struct seminfo* __buf;
} semArg={1};

struct sembuf semCtr[2]={
		{0,-1,0},			//lock
		{0,1,IPC_NOWAIT}	//unlock
}; 

void exit1();	//when exit remove shm
void exit2();	//when exit remove sem
bool push(char);
char pop();

