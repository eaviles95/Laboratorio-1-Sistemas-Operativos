#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "../incl/funciones.h"

void usoArgumentos()
{
	printf("\n Existe un error en los argumentos de entrada! \n");
	printf("\nc: cantidad de imagenes.\n");
	printf("m: nombre del archivo con la mascara.\n");
	printf("n: porcentaje del umbral de negro.\n");
	printf("b: bandera para mostrar datos por pantalla (si se ingresa, se muestran los resultados).\n");
	printf("\n./exe -c <Cantidad> -m <filtro.txt> -n <Umbral> -b\n\n");
	return;
}


