/* L1_Ej6_Funciones.c
   Autor: Luis Alberto Rivera
   
   Programa que muestra el uso de funciones, variables globales vs. locales,
   y formatos % adicionales.
*/

#include <stdio.h>
int x = 0;	// variable global

/* Las funciones pueden tener un tipo de retorno (o ninguno), y pueden no tener argumentos
   (void), tener uno o varios argumentos, del mismo o de distintos tipos. */
   
void mensaje(void)
{
	printf("\nEste programa ilustra el uso de funciones, "
	       "y variables globales vs. locales.\n\n");
}

int f(void)
{
	int x = 10;	// variable local, oculta a la variable global
	x = x + 10; // Para evitar confusión, es mejor evitar usar los mismos nombres
	return x;	// para distintas variables.
}

double g(double y)
{
	y += (double)(++x);	// ¿qué x se usa?
	return y;
}

double h(int a, double b)
{
	double z = x + a + b;
	return z;
}

int main(void)
{
	int var;
	mensaje();
	
	// Asegúrense de entender por qué se obtienen los valores que se muestran.
	var = f();
	printf("%04d\n", var);
    printf("%.2lf\n", g(2.5));	// Se pueden llamar funciones dentro de otras funciones
	printf("%.2f\n", h(5, -1.2));
	printf("%04d\n", f());
    printf("%.2lf\n", g(2.5));
	printf("%.2f\n", h(5, -1.2));
	
	return 0;
}