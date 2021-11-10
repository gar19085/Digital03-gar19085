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
#include <semaphore.h>
#include <pthread.h>
#include "IE3048lab7.h"


#define INIT_VALUE	1		// Para el valor inicial del semáforo
int PRIORIDADVERDE = 1;
int PRIORIDADROJO = 1;
int PRIORIDADAMARILLO = 1;



int check_button(void);
void clear_button(void);
void LUZVERDE(void*ptr);
void LUZROJA(void*ptr);

sem_t semaphore;

int main(void){  
    struct sched_param param;
    param.sched_priority = PRIORIDADAMARILLO;
    sched_setscheduler(0, SCHED_RR, &param);      
    wiringPiSetupGpio();
    pinMode(13, OUTPUT); //Verde
    pinMode(19, OUTPUT); //Amarillo
    pinMode(26, OUTPUT); //Rojo
    pinMode(16, INPUT);
    pullUpDnControl(16, PUD_DOWN);

    pthread_t thrd1;
    pthread_t thrd2;


    sem_init(&semaphore, 0, INIT_VALUE);

    pthread_create(&thrd1, NULL, (void*)&LUZVERDE, NULL);
    pthread_create(&thrd2, NULL, (void*)&LUZROJA, NULL);

    printf("LUZ AMARILLA");
    while(1){
        sem_wait(&semaphore);
        if(check_button()==1){
            digitalWrite(19, HIGH);
            sleep(1);
            digitalWrite(19, LOW);     
        }
        sem_post(&semaphore);     
        usleep(1000);   
        clear_button();
    }           
        return 0;
      
}

void LUZVERDE(void*ptr){
    struct sched_param param;
    param.sched_priority = PRIORIDADVERDE;
    sched_setscheduler(0, SCHED_RR, &param); 
    while(1){
            sem_wait(&semaphore);
            digitalWrite(13, HIGH);
            sleep(1);
            digitalWrite(13, LOW);
            sem_post(&semaphore);
            usleep(1000);
    }
    pthread_exit(0);
}

void LUZROJA(void*ptr){
    struct sched_param param;
    param.sched_priority = PRIORIDADROJO;
    sched_setscheduler(0, SCHED_RR, &param);
    while(1){    
            sem_wait(&semaphore);
            digitalWrite(26, HIGH);
            sleep(1);
            digitalWrite(26, LOW);
            sem_post(&semaphore);
            usleep(1000);
    }
    pthread_exit(0);
}
