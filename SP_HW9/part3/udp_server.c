/*
 * udp_server : listen on a UDP socket ;reply immediately
 * argv[1] is the name of the local datafile
 * PORT is defined in dict.h
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>

#include "dict.h"

int main(int argc, char **argv) {
	static struct sockaddr_in server,client;
	int sockfd,siz;
	Dictrec dr, *tryit = &dr;

	if (argc != 2) {
		fprintf(stderr,"Usage : %s <datafile>\n",argv[0]);
		exit(errno);
	}

	/* Create a UDP socket.
	 * Fill in code. */
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
		DIE("socket");
	}



	/* Initialize address.
	 * Fill in code. */
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY);//any eth

	/* Name and activate the socket.
	 * Fill in code. */
	if(bind(sockfd, (struct sockaddr*)&server, sizeof(server)) == -1){
		//name
		DIE("bind");
	}
	/* udp not need listen()*/

	for (;;) { /* await client packet; respond immediately */

		siz = sizeof(client); /* siz must be non-zero */

		/* Wait for a request.
		 * Fill in code. */

		while (recvfrom(sockfd, tryit, sizeof(*tryit), 0, (struct sockaddr*) &client, &siz) != -1) {
			/* Lookup request and respond to user. */
			switch(lookup(tryit,argv[1]) ) {
				case FOUND: 
					/* Send response.
					 * Fill in code. */
					if(sendto(sockfd, tryit, sizeof(*tryit), 0, (struct sockaddr *) &client, siz) == -1){
						DIE("sendto");
					}
					

					break;
				case NOTFOUND : 
					/* Send response.
					 * Fill in code. */
					strcpy(tryit->text, "XXXX");
					if(sendto(sockfd, tryit, sizeof(*tryit), 0, (struct sockaddr *) &client, siz) == -1){
						DIE("sendto");
					}



					break;
				case UNAVAIL:
					DIE(argv[1]);
			} /* end lookup switch */
		} /* end while */
	} /* end forever loop */
} /* end main */
