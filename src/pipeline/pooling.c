#include "../../incl/cabeceras.h"


int** obtenerMtx(int** m, int filas, int columnas, int x, int y){
	int i, j;
	int** posicion = (int**)malloc(sizeof(int*)*3);
	for ( i = 0; i < 3; i++)
	{
		posicion[i] = (int*)malloc(sizeof(int)*3);
	}
	/*
	for (i = 0; i < filas; i++)
	{
		for (j = 0; j < columnas; j++)
		{
			printf("%d ", m[i][j]);
		}
		printf("\n");
	}*/

	posicion[0][0] = m[x][y];
	posicion[0][1] = m[x][y+1];
	posicion[0][2] = m[x][y+2];

	posicion[1][0] = m[x+1][y];
	posicion[1][1] = m[x+1][y+1];
	posicion[1][2] = m[x+1][y+2];

	posicion[2][0] = m[x+2][y];
	posicion[2][1] = m[x+2][y+1];
	posicion[2][2] = m[x+2][y+2];

	/*for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			printf("%d ", posicion[i][j]);
		}
		printf("\n");
	}*/
	return posicion;
	
}


int* matrizPooling(int** matriz){
    int* mtx = (int*)malloc(sizeof(int*)*9);
    mtx[0] = matriz[0][0];
    mtx[1] = matriz[0][1];
    mtx[2] = matriz[0][2];
     
    mtx[3] = matriz[1][0];
    mtx[4] = matriz[1][1];
    mtx[5] = matriz[1][2];

    mtx[6] = matriz[2][0];
    mtx[7] = matriz[2][1];
    mtx[8] = matriz[2][2];
    return mtx;
}

int buscarMayor(int* arreglo){
    int mayor = 0;
    int i, j;
    for (i = 0; i < 9; i++)
    {
        if (arreglo[i]>mayor)
        {
            mayor = arreglo[i];
        }
    }
    return mayor;
}

int pooling(int** matriz1, int filas, int columnas, int x, int y){
	
    int** miniImagen = obtenerMtx(matriz1, filas, columnas, x, y);

	int* arregloPooling = matrizPooling(miniImagen);

	int datoPooling = buscarMayor(arregloPooling);

	return datoPooling;
}


int** generarPooling(int** matriz1, int filas, int columnas){
	int filaAux = filas - 2;
	int columnaAux = columnas - 2;
	int i, j;
	int** mtxPooling = (int**)malloc(sizeof(int*)*filaAux);
	int pool = 0;
	printf("La matriz convolucion es la siguiente: \n");
	for ( i = 0; i < filaAux; i++)
	{
		mtxPooling[i] = (int*)malloc(sizeof(int)*columnaAux);
		for (j = 0; j < columnaAux; j++)
		{
			pool = pooling(matriz1, filas, columnas, i, j);
            mtxPooling[i][j] = pool;
			//printf("%2d ", mtxConv[i][j]);
		}
		//printf("\n");
		
	}

	return mtxPooling;
	
}


// Cuarta etapa del pipeline
int main(int argc, char *argv[])
{
    // Creacion de pipe pooling->umbral
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

        // Se realiza un EXEC para reemplazar este proceso con la quinta etapa del pipeline
        char *args[] = {"umbral.out", argv[1], argv[2], NULL};
        execvp("src/pipeline/umbral.out", args);
    }
    else // Soy el padre
    {
        // Se conecta el STDOUT del padre con el write del pipe
        dup2(tuberia[1], STDOUT_FILENO);
        close(tuberia[0]);
        close(tuberia[1]);

        int dimensiones[2]; // [alto][ancho]
        read(STDIN_FILENO, dimensiones, 2 * sizeof(int));

        int matriz[dimensiones[0]][dimensiones[1]];
        read(STDIN_FILENO, matriz, dimensiones[0] * dimensiones[1] * sizeof(int));

        /* De aqui en adelante ya se puede trabajar sobre la matriz */
        int nuevoAlto, nuevoAncho, altoPool, anchoPool;

        altoPool = 3;  // Dimensiones de la mascara de pooling.
        anchoPool = 3; // Se pueden cambiar.

        nuevoAlto = dimensiones[0] / altoPool;
        nuevoAncho = dimensiones[1] / anchoPool;

        int nuevasDimensiones[2]; // Dimensiones de la matriz nueva
        nuevasDimensiones[0] = nuevoAlto;
        nuevasDimensiones[1] = nuevoAncho;

        int i, j;
        int** mtx = (int**)malloc(sizeof(int*)*dimensiones[0]);
        for (i = 0; i < dimensiones[0]; i++)
        {
            mtx[i] = (int*)malloc(sizeof(int)*dimensiones[1]); 
            for ( j = 0; j < dimensiones[1]; j++)
            {
                mtx[i][j] = matriz[i][j];
            }
        }
        
        int dimFila = dimensiones[0]-2;
        int dimColumna = dimensiones[1]-2;

        int** mtxPooling =  generarPooling(mtx, dimensiones[0],dimensiones[1]);

        int matrizNueva[dimColumna][dimFila];

        for (i = 0; i < dimColumna; i++)
        {
            for (j = 0; j < dimFila; j++)
            {
                matrizNueva[i][j] = mtxPooling[i][j];
            } 
        }

        int nuevasDimensiones[2];

        nuevasDimensiones[0] = dimColumna;
        nuevasDimensiones[1] = dimFila;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

        // Envio de la matriz por el pipe
        write(STDOUT_FILENO, nuevasDimensiones, 2 * sizeof(int));
        write(STDOUT_FILENO, matrizNueva, dimColumna* dimFila * sizeof(int));
        wait(NULL);
    }

    return 0;
}