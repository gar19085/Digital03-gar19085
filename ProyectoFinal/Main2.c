#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <time.h>
#include <string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include <pthread.h>

#define SPI_CHANNEL	      0	// Canal SPI de la Raspberry Pi, 0 ó 1
#define SPI_SPEED 	1500000	// Velocidad de la comunicación SPI (reloj, en HZ)
                            // Máxima de 3.6 MHz con VDD = 5V, 1.2 MHz con VDD = 2.7V
#define ADC_CHANNEL       0	// Canal A/D del MCP3002 a usar, 0 ó 1
#define MSG_SIZE 40	


//Variables
uint16_t get_ADC(int channel);	
float voltajeadc=0;
uint32_t time_on=0;
char timestamp_str [26];
uint32_t numero_eventos=0;
#define MAX_NEVENTOS 100
char eventos_pendientes[MAX_NEVENTOS+1][64];
uint16_t n_eventos_pendientes_envio =0;
uint8_t boton1 =0;
uint8_t boton2 =0;

int A;
int PUSH1 = 0;
int PUSH2 = 0;
int FLG1 = 0;
int FLG2 = 0;
int FLGB = 0;


int FLG;
int OFL;
int sockfd, n;
unsigned int length;
struct sockaddr_in server, addr;
char buffer[MSG_SIZE];	// to store received messages or messages to be sent.
int boolval = 1;	

//funciones
void Button1(void); 
void Button2(void); 
void Switch1(void);
void Switch2(void);
void iotarduino(void);
/*
int socket_desc;
	struct sockaddr_in server;
	char *message;
    char server_reply[2000];
*/
void RTU2(void*ptr);

void ej_strtok(char *);

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

//Conexión con historiador
void RTU2(void*ptr){
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
	    //n = sendto(sockfd, "Got a message. Was it from you?\n", MSG_SIZE, 0,
    	//	      (struct sockaddr *)&addr, length);
	    
		if(n < 0)
	 		error("sendto");

		if((strcmp(buffer, "RTU2\n"))==0){
			printf("Se recibio RTU\n");
			fflush(stdout);
			strcpy(buffer, "RTU2 recibio");
			fflush(stdout);
			n = sendto(sockfd, buffer, MSG_SIZE, 0,
            (struct sockaddr *)&addr, length);
			if(n < 0)
			error("sendto");
		}
		if((strcmp(buffer, "RTU2 LED1\n"))==0){
			printf("Encender LED1\n");
			fflush(stdout);
			strcpy(buffer, "RTU2 LED1 = 1");
			fflush(stdout);
			n = sendto(sockfd, buffer, MSG_SIZE, 0,
            (struct sockaddr *)&addr, length);
			if(n < 0)
			error("sendto");
		}
		if((strcmp(buffer, "RTU2 LED2\n"))==0){
			printf("Encender LED2\n");
			fflush(stdout);
			strcpy(buffer, "RTU2 LED2 = 1");
			fflush(stdout);
			n = sendto(sockfd, buffer, MSG_SIZE, 0,
            (struct sockaddr *)&addr, length);
			if(n < 0)
			error("sendto");
		}        
		if((strcmp(buffer, "RTU2 REPORTE\n"))==0){
			printf("Enviar Reporte\n");
			fflush(stdout);
			strcpy(buffer, "RTU1 recibio");
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

	}
}

uint32_t timestamp (void){
    
    time_t myTime;
    
    myTime= time(NULL);
    return (uint32_t ) myTime; 
    
}

//Timestep
void update_timestamp (void){
    
     time_t timer;
    char buffer[26];
    struct tm* tm_info;

    timer = time(NULL);
    tm_info = localtime(&timer);

    strftime(timestamp_str, 26, "%Y-%m-%d %H:%M:%S", tm_info);
 
    return ;
}



//Funciones para orden de eventos
void listar_eventos(void){
    int i;
    printf("listado eventos\n");
    for (i=0; i< n_eventos_pendientes_envio; i++){
        printf("%d = %s\n ", i, eventos_pendientes[i]);
    }
}

void agregar_evento(char * msg){
    char buffer[128];
    numero_eventos++;
    sprintf (buffer,"%ld\t %s\t %s", numero_eventos, timestamp_str, msg);
    printf("Evento agregado: %s\n", buffer);
    if(n_eventos_pendientes_envio < MAX_NEVENTOS){
        strcpy(eventos_pendientes[n_eventos_pendientes_envio ], buffer);
        n_eventos_pendientes_envio++;
        printf("n_eventos_pendientes_envio = %ld\n", n_eventos_pendientes_envio);
    }
}

//Funciones de alarma
void alarma_bajo_voltaje (void){
    char mensaje[64];
    static uint8_t last_alarm_status=0; 
    
    if (voltajeadc < 0.5){
        if(last_alarm_status == 0){
           //printf ("%ld\t %s\t Alarma de bajo voltaje detectado\t %0.2f\n", time_on, timestamp_str, voltajeadc);
            sprintf (mensaje,"Alarma de bajo voltaje detectado\t %0.2f", voltajeadc);
            agregar_evento(mensaje);
            last_alarm_status =1;
        }
        FLGB = 1;
        if(FLGB == 1){
            //last_alarm_status =1;
            //FLGB = 1;
            digitalWrite(13, HIGH);
            delay(A);
            digitalWrite(13, LOW);
            delay(A);     
        }    
    }

    else {
        last_alarm_status=0;
        FLGB = 0;
    }
}

