/* L1_Ej3_Operadores.c
   Original created by: Alina Zare
   Modified by: Luis Alberto Rivera
   
   Programa que muestra más operadores.
*/

#include <stdio.h>

int main(void)
{
	unsigned int x = 3; 
	int z = 4;
	
	// Notar qué pasa si no se usan los formatos/tipos adecuados.
    printf("\n3/4 using integral types: %d.\n", x/z);
    printf("3/4 using float cast: %f\n", (float)x/z);
    printf("The average of %d and %d is %d.\n", x, z, (1/2)*(x+z));
    printf("The average of %d and %d is %d.\n", x, z, (1.0/2)*(x+z));
    printf("The average of %d and %d is %f.\n\n", x, z, (1.0/2)*(x+z));

    x = 0x0F;
    z = 0xF0;
    printf("x is %d (%X);  z is %d (%X); x&z is %d (%X).\n", x, x, z, z, x&z, x&z);	  // AND (bitwise)
    printf("x is %d (%X);  z is %d (%X); x|z is %d (%X).\n", x, x, z, z, x|z, x|z);	  // OR (bitwise)
    printf("x is %d (%X);  z is %d (%X); x^z is %d (%X).\n\n", x, x, z, z, x^z, x^z); // XOR (bitwise)

    x = 1;
    printf("x is %d (%X);  x<<1 is: %d (%X);  x<<4 is: %d (%X).\n",
			x, x, x<<1, x<<1, x<<4, x<<4); // "bit shift" hacia la izquierda
	
	x = 32;
    printf("x is %d (%X);  x>>1 is: %d (%X);  x>>5 is: %d (%X).\n\n",
			x, x, x>>1, x>>1, x>>5, x>>5); // "bit shift" hacia la derecha

    x = 3;
    z = 2;
    x += z;		// equivalente a x = x + z;
    printf("%d\n", x);
    x *= z;
    printf("%d\n", x);
    x *= z+1;
    printf("%d\n", x);
    x *= z++;
    printf("%d\n", x);
    x /= ++z;
    printf("%d\n\n", x);
	
	return 0;
}
