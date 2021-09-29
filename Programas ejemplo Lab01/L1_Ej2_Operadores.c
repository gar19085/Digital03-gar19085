/* L1_Ej2_Operadores.c
   Original created by: Alina Zare
   Modified by: Luis Alberto Rivera
   
   Programa que muestra algunos operadores, y más formatos %.
*/

#include <stdio.h>
#include <limits.h>

int main(void)
{
	unsigned int x; 
	int z = 0;
	
	x = 1;
	printf("\nUnary ! operator: x: %d and !x: %d.\n", x, !x);	// NOT
	printf("Unary ! operator: x+1: %d and !(x+1): %d.\n", x+1, !(x+1));
	
	x = 0;
	printf("Unary ! operator: x: %d and !x: %d.\n", x, !x);
	
	x = UINT_MAX;
	printf("Unary ~ operator: x: %u and ~x: %u.\n", x, ~x);		// complemento (bitwise)

	x = 0xFFFFFFFE;		// notación hexadecimal
	printf("Unary ~ operator: x: %u (hex: %X) and ~x: %u (hex: %X).\n",x, x, ~x, ~x);
	
	x = 0b11001100;		// notación binaria
	printf("Unary ~ operator: x: %u (hex: %X) and ~x: %u (hex: %X).\n",x, x, ~x, ~x);

	z = 10;
	printf("Unary - operator: z: %d and -z: %d.\n\n",z, -z);	// negativo

	x = 1;
	// ¿Cuál es la diferencia entre ++x y x++?
	printf("Unary ++ prefix operator: x:  %d.\n", x);
	printf("\t \t \t ++x: %d.\n", ++x);
	printf("\t \t \t ++x: %d.\n\n", ++x);
	
	x = 1;
	printf("Unary ++ postfix operator: x: %d.\n", x);
	printf("\t \t \t x++: %d.\n", x++);
	printf("\t \t \t x++: %d.\n\n", x++);
	
	return 0;
}
