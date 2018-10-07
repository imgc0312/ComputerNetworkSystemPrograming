/*
 * usock_server : listen on a Unix socket ; fork ;
 *                child does lookup ; replies down same socket
 * argv[1] is the name of the local datafile
 * PORT is defined in dict.h
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include "dict.h"

int main(int argc, char **argv) {
    struct sockaddr_un server;
    int sd,cd,n;
    Dictrec tryit;

    if (argc != 3) {
      fprintf(stderr,"Usage : %s <dictionary source>"
          "<Socket name>\n",argv[0]);
      exit(errno);
    }

    /* Setup socket.
     * Fill in code. */
	if((sd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1){
		DIE("socket");
	}
    
    /* Initialize address.
     * Fill in code. */
		server.sun_family =  AF_UNIX;
		strcpy(server.sun_path,argv[2]);
		unlink(server.sun_path ); /* Otherwise bind could fail */

    /* Name and activate the socket.
     * Fill in code. */
		if(bind(sd, (struct sockaddr*) &server, sizeof(server)) == -1){
			//name socket
			DIE("bind");
		}

		if(listen(sd,128) == -1){//128 is max
			//activate socket
			DIE("listen");
		}



    /* main loop : accept connection; fork a child to have dialogue */
    for (;;) {
		/* Wait for a connection.
		 * Fill in code. */
		struct sockaddr_un client;
		int addr_size = sizeof(client);
		if((cd = accept(sd, (struct sockaddr*) &client, &addr_size)) == -1){
			DIE("accept");
		}



		/* Handle new client in a subprocess. */
		switch (fork()) {
			case -1 : 
				DIE("fork");
			case 0 :
				close (sd);	/* Rendezvous socket is for parent only. */
				/* Get next request.
				 * Fill in code. */
				while (read(cd, &tryit, sizeof(tryit)) != -1) {

					/* Lookup request. */
					switch(lookup(&tryit,argv[1]) ) {
						/* Write response back to client. */
						case FOUND: 
							/* Fill in code. */
							if(write(cd, &tryit, sizeof(tryit)) == -1){
								DIE("write");
							}

							break;
						case NOTFOUND: 
							/* Fill in code. */
							strcpy(tryit.text,"XXXX");
							if(write(cd, &tryit, sizeof(tryit)) == -1){
								DIE("write");
							}

							break;
						case UNAVAIL:
							DIE(argv[1]);
					} /* end lookup switch */

				} /* end of client dialog */

				/* Terminate child process.  It is done. */
				exit(0);

			/* Parent continues here. */
			default :
				close(cd);
				break;
		} /* end fork switch */
    } /* end forever loop */
} /* end main */
