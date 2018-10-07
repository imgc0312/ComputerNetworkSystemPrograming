/*
 * lookup9 : does no looking up locally, but instead asks
 * a server for the answer. Communication is by Internet UDP Sockets
 * The name of the server is passed as resource. PORT is defined in dict.h
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include "dict.h"

int lookup(Dictrec * sought, const char * resource) {
	static int sockfd;
	static struct sockaddr_in server;
	struct hostent *host;
	static int first_time = 1;

	if (first_time) {  /* Set up server address & create local UDP socket */
		first_time = 0;

		/* Set up destination address.
		 * Fill in code. */
		server.sin_family = AF_INET;
		server.sin_port = htons(PORT);
		if((host = gethostbyname(resource)) == NULL){
			perror("gethostbyname");
			return UNAVAIL;
		}
		memcpy((char *)&server.sin_addr, host->h_addr, host->h_length);

		/* Allocate a socket.
		 * Fill in code. */
		if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
			perror("socket");
			return UNAVAIL;
		}


	}

	/* Send a datagram & await reply
	 * Fill in code. */
	int addr_size = sizeof(struct sockaddr_in);
	if(sendto(sockfd, sought, sizeof(*sought), 0, (struct sockaddr*)&server, addr_size) == -1){
		perror("sendto");
		return UNAVAIL;
	}
	if(recvfrom(sockfd, sought, sizeof(*sought), 0, (struct sockaddr*) &server, &addr_size) == -1){
		perror("recvfrom");
		return UNAVAIL;
	}




	if (strcmp(sought->text,"XXXX") != 0) {
		return FOUND;
	}

	return NOTFOUND;
}
