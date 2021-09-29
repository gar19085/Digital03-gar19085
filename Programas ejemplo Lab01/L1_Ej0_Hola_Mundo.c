/* L1_Ej0_Hola_Mundo.c
   Autor: Luis Alberto Rivera
   
   Programa que muestra aspectos básicos del lenguaje C, incluyendo variables,
   impresión de mensajes a la terminal y lectura de entradas usando el teclado.
*/

/* Para bloques de comentarios, encierre el texto entre /* */
// Para líneas individuales de comentarios, use //

// "Headers" o encabezados a incluir:
#include <stdio.h>

// Todo programa necesita una función principal (main)
int main()
{
	// Declaración de variables, varios tipos (hay más tipos de los que se muestran)
	// Se pueden inicializar o no. Si no, el valor puede ser cero, o basura (depende del compilador)
	char c1, c2 = 'A';
	int i1 = 1, i2;
	float f1 = -2.97, f2;
	double d1, d2 = 0.5;
	char cadena1[50], cadena2[50]; // Estudiaremos cadenas (arreglos de caracteres) y punteros más adelante	
	
	// printf y puts para escribir al "standard output", que por defecto es la consola:
	printf("\nCaracteres: %c, %c.\n", c1, c2);
	printf("\nEnteros: %d, %d.\n", i1, i2);
	printf("\nFloats: %f, %f.\n", f1, f2);
	printf("\nDoubles: %f, %f.\n", d1, d2);
    
	// scanf y gets para leer del "standard input", que por defecto es el teclado:
	printf("\nIngrese un caracter: ");
	fflush(stdout);	  // Para forzar la escritura. Recomendable antes de un scanf.
	scanf("%c", &c1); // Se usa la dirección de la variable (&)
	
	printf("\nIngrese un entero: ");
	fflush(stdout);
	scanf("%d", &i2);
		
	printf("\nIngrese un float: ");
	fflush(stdout);
	scanf("%f", &f2);
	
	printf("\nIngrese un double: ");
	fflush(stdout);
	scanf("%lf", &d1);
		
	printf("\nIngrese una cadena (menos de 50 caracteres, pueden haber espacios en blanco):\n");
	fflush(stdout);
	scanf(" ");		// Para consumir el "enter" ingresado en el último scanf.
					// Necesario antes de leer caracteres o cadenas (si se usó scanf antes).
					// ¿Qué pasa si no se incluye?
	gets(cadena1);	// "get string"
	
	printf("\nIngrese una cadena (menos de 50 caracteres, sin espacios en blanco):\n");
	fflush(stdout);
	scanf("%s", cadena2);	// cadena ya es la dirección (puntero)
	
	// Imprimamos otra vez, para ver lo que se ingresó:
	printf("\nCaracteres: %c, %c.\n", c1, c2);
	printf("\nEnteros: %d, %d.\n", i1, i2);
	printf("\nFloats: %f, %f.\n", f1, f2);
	printf("\nDoubles: %f, %f.\n", d1, d2);
		
	printf("\nCadena1: %s\n", cadena1);
	puts("\nCadena2: "); // Con puts no hay formatos %). Incluye la nueva línea '\n' de una vez.
	puts(cadena2);		 // "put string"
		
	return 0;	// la función main es tipo entero, por eso se retorna un valor
				// se puede usar para retornar estatus/errores del programa
}
