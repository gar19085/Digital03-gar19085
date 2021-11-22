/*
 * Universidad del Valle de Guatemala
 * Rodrigo Garcia, 19085
 * Digital 3
 * Laboratorio No.8
 * Fecha 27/10/2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <pthread.h>

#define MSG_SIZE 40			// message size

//ESTE CODIGO VA EN LA RPI
void ej_strtok(char *);

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
	int FLG;
	int OFL;
	int sockfd, n;
	int val;
	unsigned int length;
	struct sockaddr_in server, addr;
	char buffer[MSG_SIZE];	// to store received messages or messages to be sent.
	int boolval = 1;			// for a socket option

	srand(time(0));

	if(argc != 2)
	{
		printf("usage: %s port\n", argv[0]);
		exit(0);
	}

	sockfd = socket(AF_INET, SOCK_DGRAM, 0); // Creates socket. Connectionless.
	if(sockfd < 0)
		error("Opening socket");

	server.sin_family = AF_INET;		// symbol constant for Internet domain
	server.sin_port = htons(atoi(argv[1]));		// port number
	server.sin_addr.s_addr = htonl(INADDR_ANY); //inet_addr("192.168.1.255");	// para recibir de cualquier interfaz de red

	length = sizeof(server);			// size of structure

	// binds the socket to the address of the host and the port number
	if(bind(sockfd, (struct sockaddr *)&server, length) < 0)
		error("Error binding socket.");

	// change socket permissions to allow broadcast
	if(setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &boolval, sizeof(boolval)) < 0)
   		error("Error setting socket options\n");

   	server.sin_addr.s_addr = inet_addr("192.168.0.255");

	while(1)
	{
		memset(buffer, 0, MSG_SIZE);	// sets all values to zero.
		
		// receive from a client
		n = recvfrom(sockfd, buffer, MSG_SIZE, 0, (struct sockaddr *)&addr, &length);
	    if(n < 0)
	 		error("recvfrom"); 

	    printf("Received a datagram. It says: %s", buffer);

		// El siguiente mensaje se envía a la dirección de la que se recibió
		// el mensaje anterior. Dicha IP se copia en la estructura addr al
		// momento de recibirse el mensaje.
	    //n = sendto(sockfd, "Got a message. Was it from you?\n", MSG_SIZE, 0,
    	//	      (struct sockaddr *)&addr, length);
	    
		if(n < 0)
	 		error("sendto");

		if((strcmp(buffer, "hola\n"))==0){
			printf("Se recibio hola\n");
			fflush(stdout);
			//val = (rand()%10 ) + 1;
			//printf("%d", val);
			strcpy(buffer, "manda un 1 al FLG");
			fflush(stdout);
			n = sendto(sockfd, buffer, MSG_SIZE, 0,
            (struct sockaddr *)&addr, length);
			if(n < 0)
			error("sendto");
		}
		else{
			printf("Se recibio basura\n");
			fflush(stdout);
		}

	    //printf("Despues de enviar\n");
	}

	return 0;
 }

