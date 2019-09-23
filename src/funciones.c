#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../incl/funciones.h"


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
    FILE *fp;
	int i=0; 	
 	char buffer[100];
 	fp = fopen (nombre, "r");
    for (i = 0; i < lineas; i++)
    {
		palabra[i]=(char*)malloc(sizeof(char)*20);
        fgets(buffer, 30,fp);
        palabra[i] = buffer;
     	//printf("%s",buffer);
    }
 	fclose ( fp );
    printf("\n------Fin de la lectura de la imagen.----\n");
	return palabra;
}


void quitarEspacios(char frase[]){
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
        printf("%c ", linea[i]);		
	}
}





