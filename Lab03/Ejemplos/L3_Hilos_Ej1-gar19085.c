/*
 ============================================================================
 Nombre: L3_Hilos_Ej1.c
 Autor:  Luis Alberto Rivera
 Editado por:Rodrigo García
 Carnet:19085
 Tercera parte del ejercicio del Laboratorio No.3
 4/08/2021
 ============================================================================
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Código a ejecutar por el segundo hilo
void My_Thread2(void *ptr)
{
	char *message;	// puntero, para la cadena de caracteres (string)
	message = (char *)ptr; // recupera la información pasada a este hilo

	while(1)
	{
		printf("%s", message);
		fflush(stdout);
		usleep(1100000);
	}
	
	// Lo siguiente no se ejecutará, pero es buena costumbre incluirlo
	pthread_exit(0);	// Para salir correctamente del hilo
}

void My_Thread4(void *ptr)
{
	while(1)
	{
		fflush(stdout);
		usleep(5000000);
		printf("ELECTRONICA DIGITAL 3, LAB 3, Rodrigo Garcia");
	}	
	pthread_exit(0);	// Para salir correctamente del hilo
}

// Función principal (primer hilo de ejecución)
int main(void)
{
	pthread_t thread2;	// variable para identificar el 2do hilo que se creará
	pthread_t thread3;
	pthread_t thread4;
	// Los siguientes son dos strings
	char *message1 = "Hello ";	
	char *message2 = "World\n";
	char *message3 = "West";	
	char *message4 = "Virginia\n";
	// Función que crea un POSIX thread (pthread), que es un hilo del estándar POSIX
	// necesita la variable tipo pthread, configuraciones (NULL para usar las default),
	// la función a ejecutar por el hilo, y puntero para la información que se quiere
	// pasar al nuevo hilo (NULL si no se quiere pasar nada)
	pthread_create(&thread2, NULL, (void*)&My_Thread2, (void*)message1);
	pthread_create(&thread3, NULL, (void*)&My_Thread2, (void*)message3);
	pthread_create(&thread4, NULL, (void*)&My_Thread4, NULL);

	while(1)
	{
		printf("%s", message2);
		printf("%s", message4);
		fflush(stdout);
		usleep(1000000);
	}

	return(0);
}