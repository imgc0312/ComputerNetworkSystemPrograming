#include "my.h"

int main(int argc,char**argv){
	int i;	
	char temp[SIZE];
	packet pack;
	int num_block;
	sprintf(process,"%sproducer:\t%s",BLUE,BASE);
	
	if(argc < 2){
		PRINT("error: ./producer < size number > ");
		exit(0);	
	}
	else if (((num_block = atoi(argv[1])) < MIN_BLOCKS) || (atoi(argv[1]) > MAX_BLOCKS)){
		sprintf(temp, "error: size number need to be %d ~ %d", MIN_BLOCKS, MAX_BLOCKS);
		PRINT(temp);
		exit(0);
	}


	if((key = ftok("key",1)) == -1){
		DIE("ftok");
	}

	if ((shm_id = shmget(key, num_block * PACKET_SIZE , IPC_CREAT | IPC_EXCL | 0666)) < 0) {
		//get shm memory
		DIE("shmget");
	}
	atexit(exit1);

	if((shm_addr = (char*)shmat(shm_id, NULL, 0)) == (void*)-1){	//attach
		DIE("shmat");
	}

	sleep(15);//wait 15 sec

	for(i=0;i < MAX_PACKET;i++){
		setPacket(&pack,i);
		memcpy(shm_addr + (i % num_block) * PACKET_SIZE, &pack, PACKET_SIZE);
		//sent packet	
		usleep(1);
	}
	
	return 0;
}

void exit1(){	//when exit remove shm
	struct shmid_ds t;
	if(shmctl(shm_id, IPC_STAT,&t) == -1){
		DIE("shmctl");
	}
	
	if(t.shm_nattch == 1){
		PRINT("free");
		if(shmctl(shm_id, IPC_RMID, NULL) == -1){//remove shm memory
			DIE("shmctl");
		}
	}
}

void setPacket(packet *P,int id){
	int i;
	P->id = id;
	for(i=0;i<5;i++){
		P->dataShort[i] = (short)(rand() % (256));
		P->dataLong[i] =  (long)(rand() % (256));
		P->dataDouble[i] =  (double)(rand() % (256));
		P->dataByte[i] =  (char)(rand() % (256));
	}
	P->dataByte[5] = 1;//to mean its a packet
}
