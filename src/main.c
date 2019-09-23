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

		while ((option = getopt(argc, argv, "cmnb")) != -1)
		{
			switch (option)
			{
			case 'c':
				cflag = 1;
				break;
			case 'm':;
				mflag = 1;
				break;
			case 'n':
				nflag = 1;
				break;
			case 'b':
				bflag = 1;
				break;
			default:
				printf("Error");
			}
		}

		if (cflag == 0 || mflag == 0 || nflag == 0)
		{
			usoArgumentos();
		}
	}
	else
	{
		usoArgumentos();
	}
	

	/*
	int a = obtenerCantLineas("archivo.txt");
	char h[] = "1 2 3";
	quitarEspacios(h);
	return 0;
*/
}
