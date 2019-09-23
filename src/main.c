#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "../incl/funciones.h"

int main(int argc, char **argv)
{
	if (argc > 6)
	{
		int option;

		int cflag = 0;
		int mflag = 0;
		int nflag = 0;
		int bflag = 0;

		int cantidadImagenes = 0;
		char *archivoMascara = NULL;
		int umbralNegro = 0;

		while ((option = getopt(argc, argv, "c:m:n:b")) != -1)
		{
			switch (option)
			{
			case 'c':
				cflag = 1;
				cantidadImagenes = atoi(optarg);
				break;
			case 'm':;
				mflag = 1;
				archivoMascara = optarg;
				break;
			case 'n':
				nflag = 1;
				umbralNegro = atoi(optarg);
				break;
			case 'b':
				bflag = 1;
				break;
			case '?':
				usoArgumentos();
				break;
			default:
				usoArgumentos();
			}
		}

		if (cflag == 0 || mflag == 0 || nflag == 0)
		{
			usoArgumentos();
		}
		else
		{
			// Listo para enviar al pipeline.
			printf("\nCantidad de imagenes: %d\n", cantidadImagenes);
			printf("Nombre del archivo mascara: %s\n", archivoMascara);
			printf("Porcentaje de umbral de negro: %d\n", umbralNegro);
			printf("Valor de flag de muestra de resultados: %d\n\n", bflag);

			int a = obtenerCantLineas(archivoMascara);
			char h[] = "1 2 3";
			quitarEspacios(h);
			printf("\n");
			return 0;
		}
	}
	else
	{
		usoArgumentos();
		return 0;
	}
}
