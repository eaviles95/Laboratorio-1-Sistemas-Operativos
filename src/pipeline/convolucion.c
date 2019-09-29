#include "../../incl/cabeceras.h"
#include "../../incl/convolucion.h"

int obtenerCantLineas(char *nombreArchivo)
{
	FILE *fichero = fopen(nombreArchivo, "r");
	int contador = 0;
	char *linea = (char *)malloc(sizeof(char) * 70);
	while (feof(fichero) == 0)
	{
		if (fgets(linea, 70, fichero) == NULL)
		{
			contador--;
		}
		if (linea[0] == 10 || linea[0] == 9)
		{
		}
		else
		{
			contador++;
		}
	}
	return contador;
}

char **extraerLineas(char *nombre, int lineas)
{
	char **palabra = (char **)malloc(sizeof(char *) * 100);
	char linea[1024];
	FILE *fich;

	fich = fopen(nombre, "r");
	int i = 0;
	while (fgets(linea, 1024, (FILE *)fich))
	{
		palabra[i] = (char *)malloc(sizeof(char));
		strcat(palabra[i], linea);
		i = i + 1;
	}
	fclose(fich);
	return palabra;
}

char *quitarEspacios(char frase[])
{
	char *palabras;
	char *linea = (char *)malloc(sizeof(char) * 3);
	int i;
	palabras = strtok(frase, " ");
	linea[0] = palabras[0];
	for (i = 0; i <= strlen(frase); i++)
	{
		palabras = strtok(0, " ");
		linea[i + 1] = palabras[0];
	}
	return linea;
}

int **crearMatrizMascara(char **matriz, int lineas)
{
	char **matrizAux = (char **)malloc(sizeof(char *));
	int i, j;
	int **mtx = (int **)malloc(sizeof(int *));
	for (i = 0; i < 3; i++)
	{
		matrizAux[i] = (char *)malloc(sizeof(char));
		matrizAux[i] = quitarEspacios(matriz[i]);
	}
	for (i = 0; i < 3; i++)
	{
		mtx[i] = (int *)malloc(sizeof(int));
		for (j = 0; j < 3; j++)
		{
			//se resta '0' para obtener el valor entero del caracter
			mtx[i][j] = matrizAux[i][j] - '0';
		}
	}
	i = 0;
	return mtx;
}

int **matrices(int **mtx1, int **mtx2)
{
	int i, j, k, c, d;
	int temporal = 0;
	int **resultado = (int **)malloc(sizeof(int *) * 3);

	for (i = 0; i < 3; ++i)
	{
		resultado[i] = (int *)malloc(sizeof(int) * 3);
		for (j = 0; j < 3; ++j)
		{
			resultado[i][j] = 0;
		}
	}

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			for (k = 0; k < 3; k++)
			{
				resultado[i][j] += mtx1[i][k] * mtx2[k][j];
			}
		}
	}

	return resultado;
}

int sumarMatriz(int **matriz)
{
	int i, j, acumulador;
	acumulador = 0;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			acumulador += matriz[i][j];
		}
	}
	acumulador = acumulador / 9;
	return acumulador;
}

int **obtenerMatriz(int **m, int filas, int columnas, int x, int y)
{
	int i, j;
	int **posicion = (int **)malloc(sizeof(int *) * 3);
	for (i = 0; i < 3; i++)
	{
		posicion[i] = (int *)malloc(sizeof(int) * 3);
	}

	posicion[0][0] = m[x][y];
	posicion[0][1] = m[x][y + 1];
	posicion[0][2] = m[x][y + 2];

	posicion[1][0] = m[x + 1][y];
	posicion[1][1] = m[x + 1][y + 1];
	posicion[1][2] = m[x + 1][y + 2];

	posicion[2][0] = m[x + 2][y];
	posicion[2][1] = m[x + 2][y + 1];
	posicion[2][2] = m[x + 2][y + 2];

	return posicion;
}

int convolucion(int **matriz1, int **matriz2, int filas, int columnas, int x, int y)
{
	int **miniImagen = obtenerMatriz(matriz1, filas, columnas, x, y);

	int **matrizConv = matrices(miniImagen, matriz2);

	int conv = sumarMatriz(matrizConv);

	return conv;
}

