
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

int sockfd, n;
unsigned int length;
struct sockaddr_in anybody, from;
char buffer[MSG_SIZE];	// to store received messages or messages to be sent.
int boolval = 1;		// for a socket option

//ESTE ES EL HISTORIADOR
//void recibir(void*ptr);
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

	sockfd = socket(AF_INET, SOCK_DGRAM, 0); // Creates socket. Connectionless.
	if(sockfd < 0)
		error("Error: socket");

	anybody.sin_family = AF_INET;		// symbol constant for Internet domain
	anybody.sin_port = htons(atoi(argv[1]));	 // port number
	anybody.sin_addr.s_addr = htonl(INADDR_ANY); // para recibir de cualquier interfaz de red

	length = sizeof(struct sockaddr_in);		 // size of structure

	// Sin el bind, no se reciben los mensajes propios
	if(bind(sockfd, (struct sockaddr *)&anybody, length) < 0)
		error("Error binding socket.");

	// change socket permissions to allow broadcast
	if(setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &boolval, sizeof(boolval)) < 0)
		error("Error setting socket options\n");

    // Cambiamos a la dirección de broadcast
	anybody.sin_addr.s_addr = inet_addr("192.168.0.255");	// broadcast address

    while(1){
        memset(buffer, 0, MSG_SIZE);
        memset(buffer, 0, MSG_SIZE);
		// receive message
		n = recvfrom(sockfd, buffer, MSG_SIZE, 0, (struct sockaddr *)&from, &length);
		if(n < 0)
			error("recvfrom");
		printf("Received something: %s\n", buffer);
    }
	
}

void enviar(void*ptr){

    while(1){
		memset(buffer, 0, MSG_SIZE);	// sets all values to zero
        printf("Los comandos son los siguientes:\n");
		printf("Please enter the message (! to exit): \n");
		fgets(buffer,MSG_SIZE-1,stdin); // MSG_SIZE-1 because a null character is added        
		if(buffer[0] != '!')
		{
			// send message to anyone out there...
			n = sendto(sockfd, buffer, strlen(buffer), 0,
					  (const struct sockaddr *)&anybody, length);
			if(n < 0)
				error("Sendto");
        }
    
    }
}
