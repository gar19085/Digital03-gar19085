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

#define SPI_CHANNEL	      0	// Canal SPI de la Raspberry Pi, 0 ó 1
#define SPI_SPEED 	1500000	// Velocidad de la comunicación SPI (reloj, en HZ)
                            // Máxima de 3.6 MHz con VDD = 5V, 1.2 MHz con VDD = 2.7V
#define ADC_CHANNEL       0	// Canal A/D del MCP3002 a usar, 0 ó 1

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
uint8_t interruptor1 =0;
uint8_t interruptor2 =0;


int socket_desc;
	struct sockaddr_in server;
	char *message;
    char server_reply[2000];

uint32_t timestamp (void){
    
    time_t myTime;
    
    myTime= time(NULL);
    return (uint32_t ) myTime; 
    
}

void update_timestamp (void){
    
     time_t timer;
    char buffer[26];
    struct tm* tm_info;

    timer = time(NULL);
    tm_info = localtime(&timer);

    strftime(timestamp_str, 26, "%Y-%m-%d %H:%M:%S", tm_info);
 
    return ;
}

uint8_t conectar_servidor (void){
    
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1) printf("No pude crear socket");
		
	server.sin_addr.s_addr = inet_addr("199.250.222.55");
	server.sin_family = AF_INET;
	server.sin_port = htons(80);

	//Connect to remote server
	if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0){
		puts("connect error");
		return 1;
	}
	
	puts("Connected\n");
    
    //Send some data
	message = "GET / HTTP/1.1\r\n\r\n";
	if( send(socket_desc , message , strlen(message) , 0) < 0){
		puts("Send failed");
		return 1;
	}
	puts("Data Send\n");
       
	//Receive a reply from the server
	if (recv(socket_desc, server_reply , 2000 , 0) < 0){
		puts("recv failed");
	}
	puts("Reply received\n");
	puts(server_reply); 
}



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

    }
    else {
        last_alarm_status=0;
    }
}

void alarma_alto_voltaje (void){
    char mensaje[64];
    static uint8_t last_alarm_status=0; 
    
    if (voltajeadc > 2.5){
        if(last_alarm_status == 0){
           //printf ("%ld\t %s\t Alarma de bajo voltaje detectado\t %0.2f\n", time_on, timestamp_str, voltajeadc);
            sprintf (mensaje,"Alarma de alto voltaje detectado\t %0.2f", voltajeadc);
            agregar_evento(mensaje);
            last_alarm_status =1;
        }

    }
    else {
        last_alarm_status=0;
    }
}

void alarma_boton1 (void){
    char mensaje[64];
    static uint8_t last_boton_status=0; 
    
    if (boton1 == 1 ){
        if(last_boton_status == 0){
           //printf ("%ld\t %s\t Alarma de bajo voltaje detectado\t %0.2f\n", time_on, timestamp_str, voltajeadc);
            sprintf (mensaje,"Alarma de boton1 presionado detectado\t %0.2f", voltajeadc);
            agregar_evento(mensaje);
            last_boton_status =1;
        }

    }
    else {
        last_boton_status=0;
    }
}

int main(void)
{
    uint16_t ADCvalue;
	conectar_servidor();
    return 0;
    
	// Configura el SPI en la RPi
	if(wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) < 0) {
		printf("wiringPiSPISetup falló.\n");
		return(-1);
	}

	while(1){
        time_on++;
        
        if ((time_on % 5 )==0){
            boton1=1;
        }
            else {
                boton1=0;
            }
        
        update_timestamp();
		ADCvalue = get_ADC(ADC_CHANNEL);
    
		//printf("Valor de la conversión: %d\n", ADCvalue);
        //printf("%ld\t%0.2f\n", time_on, voltajeadc);
        //printf("%ld\t%ld\t%0.2f\n", time_on, timestamp(),voltajeadc);
        printf("%ld\t%s\t%0.2f\n", time_on, timestamp_str,voltajeadc);
        alarma_bajo_voltaje();
        alarma_alto_voltaje();
        alarma_boton1();
		fflush(stdout);
        if ((time_on % 20 )==0){
            printf("Eventos pendientes:\n");
            listar_eventos();
        }
		sleep(1);
	}
     
  return 0;   
}

// Entrada: ADC_chan 0
// Salida: un entero "unsigned" de 16 bit  con el valor de la conversión

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
