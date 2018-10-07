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

	if ((shm_fd = shm_open("key", O_CREAT | O_TRUNC | O_RDWR, 0666)) < 0) {
		//get shm memory
		DIE("shm_open");
	}
	atexit(exit1);

	if (ftruncate(shm_fd, num_block * PACKET_SIZE) < 0){//set file size
		DIE("ftruncate"); 
	}


	if((shm_addr = (char*)mmap(NULL, num_block * PACKET_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0)) == (void*)-1){	//attach
		DIE("mmap");
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
	close(shm_fd);
	shm_unlink("key");	//remove shm if all close
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