int **matrizConvolucion(int **matriz1, int **matriz2, int filas, int columnas)
{
	int filaAux = filas - 2;
	int columnaAux = columnas - 2;
	int i, j;
	int **mtxConv = (int **)malloc(sizeof(int *) * filaAux);
	int conv = 0;
	for (i = 0; i < filaAux; i++)
	{
		mtxConv[i] = (int *)malloc(sizeof(int) * columnaAux);
		for (j = 0; j < columnaAux; j++)
		{
			conv = convolucion(matriz1, matriz2, filas, columnas, i, j);
			mtxConv[i][j] = conv;
		}
	}
	return mtxConv;
}

int **normalizarMatriz(int **matrizConv, int filas, int columnas)
{
	int i, j;
	for (i = 0; i < filas - 2; i++)
	{
		for (j = 0; j < columnas - 2; j++)
		{
			if (matrizConv[i][j] < 0)
			{
				matrizConv[i][j] = 0;
			}
			else
			{
				matrizConv[i][j] = matrizConv[i][j];
			}
		}
	}

	return matrizConv;
}

// Segunda etapa del pipeline
int main(int argc, char *argv[])
{
	// Nombre del archivo con la mascara
	char *archivoMascara = argv[1];

	// Creacion de pipe convolucion->normalizacion
	int tuberia[2];
	pipe(tuberia);

	// Creacion de proceso
	pid_t pid = fork(); // Se crea el hijo

	if (pid < 0) // No se creo el hijo
	{
		perror("Fallo en el fork\n");
		exit(1);
	}
	else if (pid == 0) // Soy el hijo
	{
		// Se conecta la STDIN del hijo con el read del pipe
		dup2(tuberia[0], STDIN_FILENO);
		close(tuberia[1]);
		close(tuberia[0]);

		// Se realiza un EXEC para reemplazar este proceso con la tercera etapa del pipeline
		char *args[] = {"normalizacion.out", argv[1], argv[3], argv[4], NULL};
		execvp("src/pipeline/normalizacion.out", args);
	}
	else // Soy el padre
	{
		// Cantidad de imagenes a procesar
		int cantImagenes = atoi(argv[1]);

		// Nombre del archivo de la mascara
		char *archivoMascara = argv[2];

		// Se conecta el STDOUT del padre con el write del pipe
		dup2(tuberia[1], STDOUT_FILENO);
		close(tuberia[0]);
		close(tuberia[1]);

		int verif = 0;
		while (verif < cantImagenes)
		{
			int dimensiones[2]; // [alto][ancho]
			read(STDIN_FILENO, dimensiones, 2 * sizeof(int));

			int matriz[dimensiones[0]][dimensiones[1]];
			read(STDIN_FILENO, matriz, dimensiones[0] * dimensiones[1] * sizeof(int));

			int a = obtenerCantLineas(archivoMascara);
			char **matriz1 = extraerLineas(archivoMascara, a);

			int **mtxMascara = crearMatrizMascara(matriz1, a);

			int i, j;
			int **mtx = (int **)malloc(sizeof(int *) * dimensiones[0]);
			for (i = 0; i < dimensiones[0]; i++)
			{
				mtx[i] = (int *)malloc(sizeof(int) * dimensiones[1]);
				for (j = 0; j < dimensiones[1]; j++)
				{
					mtx[i][j] = matriz[i][j];
				}
			}

			int **matrizConv = matrizConvolucion(mtx, mtxMascara, dimensiones[0], dimensiones[1]);

			int dimFila = dimensiones[0] - 2;
			int dimColumna = dimensiones[1] - 2;

			int matrizNueva[dimColumna][dimFila];

			for (i = 0; i < dimColumna; i++)
			{
				for (j = 0; j < dimFila; j++)
				{
					matrizNueva[i][j] = matrizConv[i][j];
				}
			}

			int dimNuevo[2];

			dimNuevo[0] = dimColumna;
			dimNuevo[1] = dimFila;

			// Envio de la matriz por el pipe
			write(STDOUT_FILENO, dimNuevo, 2 * sizeof(int));
			write(STDOUT_FILENO, matrizNueva, dimFila * dimColumna * sizeof(int));
			verif++;
		}
	}
	wait(NULL);
	return 0;
}