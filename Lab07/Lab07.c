/*
 * UNIVERSIDAD DEL VALLE DE GUATEMALA
 * RODRIO GARCIA 
 * 19085 
 * DIGITAL3
 * Laboratorio No.7
 * 29/09/2021
 */


#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "IE3048lab7.h"

int check_button(void);
void clear_button(void);
void LUCES(void*ptr);

int main(void){
    wiringPiSetupGpio();
    pinMode(13, OUTPUT); //Verde
    pinMode(19, OUTPUT); //Amarillo
    pinMode(26, OUTPUT); //Rojo
    pinMode(16, INPUT);
    pullUpDnControl(16, PUD_DOWN);
    //clear_button();
    //printf("%d", check_button());

    pthread_t thrd1;

    pthread_create(&thrd1, NULL, (void*)&LUCES, NULL);
    pthread_join(thrd1, NULL);

}

void LUCES(void*ptr){
    while(1){
        if(check_button()==0){
            digitalWrite(13, HIGH);
            digitalWrite(26, LOW);
            sleep(1);
            digitalWrite(13, LOW);
            digitalWrite(26, HIGH);
            sleep(1);
        }
        printf("%d", check_button());
        if(check_button()==1){
            digitalWrite(13,LOW);
            digitalWrite(26,LOW);
            digitalWrite(19,HIGH);
            sleep(1);
            digitalWrite(19,LOW);
            clear_button();
        }
    }
}