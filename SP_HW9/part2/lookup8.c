/*
 * lookup8 : does no looking up locally, but instead asks
 * a server for the answer. Communication is by Internet TCP Sockets
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

	if (first_time) {        /* connect to socket ; resource is server name */
		first_time = 0;

		/* Set up destination address. */
		server.sin_family = AF_INET;
		/* Fill in code. */
		server.sin_port = htons(PORT);
		if((host = gethostbyname(resource)) == NULL){
			perror("gethostname");
			return UNAVAIL;
		}
		
		memcpy((char*) &server.sin_addr, host->h_addr, host->h_length);





		/* Allocate socket.
		 * Fill in code. */
		if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
			perror("socket");
			return UNAVAIL;
		}




		/* Connect to the server.
		 * Fill in code. */
		if(connect(sockfd,(struct sockaddr*) &server, sizeof(server)) == -1){
			perror("connect");
			return UNAVAIL;
		}


	}

	/* write query on socket ; await reply
	 * Fill in code. */
	if(write(sockfd, sought, sizeof(*sought)) == -1){//send
		perror("write");
		return UNAVAIL;
	}

	if(read(sockfd, sought, sizeof(*sought)) == -1){//wait
		perror("read");
		return UNAVAIL;
	}




	if (strcmp(sought->text, "XXXX") != 0) {
		return FOUND;
	}

	return NOTFOUND;
}
