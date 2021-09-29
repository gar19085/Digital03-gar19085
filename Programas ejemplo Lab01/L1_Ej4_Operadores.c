/* L1_Ej4_Operadores.c
   Original created by: Alina Zare
   Modified by: Luis Alberto Rivera
   
   Programa que muestra más operadores.
*/

#include <stdio.h>
#include <limits.h>

#define XVAL 1	// Podemos definir constantes numéricas, caracteres, cadenas, etc.
#define ZVAL 2	// Los símbolos definidos se reemplazan por sus valores en el código,
				// antes de la compilación.

int main(void)
{
	int x = XVAL, z = ZVAL, y; 
	
	y = z & x;	// AND "bitwise"
	printf("\nx is:%X,\tz is: %X,\tz & x is: %X\n", x, z, y);
	
	y = z | x;	// OR "bitwise"
	printf("\nx is:%X,\tz is: %X,\tz | x is: %X\n", x, z, y);
	
	y = z && x;	// AND lógico
	printf("\nx is:%X,\tz is: %X,\tz && x is: %X\n", x, z, y);
	
	y = z || x;	// OR lógico
	printf("\nx is:%X,\tz is: %X,\tz || x is: %X\n", x, z, y);
	
	x = 0; z = 0x1000;
	y = z && x;	// AND lógico
	printf("\nx is:%X,\tz is: %X,\tz && x is: %X\n", x, z, y);
	
	y = z || x;	// OR lógico
	printf("\nx is:%X,\tz is: %X,\tz || x is: %X\n", x, z, y);

	return 0;
}
