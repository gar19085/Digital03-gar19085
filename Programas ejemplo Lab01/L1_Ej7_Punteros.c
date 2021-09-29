/* L1_Ej7_Punteros.c
   Autor: Luis Alberto Rivera
   
   Programa que muestra el uso de punteros.
*/

#include <stdio.h>

int main(void)
{
	int x = 1, y = 2;
	int *xPtr;  // declaración de un puntero (a int, en este caso)
	// xPtr es una variable tipo "puntero a int". Por el momento, no está apuntando a nada.
	
	xPtr = &x;  // Se le asigna a xPtr la dirección (en memoria) de x. "Apunta a x"
				// La variable xPtr tiene la dirección de x.
	printf("1. The memory address of x is %p\n", &x);
	printf("2. The value of xPtr is %p.\n", xPtr);

	// Para usar o cambiar el valor guardado en la dirección a la que apunta xPtr,
	// se debe "de-referenciar" el puntero. Esto se hace con el operador *, así:
	y = *xPtr; // a y se le asigna el valor en la dirección a la que apunta xPtr
	printf("3. The value of y is now %d.\n", y);

	y = *xPtr + 1;  
	printf("4. The value of y is now %d.\n", y);

	*xPtr = 0; // En la dirección a la que apunta xPtr se guarda el valor 0
	printf("5. The value of *xPtr is now %d.\n", *xPtr);
	printf("6. The value of x is now %d.\n", x);
	printf("7. The value of y is now %d.\n", y);
	
	return 0;
}
