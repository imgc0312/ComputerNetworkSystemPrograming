#include "main.h"
#include <errno.h>

int main(){

	/* Array of threads, one per request. */
	pthread_t threads[NUM_THREADS];	
	
	/* Needed to convert constant for semctl call.*/
	/*int numCPU = NUM_CPU;	
	int numRAM = NUM_RAM;
	int amtDISK = AMT_DISK;*/

	int count;
	
	/* Allocate a single semaphore group with three semaphores in it. */
	if ((semid = semget(IPC_PRIVATE , NUM_SEMS_IN_GROUP, IPC_CREAT | 0600)) == -1){
		DIE("semget");
	}	

	/* Initialize each semaphore in the group. Could also have used SETALL. */
	//semArg.val = numCPU;
	if(semctl(semid, CPU_SEM, SETVAL, semArg[ CPU_SEM ])){
		CLEAR("Error init semaphores numCPU");
	}
	//semArg.val = numRAM;
	if(semctl(semid, RAM_SEM, SETVAL, semArg[ RAM_SEM ])){
		CLEAR("Error init semaphores numRAM");
	}
	//semArg.val = amtDISK;
	if(semctl(semid, DISK_SEM, SETVAL, semArg[ DISK_SEM ])){
		CLEAR("Error init semaphores amtDISK");
	}

	/* Initialize random number generator used for time delays. */
	srand(time(NULL)); //set rand seed
	
	/* Spawn the threads. The argument passed to threadMain is a job table index, so multiple requests can be made using the same table entry when the index wraps. Delay to model jobs being staggered instead of coming all at once. */
	for (count = 0; count < NUM_THREADS; count++) {
		//printf("For %d \n",count % numVM);
		if (pthread_create(&threads[count], NULL, threadMain, (void *)(count % numVM)) ){
			CLEAR("Error starting reader threads");
		}
		sleep(TIME_BTWN_NEW_THREADS );
		
		
	}
	
	/* Wait for threads to finish. */
	for (count = 0; count < NUM_THREADS; count++) {
		pthread_join(threads[count], (void **)NULL);
	}
	
	return 0;
}


void cleanup(){
	/* Delete the semaphore. This is not done automatically by the system. */
	if(semctl(semid, 0, IPC_RMID, NULL)){
		perror("semctl IPC_RMID:");
		exit(1);
	}
}



/*
Here is where a thread starts executing. A thread in executing this function represents a task for the moving company, and requests the resources it needs.*/

void* threadMain(void* arg){
	/* The argument passed in is a table index. */
	int vmNum = (int)arg;

	/* Local string for message composition. */
	char str[STRING_SIZE];
	sprintf(str, "VM # %d requesting %d core, %d ram, %d disk", vmNum, vmTable[vmNum].numCPU, vmTable[vmNum].numRAM, vmTable[vmNum].amtDISK);
	PRINT(str);
	
	/*Get the resources needed. Wait for them if necessary. */
	if (reserve(semid, vmTable[vmNum]) ) {
		perror("reserve");
		return 0;
	}

	sprintf(str, "%sVM # %d get %d core, %d ram, %d disk%s", YELLO, vmNum, vmTable[vmNum].numCPU, vmTable[vmNum].numRAM, vmTable[vmNum].amtDISK, BASE);
	PRINT(str);

	/* Delay to simulate the time the resources are in use. */
	sleep( (RUNTIME_RANGE * rand()) / RAND_MAX );

	sprintf(str, "%sVM # %d done;\n returning %d core, %d ram, %d disk%s", GREEN, vmNum, vmTable[vmNum].numCPU, vmTable[vmNum].numRAM, vmTable[vmNum].amtDISK, BASE);
	PRINT(str);

	if ( release(semid, vmTable[vmNum]) ){
		perror ("release");
	}
	return 0;
}


/* Reserve resources required for a VM. */
int reserve(int semid, struct vm thisVM) {
	return (playWithSemaphores(semid, -1*thisVM.numCPU, -1*thisVM.numRAM, -1*thisVM.amtDISK));
}

/* Release resources of a VM. */
int release(int semid, struct vm thisVM){
	return (playWithSemaphores(semid, thisVM.numCPU, thisVM.numRAM, thisVM.amtDISK));
}

/* This is the workhorse function that allocates deallocates resources from the semaphore group. */
/* All semaphore operations are to be handled in the same way. */
int playWithSemaphores(int semid, int numCPU, int numRAM,int amtDISK) {

	/* There is one operation per semaphore for this example. This allocates an array of semaphore operations, all of which is carried out with a single atomic operation (system call to semop()).*/

	struct sembuf ops[NUM_SEMS_IN_GROUP];
	/* One operation per semaphore. Note that a negative value to ops[x].sem_op allocates a resource, while a positive value releases it. */

	ops[0].sem_num = CPU_SEM;
	ops[0].sem_op = numCPU;
	ops[1].sem_num = RAM_SEM;
	ops[1].sem_op = numRAM;
	ops[2].sem_num = DISK_SEM;
	ops[2].sem_op = amtDISK;

	/* All semaphore operations are to be handled in the same way. */
	ops[0].sem_flg = (ops[1].sem_flg = (ops[2].sem_flg = WAIT));
	
	/* "The call" that does the work. */
	return (semop(semid, ops, NUM_SEMS_IN_GROUP));
	
}


