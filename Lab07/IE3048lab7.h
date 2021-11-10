/* IE3048lab7.h
 * IE3048 - Electrónica Digital 3
 * Autor: Luis Alberto Rivera
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Para el lab 7, necesitará copiar 3 archivos a la tarjeta SD del Raspberry Pi:
 - El archivo de encabezado "IE3048lab7.h" (este archivo)
 - El ejecutable "IE3048lab7"
 - La libería estática "libIE3048lab7.a".
 
 Por conveniencia, copie los archivos en el directorio donde estarán sus programas
 (aunque pueden copiarse donde prefiera).
 
 Para poder usar las funciones check_button y clear_button en sus programas,
 necesita incluir este archivo: #include "IE3048lab7.h"
 
 Al compilar sus programas, necesitarán enlazar la libería estática. 
 Para ello, compile así:
	gcc miprograma.c -o miprograma libIE3048lab7.a
		o
	gcc miprograma.c -o miprograma -L/ruta/al/directorio_donde_está_la_lib -lIE3048lab7
	
 Si usa funciones de wiringPi, incluya también -lwiringPi al invocar gcc.
 Si usa pthreads, no olvide incluir también -lpthread al compilar.
 
 Si usa Eclipse, asegúrese de incluir las liberías en las configuraciones.
 
 Antes de correr "miprograma", debe correr el ejecutable IE3048lab7.
 Sugerencia: abra dos terminales, y corra cada programa en una terminal distinta
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

int check_button(void);
void clear_button(void);
