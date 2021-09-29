/* L1_Ej11_Estructuras.c
   Autor: Luis Alberto Rivera
   
   Programa que muestra el uso de estructuras de datos.
*/

#include <stdio.h>

int main(void)
{
	struct Signal_Info{
		int numPoints;		// miembros de la estructura
		int maxValue;
		char *comments;
	};

	struct Signal_Info signal1_Info;	// variable tipo "struct Signal_Info"

	signal1_Info.numPoints = 50;	// los miembros se acceden con el operador '.'
	signal1_Info.maxValue = 255;
	signal1_Info.comments = "Comments for Signal";

	printf("The value of the numPoints member is: %d\n", signal1_Info.numPoints);
	printf("The value of the maxValue member is: %d\n", signal1_Info.maxValue);
	printf("The value of the comments member is: %s\n\n", signal1_Info.comments);

	struct Signal_Info *signalPtr = &signal1_Info;	// podemos tener punteros a estructuras
	printf("The value of the numPoints member is: %d\n", (*signalPtr).numPoints);
	printf("The value of the maxValue member is: %d\n", signalPtr->maxValue);	// Operador '->',
										// equivalente a (*Ptr).: (*Ptr).miembro == Ptr->miembro
	printf("The value of the comments member is: %s\n\n", signalPtr->comments);
	
	struct Signal_Info sigInfoArray[3];	// Podemos tener arreglos de estructuras
	// Notar la diferencia en bytes en las direcciones a continuación.
	// ¿Puede explicar esa diferencia?
	printf("The adresses of the structures:\n%p\n%p\n%p\n\n",
			sigInfoArray, sigInfoArray+1, sigInfoArray+2);

	// Podemos definir un nuevo tipo, con un nombre que queramos.
	typedef struct{
		struct Signal_Info info;	// podemos tener estructuras como miembros de estructuras
		int *dataPointer;	// También podemos tener punteros como miembros de estructuras.
	}FullSignal;	// FullSignal es el nombre del nuevo tipo. Se puede usar como int, char, etc.

	int signalArray[100] = {1, 2};

	// Como definimos FullSignal como nuevo tipo, ya no tenemos que escribir struct, como antes.
	FullSignal signal1 = {{10, 150, "Tarea 1"}, signalArray};	// Así podemos inicializar las estructuras
	// signal1 es una variable tipo FullSignal.

	printf("The value of the numPoints member in signal1: %d\n", signal1.info.numPoints);
	printf("The value of the maxValue member in signal1: %d\n", signal1.info.maxValue);
	printf("The value of the comments member in signal1: %s\n", signal1.info.comments);
	printf("The value of a few datapoints in signal1: %d, %d, %d\n",
			signal1.dataPointer[0], signal1.dataPointer[1], signal1.dataPointer[2]);
	
	return 0;
}
