#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>  /* For general. */
#include <sys/ipc.h> /* System 5 IPC defs. */
#include <sys/sem.h> /* System 5 IPC semaphore defs.*/
#include <pthread.h>/* Posix threads. */
#include <stdlib.h>/* Needed for delay to work properly. */

#include <unistd.h>
#include <stdbool.h>

#define NUM_THREADS 10 /* Number of simultaneous requests. */
#define TIME_BTWN_NEW_THREADS 0.5 /* Time between intro of new request. */
#define RUNTIME_RANGE 5.0 /* Time of longest job. */

#define NUM_SEMS_IN_GROUP 3 // means one vm has 3 parts
#define CPU_SEM 0
#define RAM_SEM 1
#define DISK_SEM 2
/* These are used to initialize semaphores with total resources managed. */
#define NUM_CPU 8
#define NUM_RAM 16
#define AMT_DISK 500

#define WAIT 0
#define STRING_SIZE 80

/* Flags passed thru sembuf structure; wait for resource. */

#define FALSE 0
#define TRUE (!FALSE)

int semid;/* IPC semaphore identifier (semaphore accessed through this).*/

extern int errno;

/* define all my VM */
struct vm{	int numCPU; 
			int numRAM; 
			int amtDISK;
} vmTable[]={
	{ 6, 5, 125},
	{ 2, 2, 500},
	{ 4, 5, 300},
	{ 2, 8, 125},
	{ 2, 8, 300}
};

/* Number of vm in the table. */
int numVM = sizeof(vmTable) / sizeof(struct vm);

/*union for semtcl()*/
union sem {
	int val;
	struct semid_ds* buf;
	unsigned short* array;
	struct seminfo* __buf;
} semArg[] = {
	{NUM_CPU},
	{NUM_RAM},
	{AMT_DISK}
};


#define DIE(x) perror(x),exit(errno)
#define CLEAR(x) perror(x),cleanup()
#define PRINT(x) printf("%s\n",x)

void *threadMain(void *);
void cleanup();
int reserve(int semid, struct vm thisVM);
int release(int semid, struct vm thisVM);
int playWithSemaphores(int semid, int numCPU, int numRAM,int amtDISK);

//double st;
#define BASE "\e[0m"
#define YELLO "\e[0;33m"
#define GREEN "\e[0;32m"


