/* L1_Ej10_Archivos.c
   Autor: Luis Alberto Rivera
   
   Programa que muestra cómo leer y escribir archivos.
   También se muestran algunas estructuras básicas de control (if-else, for)
   Investiguen esas y otras estructuras de control: while, do while, switch-case
*/

#include <stdio.h>

int main()
{
	FILE *fp_r, *fp_w; // Punteros a FILE
	int i, datain[5];  // Tamaño fijo. ¿Qué pasa si no sabemos cuánta data vamos a leer?
					   // En futuros labs veremos cómo asignar memoria dinámicamente.

	fp_r = fopen("L1_file1.txt","r");  // Abrir para lectura
	if(fp_r == NULL)
		perror("Error opening file");	// "print error". Se pudo usar printf.
	else
	{
		for(i = 0; i < 5; i++)	// se leen los datos del archivo, uno por uno.
			fscanf(fp_r, "%d", datain+i); // equivalente: &datain[i]
	}
	fclose(fp_r);	// Cerrar el archivo
	
	fp_w = fopen("L1_file2.txt","w"); // Se abre el archivo para escritura. Si el archivo no
										// existe, se crea.
	if(fp_w == NULL)
		perror("Error opening file");
	else
	{
		for(i = 0; i < 5; i++)	// se escriben los datos en el nuevo archivo. Notar el formato.
			fprintf(fp_w, "Dato %d:\t%d,\t%f,\t%X\n",
					i, datain[i], 1.0*datain[i], datain[i]);
	}
	fclose(fp_w);	// Cerrar el archivo.
	
	printf("Listo...\n\n");

	return 0;
}

