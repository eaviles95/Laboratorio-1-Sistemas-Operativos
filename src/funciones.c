#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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
			printf("%d", mtx[i][j]);
		}
		printf("\n");
	}
	return mtx;
}


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

	while(i<numero)
	{
		j=0;
		while(j<numero)
		{
			matriz[i][j] = 0;
			j++;
		}
		i++;
	}

	return matriz;
}



