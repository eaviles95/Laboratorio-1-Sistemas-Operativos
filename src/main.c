#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../incl/example.h"
#include "../incl/funciones.h"


int main(int argc, char const *argv[])
{
	int a = obtenerCantLineas("archivo.txt");
	char h[] = "1 2 3";
	quitarEspacios(h);
	return 0; 
}
