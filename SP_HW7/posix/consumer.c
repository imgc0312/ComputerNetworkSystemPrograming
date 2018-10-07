#include "my.h"

int main(int argc,char**argv){
	int i;	
	char temp[SIZE];
	packet pack;
	int loss ;
	int num_block;
	struct stat sb;
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

	if ((shm_fd = shm_open("key", O_RDONLY, 0)) < 0) {
		//get shm memory
		DIE("shm_open");
	}
	atexit(exit1);

	if(fstat(shm_fd, &sb) == -1){
		DIE("fstat");
	}
	
	if(sb.st_size < num_block * PACKET_SIZE){
		PRINT("produce size is smaller");
		exit(0);
	}
	
	if((shm_addr = (char*)mmap(NULL, num_block * PACKET_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0)) == (void*)-1){	//attach
		DIE("mmap");
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
	close(shm_fd);
	shm_unlink("key");	//remove shm if all close
}

