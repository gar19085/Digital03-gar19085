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

int PUSH1 = 0;
int PUSH2 = 0;
int FLG1 = 0;
int FLG2 = 0;
int SW1 = 0;
int SW2 = 0;

void Button1(void); 
void Button2(void); 
void Switch1(void);
void Switch2(void);

int main(void){
    wiringPiSetupGpio();
    pinMode(5, INPUT);
	pinMode(17, INPUT);
	pinMode(19, INPUT);
	pinMode(26, INPUT);
    pullUpDnControl(5, PUD_UP);
	pullUpDnControl(17, PUD_UP);
	pullUpDnControl(19, PUD_UP);
	pullUpDnControl(26, PUD_UP);

	wiringPiISR(5, INT_EDGE_BOTH, (void*)&Button1);
	wiringPiISR(17, INT_EDGE_BOTH, (void*)&Button2);
	wiringPiISR(19, INT_EDGE_BOTH, (void*)&Switch1);
	wiringPiISR(26, INT_EDGE_BOTH, (void*)&Switch2);

	while (1){
		/* code */
	}
	
}

void Button1(void){
	PUSH2 = digitalRead(5);
	if(PUSH2 == 0){
		FLG1=1;
	}		
	if(PUSH2 == 1 && FLG1 == 1){	
    	printf("Boton 1 funciona interrupción funcionando\n");
		fflush(stdout);
		FLG1=0;
	}
}

void Button2(void){
	PUSH1 = digitalRead(17);
	if(PUSH1 == 0){
		FLG2=1;
	}	
	if(PUSH1 == 1 && FLG2 == 1){
    	printf("Boton 2 funciona interrupción funcionando\n");
		fflush(stdout);
		FLG2=0;
	}
}

void Switch1(void){
	SW1 = digitalRead(19);
	printf("Switch 1 funciona interrupción funcionando\n");
	fflush(stdout);
}

void Switch2(void){
	SW2 = digitalRead(26);
	printf("Switch 2 funciona interrupción funcionando\n");
	fflush(stdout);
}