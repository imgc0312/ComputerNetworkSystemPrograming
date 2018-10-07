/*
 * lookup7 : does no looking up locally, but instead asks
 * a server for the answer. Communication is by Unix TCP Sockets
 * The name of the socket is passed as resource.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "dict.h"

int lookup(Dictrec * sought, const char * resource) {
	static int sockfd;
	static struct sockaddr_un server;
	static int first_time = 1;
	int n;

	if (first_time) {     /* connect to socket ; resource is socket name */
		first_time = 0;

		/* Set up destination address.
		 * Fill in code. */
		if((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1){
			//use default procotol
			perror("socket");
			return UNAVAIL;
		}
		

		/* Allocate socket. */
		server.sun_family = AF_UNIX;
		strcpy(server.sun_path,resource);

		/* Connect to the server.
		 * Fill in code. */
		if(connect(sockfd, (struct sockaddr *) &server, sizeof(server)) == -1){
			perror("connect");
			return UNAVAIL;
		}



	}

	/* write query on socket ; await reply
	 * Fill in code. */
	if(write(sockfd, sought, sizeof(*sought)) == -1){//send request
		perror("write");
		return UNAVAIL;
	}

	if(read(sockfd, sought, sizeof(*sought)) == -1){//wait reply
		perror("read");
		return UNAVAIL;
	}




	if (strcmp(sought->text,"XXXX") != 0) {
		return FOUND;
	}

	return NOTFOUND;
}