void alarma_alto_voltaje (void){
    char mensaje[64];
    static uint8_t last_alarm_status=0; 
    
    if (voltajeadc < 0.5){
        if(last_alarm_status == 0){
           //printf ("%ld\t %s\t Alarma de bajo voltaje detectado\t %0.2f\n", time_on, timestamp_str, voltajeadc);
            sprintf (mensaje,"Alarma de bajo voltaje detectado\t %0.2f", voltajeadc);
            agregar_evento(mensaje);
            last_alarm_status =1;
        }
        FLGB = 1;
        if(FLGB == 1){
            //last_alarm_status =1;
            //FLGB = 1;
            digitalWrite(13, HIGH);
            delay(A);
            digitalWrite(13, LOW);
            delay(A);     
        }    
    }

    else {
        last_alarm_status=0;
        FLGB = 0;
    }
}

//Funcion principal
int main(int argc, char *argv[]){
    wiringPiSetupGpio();
    pinMode(5, INPUT);
	pinMode(17, INPUT);
	pinMode(19, INPUT);
	pinMode(26, INPUT);
    pinMode(12, INPUT);
    pinMode(13,OUTPUT);
    A = (1/1760)/2;
    pullUpDnControl(5, PUD_UP);
	pullUpDnControl(17, PUD_UP);
	pullUpDnControl(19, PUD_UP);
	pullUpDnControl(26, PUD_UP);
    digitalWrite(13, LOW);

	wiringPiISR(5, INT_EDGE_BOTH, (void*)&Button1);
	wiringPiISR(17, INT_EDGE_BOTH, (void*)&Button2);
	wiringPiISR(19, INT_EDGE_BOTH, (void*)&Switch1);
	wiringPiISR(26, INT_EDGE_BOTH, (void*)&Switch2);
    wiringPiISR(12, INT_EDGE_BOTH, (void*)&iotarduino);

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

    uint16_t ADCvalue;
	//conectar_servidor();
    //return 0;

    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, (void*)&RTU2, NULL);    

	// Configura el SPI en la RPi
	if(wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) < 0) {
		printf("wiringPiSPISetup falló.\n");
		return(-1);
	}

	while(1){
        time_on++;
                
        update_timestamp();
		ADCvalue = get_ADC(ADC_CHANNEL);
    
		//printf("Valor de la conversión: %d\n", ADCvalue);
        //printf("%ld\t%0.2f\n", time_on, voltajeadc);
        //printf("%ld\t%ld\t%0.2f\n", time_on, timestamp(),voltajeadc);
        printf("%ld\t%s\t%0.2f\n", time_on, timestamp_str,voltajeadc);
        alarma_bajo_voltaje();
        alarma_alto_voltaje();


		fflush(stdout);
        if ((time_on % 20 )==0){
            printf("Eventos pendientes:\n");
            listar_eventos();
            if (n_eventos_pendientes_envio >0){
           // conectar_servidor();
            }
        }
		sleep(1);
	}
     
  return 0;   
}

uint16_t get_ADC(int ADC_chan)
{
	uint8_t spiData[2];	// La comunicación usa dos bytes
	uint16_t resultado;
	
	if((ADC_chan < 0) || (ADC_chan > 1))
		ADC_chan = 0;

	// Byte de configuración: 0, start bit, modo, canal, MSBF: 01MC1000
	spiData[0] = 0b01101000 | (ADC_chan << 4);  // M = 1 ==> "single ended"
												// C: canal: 0 ó 1
	spiData[1] = 0;	// "Don't care"
	
	wiringPiSPIDataRW(SPI_CHANNEL, spiData, 2);	// 2 bytes
	
	// spiData[0] y spiData[1] tienen el resultado (2 bits y 8 bits, respectivamente)
	resultado = (spiData[0] << 8) | spiData[1];
    
    voltajeadc=(resultado*3.3)/1023.0;
	
	return(resultado);
}

//Funciones de Interrupciones

void Button1(void){
    char mensaje[64];
	PUSH2 = digitalRead(5);
	
	if(PUSH2 == 1 ){
    	sprintf(mensaje, "Boton 1 presionado\n");
		fflush(stdout);
        agregar_evento(mensaje);
	}
}

void Button2(void){
    char mensaje[64];
	PUSH1 = digitalRead(17);
    
	if(PUSH1 == 1 ){
    	sprintf(mensaje, "Boton 2 presionado\n");
    //    printf(mensaje);
		fflush(stdout);
        agregar_evento(mensaje);
	}
}

void Switch1(void){
    char mensaje[64];
    int switch1= digitalRead(19);
    
   // printf("Switch1 = %d\n", switch1);
    if (switch1==1){
	sprintf(mensaje,"Switch 1 apagado\n");
	fflush(stdout);
    agregar_evento(mensaje);
    }
    if (switch1==0 ) {
	sprintf(mensaje,"Switch 1 encendido\n");
	fflush(stdout);
    agregar_evento(mensaje);
    }
    
}

void Switch2(void){
    char mensaje[64];
    int switch2= digitalRead(26);
    
	//printf("Switch2 = %d\n", switch2);
    if (switch2==1){
	sprintf(mensaje,"Switch 2 apagado\n");
	fflush(stdout);
    agregar_evento(mensaje);
    }
    if (switch2==0 ) {
	sprintf(mensaje, "Switch 2 encendido\n");
	fflush(stdout);
    agregar_evento(mensaje);
    }
}

void iotarduino(void){
    char mensaje[64];
    int status_led_1= digitalRead(12);
	//printf("Iot status LED = %d\n", status_led_1);
    
    if (status_led_1==1){
	sprintf(mensaje, "Iot status LED  encendido\n");
	fflush(stdout);
    agregar_evento(mensaje);
    }
    if (status_led_1==0 ) {
	sprintf(mensaje,"Iot status LED  apagado\n");
	fflush(stdout);
    agregar_evento(mensaje);
    }
}
