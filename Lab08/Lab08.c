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

#define MSG_SIZE 40			// message size
#define IP "192.168.1.34"
#define UIP "34"

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
	char R1[MSG_SIZE];
	char R2[MSG_SIZE];
	char VO[MSG_SIZE];
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
	server.sin_addr.s_addr = inet_addr("192.168.1.255");	// para recibir de cualquier interfaz de red

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
		}
		
		else if((strncmp(buffer, "#\n", 1))==0){
			char *token;
			int cont;
			cont = 0;
			int RIP;
			token = strtok(buffer, ". ");

			while (token != NULL){
				token = strtok(NULL, ". ");
				cont++;
				//printf("CONT: %d \n", cont);
				if(cont==4){
					RIP=atoi(token);
				}					
				if(cont==5 && atoi(token) > val){
					FLG = 0;
					cont=0;
					OFL = 1;
					//printf("TOK %s", token);
					token = 0;
				}
				if(cont==5 && atoi(token) < val){
					FLG = 1;
					cont=0;
					//printf("TOK %s", token);
					token = 0;
				}
				if(cont==5 && atoi(token) == val){
					cont=0;
					//printf("TOK %s", token);
					if(RIP > atoi(UIP)){
						FLG = 1;
					}
					if(RIP < atoi(UIP)){
						FLG = 0;
						OFL = 1;
					}
					token = 0;
				}
			}
			
			printf("se recibio voto\n");
			fflush(stdout);
									
		}
		 
		else{
			printf("Se recibio basura\n");
			fflush(stdout);
		}

	    //printf("Despues de enviar\n");
	}

	return 0;
 }

