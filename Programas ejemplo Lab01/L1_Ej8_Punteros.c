/* L1_Ej8_Punteros.c
   Autor: Luis Alberto Rivera
   
   Programa que muestra el uso de punteros.
*/

#include <stdio.h>

int main(void)
{
	int x = 1;
	int *xPtr = &x;  // xPtr apunta a x
	
	printf("\nTamaño de int (bytes): %d\n", sizeof(int));
	printf("Tamaño de double (bytes): %d\n", sizeof(double));
	printf("Tamaño de char (bytes): %d\n\n", sizeof(char));

	// Notar que con %p se imprimen las direcciones (punteros)
	printf("The memory address of x and the value of xPtr is %p.\n", xPtr);
	xPtr++;	// Se incrementa el puntero (dirección) en una unidad del tamaño de variables int
	printf("After xPtr++: The  value of xPtr is %p.\n\n", xPtr);	// ¿Cuántos bytes para un int?

	double *xPtrd = (double *)&x;	// without the cast, you get a warning
	printf("The memory address of x and the value of xPtrd is %p.\n", xPtrd);
	xPtrd++; // Se incrementa el puntero en una unidad del tamaño de variables double
	printf("After xPtrd++: The value of xPtrd is %p.\n\n", xPtrd);	// ¿Cuántos bytes para un double?

	char *xPtrc = (char *)&x;	// without the cast, you get a warning
	printf("The memory address of x and the value of xPtrc is %p.\n", xPtrc);
	xPtrc++; // Se incrementa el puntero en una unidad del tamaño de variables char
	printf("After xPtrc++: The value of xPtrc is %p.\n\n", xPtrc);	// ¿Cuántos bytes para un char?
	
	return 0;
}
