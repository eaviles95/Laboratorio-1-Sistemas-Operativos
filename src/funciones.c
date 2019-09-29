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

int obtenerCantLineas(char *nombreArchivo){
	FILE *fichero=fopen(nombreArchivo,"r");
	int contador=0;
	char *linea=(char *)malloc(sizeof(char)*70);
	while(feof(fichero)==0){
		if(fgets(linea,70,fichero)==NULL){
			contador--;
		}
		if(linea[0]==10 || linea[0]==9){
		}
		else{
			contador++;	
		}
	}
	return contador;
}



char** extraerLineas(char *nombre,int lineas){
    char** palabra=(char**)malloc(sizeof(char*)*100);
    printf("-----Leyendo imagen %s...------\n",nombre);
	// se indica que se quiere leer el archivo para lectura.
    char linea[1024];
    FILE *fich;
 
    fich = fopen(nombre, "r");
    //Lee línea a línea y escribe en pantalla hasta el fin de fichero
	int i = 0;
    while(fgets(linea, 1024, (FILE*) fich)) {
		palabra[i] = (char*)malloc(sizeof(char));
		strcat(palabra[i],linea);
        //printf("LINEA: %s", palabra[i]);
		i=i+1;
    }
	printf("\n------Fin de la lectura de la imagen.----\n");
    fclose(fich);
	return palabra;
}


char* quitarEspacios(char frase[]){
    char* palabras;
    char* linea = (char*)malloc(sizeof(char)*3);
    int i;
    palabras=strtok(frase," ");
    linea[0] = palabras[0];
    for (i = 0; i <=strlen(frase); i++)
    {
        palabras=strtok(0," ");
        linea[i+1] = palabras[0];
    }
	for (i = 0; i < strlen(linea); i++)
	{
        //printf("%c", linea[i]);		
	}
	return linea;
}


int** crearMatrizMascara(char** matriz,int lineas){
	char** matrizAux = (char**)malloc(sizeof(char*));
	int i, j;
	int** mtx = (int**)malloc(sizeof(int*));
	for (i = 0; i < 3; i++)
	{
		matrizAux[i] = (char*)malloc(sizeof(char));
		matrizAux[i] = quitarEspacios(matriz[i]);
		//printf("%s\n", matrizAux[i]);
	}
	for ( i = 0; i < 3; i++)
	{
		mtx[i] = (int*)malloc(sizeof(int));
		for (j = 0; j < 3; j++)
		{
			//se resta '0' para obtener el valor entero del caracter
			mtx[i][j] = matrizAux[i][j] - '0';
			//printf("%d", mtx[i][j]);
		}
		//printf("\n");
	}
	i = 0;
	return mtx;
}
/*
int** mascara(char* nombreArchivo){
	int a = obtenerCantLineas(nombreArchivo);
	char** matriz = extraerLineas(nombreArchivo, a);
	int** mtxMascara = crearMatrizMascara(matriz, a);
	return mtxMascara;
}
*/

int** crearMatrizVacia(int numero)
{
	int ** matriz;
	matriz = (int**)malloc(sizeof(int*)*numero);
	
	int i;
	i = 0;
	while(i<numero)
	{
		matriz[i]= (int*)malloc(sizeof(int)*numero);
		i++;
	}

	int j;
	i =0;
	int k = 0;
	while(i<numero)
	{
		j=0;
		while(j<numero)
		{
			matriz[i][j] = k;
			j++;
			k++;
		}
		i++;
	}
	return matriz;
}

int** matrices(int** mtx1, int** mtx2){
    int i,j, k, c, d;
	int temporal = 0 ;
	int** resultado = (int**)malloc(sizeof(int*)*3);
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){

        	printf("%d ",mtx1[i][j]);
        }
		printf("\n");
    }
	printf("\n");

	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
		printf("%d ",mtx2[i][j]);
		}
		printf("\n");
	}
    printf("***LA MATRIZ PRODUCTO DE LAS 2 INDICADAS ES:\n");

	for(i=0; i<3; ++i){
		resultado[i] = (int*) malloc(sizeof(int)*3);
        for(j=0; j<3; ++j)
        {
            resultado[i][j] = 0;
        }
	}
	
	for ( i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			for (k = 0; k < 3; k++)
			{
				resultado[i][j] += mtx1[i][k]*mtx2[k][j];
			}	
		}
	}

	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
		printf("%2d ", resultado[i][j]);
		}
		printf("\n");
	}
	return resultado;
}

int sumarMatriz(int** matriz){
	int i, j, acumulador;
	acumulador =0;
	for ( i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			acumulador+= matriz[i][j];
		}
	}
	acumulador = acumulador/9;
	printf("%d", acumulador);
	return acumulador;
}

int** obtenerMatriz(int** m, int filas, int columnas, int x, int y){
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

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			printf("%d ", posicion[i][j]);
		}
		printf("\n");
	}
	return posicion;
	
}


int convolucion(int** matriz1, int** matriz2, int filas, int columnas, int x, int y){
	int** miniImagen = obtenerMatriz(matriz1, filas, columnas, x, y);

	int** matrizConv = matrices(matriz1, matriz2);

	int conv = sumarMatriz(matrizConv);

	return conv;


}


