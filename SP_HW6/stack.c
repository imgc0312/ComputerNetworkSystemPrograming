#include "my.h"

int main(){
	int i;
	char get;
	char buffer[SIZE];
	sprintf(process,"%sunfork:\t%s",BLUE,BASE);
	srand(time(NULL));

	if ((shm_id = shmget(key, STACK_SIZE, IPC_CREAT | IPC_EXCL | 0666)) < 0) {
		//get shm memory
		DIE("shmget");
	}
	atexit(exit1);


	if ((sem_id = semget(IPC_PRIVATE , 1, IPC_CREAT | 0600)) == -1){//make semphore
		DIE("semget");
	}
	if(semctl(sem_id, 0, SETVAL, semArg)){
		DIE("semctl");
	}	
	atexit(exit2);
	PRINT("create semphore success");

	if((shm_addr = (char*)shmat(shm_id, NULL, 0)) == (void*)-1){	//attach
		DIE("shmat");
	}
	PRINT("create shmat success");


	switch(pid = fork()){
		case -1:	//error
			DIE("fork");
			break;

		case 0:		//child
			sprintf(process, "%schild:\t%s",YELLO,BASE);
			sprintf(buffer, "abcderfghijk");
			//PRINT("c");
			break;
		default:	//parent	
			sprintf(process, "%sparent:\t%s",GREEN,BASE);
			sprintf(buffer, "ABCDEFGHIJK");
			//PRINT("p");
	}
	
	for(i = 0; i < 10; i++){
		if(rand()%2){
			push(buffer[i]);
		}
		else{
			pop();
		}
		SLEEP((double) (rand() % 3));
	}
	if(shmdt(shm_addr) == -1){	//detech
		DIE("shmdt");
	}
	waitpid(pid,NULL,0);
	return 0;
}

void exit1(){	//when exit remove shm
	if(shmctl(shm_id, IPC_RMID, NULL) == -1){//remove shm memory
		DIE("shmctl");
	}
}

void exit2(){	//when exit remove sem
	if(semctl(sem_id, 0, IPC_RMID, NULL)){
		DIE("semid");
	}
}

bool push(char x){
	char output[SIZE] ;

	if(semop(sem_id,&semCtr[0],1)){//wait for unlock , then lock
		DIE("semop");
	}

	if(shm_addr[0] >= STACK_SIZE - 1){ //if stack is full 
		sprintf(output,"push '%c' failed, stack is full",x);
		PRINT(output);

		if(semop(sem_id,&semCtr[1],1)){	//unlock
			DIE("semop");
		}
		return false;	
	}

	shm_addr[0] += 1;//stack high +1;
	shm_addr[shm_addr[0]] = x;//top of stack = input

	sprintf(output,"push '%c' success, stack high is %d now", x, shm_addr[0]);
	PRINT(output);

	if(semop(sem_id,&semCtr[1],1)){//unlock
		DIE("semop");
	}
	return true;
}

char pop(){
	char output[SIZE] ;
	char get;


	if(semop(sem_id,&semCtr[0],1)){//wait for unlock , then lock
		DIE("semop");
	}

	if(shm_addr[0] <= 0){ //if stack is empty
		sprintf(output,"pop failed, stack is empty");
		PRINT(output);

		if(semop(sem_id,&semCtr[1],1)){	//unlock
			DIE("semop");
		}	
		return NULL;	
	}

	get = shm_addr[shm_addr[0]];//get = top of stack
	shm_addr[0] -= 1;//stack high +1;

	sprintf(output,"pop '%c' , stack high is %d now", get, shm_addr[0]);
	PRINT(output);
	
	if(semop(sem_id,&semCtr[1],1)){//unlock
		DIE("semop");
	}
	return get;
}
