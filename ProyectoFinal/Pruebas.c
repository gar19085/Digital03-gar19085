/*
*
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* RODRIGO GARCIA, 19085
* DIGITAL 3 
* FECHA: 09/11/2021
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <time.h>

//#define SPI_CHANNEL     0   // Canal SPI de la Raspberry Pi, 0 ó 1
//#define SPI_SPEED 	1500000	// Velocidad de la comunicación SPI (reloj, en HZ)
                            // Máxima de 3.6 MHz con VDD = 5V, 1.2 MHz con VDD = 2.7V
//#define ADC_CHANNEL     0   // Canal A/D del MCP3002 a usar, 0 ó 1


void prueba(void); 

int main(void){
    wiringPiSetup();
    //pinMode(16, INPUT);
    //pullUpDnControl(16, PUD_DOWN);


	wiringPiISR(0, INT_EDGE_FALLING, (void*)&prueba);
	
	while (1)
	{
		/* code */
	}
	
}


void prueba(void){
    printf("interrupción funcionando");
	fflush(stdout);
}