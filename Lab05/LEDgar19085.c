/*
 * UNIVERSIDAD DEL VALLE DE GUATEMALA
 * RODRIO GARCIA 
 * 19085 
 * DIGITAL3
 * Laboratorio No.5
 * 21/08/2021
 */


#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


int main(void){
        wiringPiSetupGpio(); //
        pinMode(17 ,OUTPUT); //
        pinMode(27 ,OUTPUT); //
        srand(time(0));
        for(;;)
        {
            digitalWrite(17, HIGH);
            delay(rand()%1500+500); 
            digitalWrite(17, LOW);
            digitalWrite(27, HIGH);
            delay(rand()%1500+500); 
            digitalWrite(27, LOW); 
        }
    return 0;
}

