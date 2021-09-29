/* L1_Ej5_Preprocesador.c
   Autor: Luis Alberto Rivera
   
   Programa que muestra el uso de instrucciones del pre-procesador
*/

// Las instrucciones con # como las siguientes son instrucciones del pre-procesador.
// Se procesan antes de compilar.
#include <stdio.h>
#define PRINTF 0	// probar también con los valores 1 y 2. Compilar y ver qué pasa
					// en cada caso.

int main(void)
{
	char a;
	printf("\nAlways to be printed. Enter a letter to continue.\n");
	fflush(stdout);
	scanf("%c", &a);

#if PRINTF > 0	// si no se cumple la condición, el código no se compila
	printf("\nPrinted if PRINTF > 0\n");
#endif

#if PRINTF > 1	// si no se cumple la condición, el código no se compila
	printf("\nPrinted if PRINTF > 1\n");
#endif
	
	return 0;
}
