#include <stdio.h>

#include <errno.h>

#include <string.h>

#include <stdlib.h>

#include <unistd.h>

#include <sys/ipc.h>

#include <sys/shm.h>

#include <sys/types.h>

#include <stdbool.h>

#define SIZE 100

#define MIN_BLOCKS 5

#define MAX_BLOCKS 30

#define MAX_PACKET 5000

struct packet{
	int id;
	short dataShort[5];
	long dataLong[5];
	double dataDouble[5];
	char dataByte[6];
}typedef packet;

#define PACKET_SIZE sizeof(packet)



#define BASE "\e[0m"
#define GREEN "\e[0;32m"
#define YELLO "\e[0;33m"
#define BLUE "\e[0;34m"

#define DIE(x) perror(x),exit(0)
#define PRINT(x) printf("%s%s\n", process, x)

char process[SIZE] ;
int shm_id;
char *shm_addr;
key_t key;

void exit1();

void setPacket(packet *P,int id);
