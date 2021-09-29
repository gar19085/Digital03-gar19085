/* L1_Ej9_Arrays.c
   Autor: Luis Alberto Rivera
   
   Programa que muestra el uso de arreglos (arrays) y su relación con punteros.
*/

#include <stdio.h>

int main(void)
{
	int a[10];	// arreglo de 10 enteros. 10 espacios de memoria del tamaño de int.
	int *arrayPtr = &a[0]; 	// apunta a la dirección del primer elemento del arreglo

	*arrayPtr = 1;		// equivalente a a[0] = 1;
	*++arrayPtr = 2;	// equivalente a a[1] = 2;
	*++arrayPtr = 3;	// equivalente a a[2] = 3;
	*(arrayPtr+2) = 5;	// equivalente a a[4] = 5;

	printf("The value at location 0 is %d. \n", a[0]);
	printf("The value at location 1 is %d. \n", a[1]);
	printf("The value at location 2 is %d. \n", a[2]);
	printf("The value at location 3 is %d. \n", a[3]);
	printf("The value at location 4 is %d. \n\n", a[4]);

	// Hay varias formas de acceder a los elementos. Lo más fácil es usar a[i],
	// pero se puede trabajar como punteros.

	a[3] = 4;
	arrayPtr = &a[0];
	printf("The value at a[3] is %d. \n", a[3]);
	printf("The value at *(arrayPtr+3) is %d. \n", *(arrayPtr+3));
	printf("The value at *(a+3) is %d. \n\n", *(a+3));	// a es en sí un puntero

	// Notar las direcciones, y la diferencia (en bytes) entre direcciones consecutivas.
	printf("The address value of arrayPtr is %p.\n", arrayPtr);
	printf("The address value of a is %p.\n", a);
	printf("The address value of &a[0] is %p.\n\n", &a[0]);

	printf("The address of location 1 in a is %p. \n", &a[0]);
	printf("The address at location 2 in a is %p. \n", &a[1]);
	printf("The address at location 3 in a is %p. \n\n", &a[2]);
	
	printf("The address value of a+2 is %p.\n", a+2);
	printf("The address value of &a[2] is %p.\n\n", &a[2]);
	
	printf("The address value of a+9 is %p.\n", a+9);
	printf("The address value of &a[9] is %p.\n\n", &a[9]);

	double b[10];
	printf("The address of location 1 in b is %p. \n", &b[0]);
	printf("The address at location 2 in b is %p. \n", &b[1]);
	printf("The address at location 3 in b is %p. \n\n", &b[2]);

	return 0;
}
