#include "my.h"

int main(int argc,char**argv){
	int i;	
	char temp[SIZE];
	packet pack;
	int loss ;
	int num_block;
	sprintf(process,"%scumsumer:\t%s",GREEN,BASE);
	
	if(argc < 2){
		PRINT("error: ./consumer < size number > ");
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

	if ((shm_id = shmget(key, 0 , 0)) < 0) {
		//get shm memory
		DIE("shmget");
	}
	atexit(exit1);

	if((shm_addr = (char*)shmat(shm_id, NULL, SHM_RDONLY)) == (void*)-1){	//attach
		DIE("shmat");
	}

	i = 0;
	loss =0;
	while(1){
		memcpy(&pack, shm_addr, PACKET_SIZE);
		if(pack.dataByte[5] == 1){
			break;
		}
	}
	for(i=0;i < MAX_PACKET; ){
		memcpy(&pack, shm_addr + (i % num_block) * PACKET_SIZE , PACKET_SIZE);
		if(pack.id >= i){
			loss += (pack.id - i);
			i = pack.id + 1;
		}
		else{
			usleep(1);
		}
	}
	
	printf("Lost: %d datas\n",loss);

	return 0;
}

void exit1(){	//when exit remove shm
	struct shmid_ds t;
	if(shmctl(shm_id, IPC_STAT,&t) == -1){
		DIE("shmctl");
	}
	
	if(t.shm_nattch == 1){
		
		if(shmctl(shm_id, IPC_RMID, NULL) == -1){//remove shm memory
			DIE("shmctl");
		}
	}
}

