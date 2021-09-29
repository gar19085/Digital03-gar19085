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
#include <pthread.h>

int A;
int Push;
int FLG = 0;
int START = 1;
int menu;

void Threadcontrol(void*ptr){
            while(1){
            fflush(stdout);
            printf("Menu de sonido");
            scanf(" %c", &menu);
            if(menu == 'p'){
                FLG = 1;
            }
            if(menu == 'r'){
                FLG = 0;
            }
            if(menu == 's'){
               exit(0);       
            }
    }
}    

int main(void){
            wiringPiSetupGpio();
            pinMode(13, OUTPUT);
            pullUpDnControl(5, PUD_UP);
            A = (1/1760)/2;
            pthread_t thread1;
            pthread_create(&thread1, NULL, (void*)&Threadcontrol, NULL);
            
            while(1){
                Push = digitalRead(5);
                if(Push == 0 ){
                    START = 0;
                }
                if(START == 0 & FLG == 0){    
                        digitalWrite(13,HIGH);
                        delay(A);
                        digitalWrite(13,LOW);
                        delay(A);
                }        
            }
}

