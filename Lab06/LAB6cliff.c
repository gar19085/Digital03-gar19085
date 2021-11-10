/*
 * Universidad del Valle de Guatemala
 * Laboratorio No.6
 * Electronica Digital 3
 * 01/09/2021
 * Rodrigo Garcia, 19085
 */


#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sched.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/timerfd.h>
#include <time.h>


#define ARCH1 "Lab6_primero.txt" //Impares
#define ARCH2 "Lab6_segundo.txt" //Pares
#define NUEVO "Lab06_nuevo.txt"
#define CADENA 60
#define LETRAS 100
#define PRIORIDAD 1

void DELAY(int n);
char StringArray[CADENA][LETRAS+1]; // arreglo de cadenas
int i = 0;
int pares = 0;
int impares = 0;
char Cadena[LETRAS+1];


void PRIMERO(void*ptr){ //Impares
    int timer_fd1 = timerfd_create(CLOCK_MONOTONIC, 0);
    struct itimerspec itval;
    itval.it_interval.tv_sec = 0;
    itval.it_interval.tv_nsec = 200000000;
    itval.it_value.tv_sec = 0;
    itval.it_value.tv_nsec = 100;
    if(	timerfd_settime(timer_fd1, 0, &itval, NULL) == 1)
    {
		perror("Error al hacer el timer.");
		exit(0);
	}	

    struct sched_param param;
    param.sched_priority = PRIORIDAD;
    if(sched_setscheduler(0, SCHED_FIFO, &param) == 1){
        perror("sched_setscheduler falló");
        exit(0);
    }	
    FILE *fp_arch1;
        
    fp_arch1=fopen(ARCH1, "r");
    if(fp_arch1 == NULL){
		perror("Error al abrir el archivo.");
		exit(0);
	}
	DELAY(timer_fd1);	
	while(fgets(Cadena, LETRAS, fp_arch1) != NULL){
		fflush(stdout);
		DELAY(timer_fd1);
		impares++;
	}

	fclose(fp_arch1);	// cierra el archivo original.
	pthread_exit(0);
}

void SEGUNDO(void*ptr){ //Pares
    int timer_fd2 = timerfd_create(CLOCK_MONOTONIC, 0);
   struct itimerspec itval;
    	itval.it_interval.tv_sec = 0;
    	itval.it_interval.tv_nsec = 200000000;
    	itval.it_value.tv_sec = 0;
    	itval.it_value.tv_nsec = 100000000;
   	if(	timerfd_settime(timer_fd2, 0, &itval, NULL) == 1)
    {
		perror("Error al hacer el timer.");
		exit(0);
	}

    struct sched_param param;
    param.sched_priority = PRIORIDAD;
    if(sched_setscheduler(0, SCHED_FIFO, &param) == 1){
        perror("sched_setscheduler falló");
        exit(0);
    }	
    
	FILE *fp_arch2;
    
    fp_arch2=fopen(ARCH2, "r");
    if(fp_arch2 == NULL){
		perror("Error al abrir el archivo.");
		exit(0);
	}
	DELAY(timer_fd2);	
	while(fgets(Cadena, LETRAS, fp_arch2) != NULL){
		fflush(stdout);
		DELAY(timer_fd2);
		pares++;	
	}

	fclose(fp_arch2);	
	pthread_exit(0);	
}

void UNIR(void*ptr){
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


int main(){
    pthread_t thrd1, thrd2, thrd3;
    char Buffer[LETRAS];
    
    pthread_create(&thrd1, NULL, (void *)&PRIMERO, (void *)Buffer);
    pthread_create(&thrd2, NULL, (void *)&SEGUNDO, (void *)Buffer);
    pthread_create(&thrd3, NULL, (void *)&UNIR, (void *)Buffer);	
    
    pthread_join(thrd1, NULL);
    pthread_join(thrd2, NULL); 
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

	printf("\nNúmero total de líneas leídas: %d\n", pares+impares);	
	printf("\nReconstruicción Completa\n");	
	return 0;
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
}	