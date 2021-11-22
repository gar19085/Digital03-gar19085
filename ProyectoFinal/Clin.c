
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <pthread.h>

#define MSG_SIZE 40			// message size

int sockfd1,sockfd2, n;
unsigned int length;
struct sockaddr_in RTU, from1;
char buffer[MSG_SIZE];	// to store received messages or messages to be sent.
int boolval = 1;		// for a socket option

//ESTE ES EL HISTORIADOR

void enviar(void*ptr);

void error(const char *msg)
{
	perror(msg);
	exit(0);
}

int main(int argc, char *argv[])
{
    pthread_t thread1, thread2;
    //pthread_create(&thread1, NULL, (void*)&recibir , NULL);
    pthread_create(&thread2, NULL, (void*)&enviar, NULL);

	if(argc != 2)
	{
		printf("usage: %s port\n", argv[0]);
		exit(1);
	}

	sockfd1 = socket(AF_INET, SOCK_DGRAM, 0); // Creates socket. Connectionless.
	if(sockfd1 < 0)
		error("Error: socket");

	/*sockfd2 = socket(AF_INET, SOCK_DGRAM, 0); // Creates socket. Connectionless.
	if(sockfd2 < 0)
		error("Error: socket");
*/
	RTU.sin_family = AF_INET;		// symbol constant for Internet domain
	RTU.sin_port = htons(atoi(argv[1]));	 // port number
	//RTU.sin_addr.s_addr = htonl(INADDR_ANY); // para recibir de cualquier interfaz de red

	length = sizeof(struct sockaddr_in);		 // size of structure

	// Sin el bind, no se reciben los mensajes propios
	if(bind(sockfd1, (struct sockaddr *)&RTU, length) < 0)
		error("Error binding socket.");

	// change socket permissions to allow broadcast
	if(setsockopt(sockfd1, SOL_SOCKET, SO_BROADCAST, &boolval, sizeof(boolval)) < 0)
		error("Error setting socket options\n");

	printf("Los comandos son los siguientes:\n");

    while(1){
        memset(buffer, 0, MSG_SIZE);
		// receive message
		n = recvfrom(sockfd1, buffer, MSG_SIZE, 0, (struct sockaddr *)&from1, &length);
		if(n < 0)
			error("recvfrom");
		printf("Received from RTU1: %s\n", buffer);


		memset(buffer, 0, MSG_SIZE);
		n = recvfrom(sockfd1, buffer, MSG_SIZE, 0, (struct sockaddr *)&from1, &length);
		if(n < 0)
			error("recvfrom");
		printf("Received from RTU2: %s\n", buffer);		
    }	
}

void enviar(void*ptr){

    while(1){
		memset(buffer, 0, MSG_SIZE);	// sets all values to zero
		printf("Please enter the message (! to exit): \n");
		fgets(buffer,MSG_SIZE-1,stdin); // MSG_SIZE-1 because a null character is added        
		if(buffer[0] != '!')
		{
			if((strcmp(buffer, "RTU1 LED1 1\n"))==0){	
    			// Cambiamos a la dirección de broadcast
				RTU.sin_addr.s_addr = inet_addr("192.168.240.245");	// broadcast address
				// send message to anyone out there...
				n = sendto(sockfd1, buffer, strlen(buffer), 0,
					  (const struct sockaddr *)&RTU, length);
				if(n < 0)
					error("Sendto");
			}
			if((strcmp(buffer, "RTU1 LED1 0\n"))==0){	
    			// Cambiamos a la dirección de broadcast
				RTU.sin_addr.s_addr = inet_addr("192.168.240.245");	// broadcast address
				// send message to anyone out there...
				n = sendto(sockfd1, buffer, strlen(buffer), 0,
					  (const struct sockaddr *)&RTU, length);
				if(n < 0)
					error("Sendto");
			}			
			if((strcmp(buffer, "RTU1 LED2 1\n"))==0){	
    			// Cambiamos a la dirección de broadcast
				RTU.sin_addr.s_addr = inet_addr("192.168.240.245");	// broadcast address
				// send message to anyone out there...
				n = sendto(sockfd1, buffer, strlen(buffer), 0,
					  (const struct sockaddr *)&RTU, length);
				if(n < 0)
					error("Sendto");
			}
			if((strcmp(buffer, "RTU1 LED2 0\n"))==0){	
    			// Cambiamos a la dirección de broadcast
				RTU.sin_addr.s_addr = inet_addr("192.168.240.245");	// broadcast address
				// send message to anyone out there...
				n = sendto(sockfd1, buffer, strlen(buffer), 0,
					  (const struct sockaddr *)&RTU, length);
				if(n < 0)
					error("Sendto");
			}			
			if((strcmp(buffer, "RTU1 REPORTE\n"))==0){	
    			// Cambiamos a la dirección de broadcast
				RTU.sin_addr.s_addr = inet_addr("192.168.240.245");	// broadcast address
				// send message to anyone out there...
				n = sendto(sockfd1, buffer, strlen(buffer), 0,
					  (const struct sockaddr *)&RTU, length);
				if(n < 0)
					error("Sendto");
			}						
			if((strcmp(buffer, "RTU2\n"))==0){
				RTU.sin_addr.s_addr = inet_addr("192.168.240.203");	
			
				n = sendto(sockfd1, buffer, strlen(buffer), 0,
					  (const struct sockaddr *)&RTU, length);
				if(n < 0)
					error("Sendto");			
			}
        }
    
    }
}
