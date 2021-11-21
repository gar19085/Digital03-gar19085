//UNIVERSIDAD DEL VALLE DE GUATEMALA
//DIGITAL 3
//PROYECTO FINAL
//FECHA: 10/11/2021
//GABRIELA ALFARO
//RODRIGO GARCIA
//HISTORIADOR


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <pthread.h>

#define MSG_SIZE 40			// message size


char buffer[MSG_SIZE];	// to store received messages or messages to be sent.
int sockfd, n;
unsigned int length;
struct sockaddr_in server, addr;
int boolval = 1;			// for a socket option


void recibir(void*ptr);
void enviar(void*ptr);
void ej_strtok(char *);

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

void recibir(void*ptr){
	memset(buffer, 0, MSG_SIZE);	// sets all values to zero.
	
	// receive from a client
	n = recvfrom(sockfd, buffer, MSG_SIZE, 0, (struct sockaddr *)&addr, &length);
    if(n < 0)
	error("recvfrom"); 

}

void enviar(void*ptr){
	memset(buffer, 0, MSG_SIZE);	// sets all values to zero.
	
	// receive from a client
	n = sendto(sockfd, "Got a message. Was it from you?\n", MSG_SIZE, 0,
        (struct sockaddr *)&addr, length);
	    if(n < 0)
	 	error("sendto");

}


int main(int argc, char *argv[])
{
	printf("Los comandos son:\n");
	
	
	pthread_t thrd1, thrd2;
	pthread_create(&thrd1, NULL, (void*)&recibir, NULL);
	pthread_create(&thrd2, NULL, (void*)&enviar, NULL);
    pthread_join(thrd1, NULL);
	pthread_join(thrd2, NULL);
	
	int FLG;
	int OFL;
	int val;

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
	//server.sin_addr.s_addr = inet_addr("192.168.1.255");	// para recibir de cualquier interfaz de red

	length = sizeof(server);			// size of structure

	// binds the socket to the address of the host and the port number
	if(bind(sockfd, (struct sockaddr *)&server, length) < 0)
		error("Error binding socket.");

	// change socket permissions to allow broadcast
	if(setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &boolval, sizeof(boolval)) < 0)
   		error("Error setting socket options\n");

   	
	while(1)
	{
		memset(buffer, 0, MSG_SIZE);	// sets all values to zero.
		
		// receive from a client
		n = recvfrom(sockfd, buffer, MSG_SIZE, 0, (struct sockaddr *)&addr, &length);
	    if(n < 0)
	 		error("recvfrom"); 

	    //printf("Received a datagram. It says: %s", buffer);

		// El siguiente mensaje se envía a la dirección de la que se recibió
		// el mensaje anterior. Dicha IP se copia en la estructura addr al
		// momento de recibirse el mensaje.
	    //n = sendto(sockfd, "Got a message. Was it from you?\n", MSG_SIZE, 0,
    	//	      (struct sockaddr *)&addr, length);
	    
		if(n < 0)
	 		error("sendto");

		if((strcmp(buffer, "VOTE\n"))==0){
			printf("Se recibio VOTE\n");
			fflush(stdout);
			val = (rand()%10 ) + 1;
			//printf("%d", val);
			sprintf(VO, "# 192.168.1.34 %d", val);
			fflush(stdout);
			OFL = 0;
			n = sendto(sockfd, VO, MSG_SIZE, 0,
				(struct sockaddr *)&server, length);
			if(n < 0)
			error("sendto");
		}
	/*
		else if((strcmp(buffer, "QUIEN ES\n"))==0){
			printf("Se recibio QUIEN ES\n");
			fflush(stdout);	
			if(FLG == 1 && OFL == 0){
				n = sendto(sockfd, "Rodrigo Garcia es el master\n", MSG_SIZE, 0,
				(struct sockaddr *)&addr, length);
			if(FLG < 0)
			error("sendto");		
			}
			if(FLG == 0 && OFL == 0){
				n = sendto(sockfd, "Rodrigo Garcia es el master\n", MSG_SIZE, 0,
				(struct sockaddr *)&addr, length);
			if(FLG < 0)
			error("sendto");		
			}								
		}*/
			 
		else{
			printf("Se recibio basura\n");
			fflush(stdout);
		}

	    //printf("Despues de enviar\n");
	}

	return 0;
 }
