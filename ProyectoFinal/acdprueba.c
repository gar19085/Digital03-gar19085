/*
 Recuerde compilar usando -lwiringPi
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>
#include <sched.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/timerfd.h>

#define SPI_CHANNEL	      0	// Canal SPI de la Raspberry Pi, 0 ó 1
#define SPI_SPEED 	1500000	// Velocidad de la comunicación SPI (reloj, en HZ)
                            // Máxima de 3.6 MHz con VDD = 5V, 1.2 MHz con VDD = 2.7V
#define ADC_CHANNEL       0	// Canal A/D del MCP3002 a usar, 0 ó 1
#define NUEVO "PruebaADC.txt"
#define CADENA 60
#define LETRAS 100

uint16_t get_ADC(int channel);	// prototipo


char StringArray[CADENA][LETRAS]; 
char Cadena[LETRAS];
int main(void)
{
    uint16_t ADCvalue;
	
	// Configura el SPI en la RPi#include <time.h>
	if(wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) < 0) {
		printf("wiringPiSPISetup falló.\n");
		return(-1);
	}

	// Bucle que constantemente lee los valores convertidos del canal seleccionado,
    // y lo despliega en la pantalla.
	
	while(1){
		ADCvalue = get_ADC(ADC_CHANNEL);
		printf("Valor de la conversión: %d\n", ADCvalue);
		fflush(stdout);
		sleep(1);
        
    pthread_t  thrd3;
    char Buffer[LETRAS];

    pthread_create(&thrd3, NULL, (void *)&UNIR, (void *)Buffer);	
    
    pthread_join(thrd3, NULL); 	

	FILE *fp_nuevo;
    fp_nuevo = fopen(NUEVO, "w");
	for(i = 0; i < 59 ; i++)
    {
		fputs(StringArray[i], fp_nuevo);
	}	
	fclose(fp_nuevo);
	for(i = 0; i < 59 ; i++)
    {
		printf(StringArray[i]);
	}	
        
	}
     
  return 0;   
}

uint16_t get_ADC(int ADC_chan)
{
	uint8_t spiData[2];	// La comunicación usa dos bytes
	uint16_t resultado;
	
	// Asegurarse que el canal sea válido. Si lo que viene no es válido, usar canal 0.
	if((ADC_chan < 0) || (ADC_chan > 1))
		ADC_chan = 0;

	// Construimos el byte de configuración: 0, start bit, modo, canal, MSBF: 01MC1000
	spiData[0] = 0b01101000 | (ADC_chan << 4);  // M = 1 ==> "single ended"
												// C: canal: 0 ó 1
	spiData[1] = 0;	// "Don't care", este valor no importa.
	
	wiringPiSPIDataRW(SPI_CHANNEL, spiData, 2);	// 2 bytes
	
	// spiData[0] y spiData[1] tienen el resultado (2 bits y 8 bits, respectivamente)
	resultado = (spiData[0] << 8) | spiData[1];
	
	return(resultado);
}

void texto(void*ptr){
    
	int timer_fd = timerfd_create(CLOCK_MONOTONIC, 0);
	struct  itimerspec itval;
    itval.it_interval.tv_sec = 0;
    itval.it_interval.tv_nsec = 100000000;
    itval.it_value.tv_sec = 0;
    itval.it_value.tv_nsec = 50000000;
	if (timerfd_settime(timer_fd, 0, &itval, NULL) == 1){
		perror("Error cargando Timer");
		exit(0);
	}	

	DELAY(timer_fd);
	for(i = 0; i < 59 ; i++)
    {
		strcpy(StringArray[i], Cadena);
        DELAY(timer_fd);
	}	
	pthread_exit(0);
}


void DELAY(int n){
	uint64_t num_periods;
	num_periods = 0;
    read(n, &num_periods, sizeof(num_periods));
    if(num_periods > 1)
    {
        puts("MISSED WINDOW");
        exit(1);
    }



