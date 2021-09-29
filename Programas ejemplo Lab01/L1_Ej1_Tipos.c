/* L1_Ej1_Tipos.c
   Original created by: Alina Zare
   Modified by: Luis Alberto Rivera
   
   Programa que ilustra más tipos, valores máximos y mínimos que se logran con
   cada tipo, más formatos.
*/

#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>

int main()
{
// Notar qué y cómo se despliegan los valores, según el tipo y el formato %

    printf("\nChars have the range: %d to %d.\n", CHAR_MIN, CHAR_MAX);
    printf("\nUnsigned chars have the range: 0 to %d.\n", UCHAR_MAX);
    printf("\nShorts have the range: %d to %d.\n", SHRT_MIN, SHRT_MAX);
    printf("\nUnsigned shorts have the range: 0 to %u.\n", USHRT_MAX);
    printf("\nInts have the range: %d to %d.\n", INT_MIN, INT_MAX);
    printf("\nUnsigned ints have the range: 0 to %u.\n", UINT_MAX);
    printf("\nLongs have the range: %lld to %lld.\n", LLONG_MAX, LLONG_MAX);
    printf("\nUnsigned longs have the range: 0 to %llu.\n", ULLONG_MAX);
    printf("\nThe smallest non-zero float value is %.3e.\n", FLT_MIN);
    printf("\nThe smallest non-zero double value is %.3e.\n", DBL_MIN);
    printf("\nThe largest double value is %.5e.\n\n", DBL_MAX);

    signed char c = CHAR_MAX+1;	// ¿Qué pasa si se exceden los máximos/mínimos?
    signed char d = CHAR_MIN-1;
    printf("\nToo small char value: %d.  A too large char value is %d.\n\n", d, c);

    const signed char charValue1 = 65;
    printf("\nThe character is %c.\n", charValue1);
    printf("\nThe character is %d.\n", charValue1);

    signed char charValue2 = 97;
    printf("\nThe character is %c.\n", charValue2);
    printf("\nThe character is %d.\n", charValue2);

    int i;
    i = 3.14;	// ¿Qué pasa si se trata de asignar un no entero a una variable int?
    double pi = i;
    printf("\nValue of pi: %f. \n", pi);
    
    pi = 3.14;
    printf("\nValue of pi: %f. \n", pi);
	
	return 0;
}
