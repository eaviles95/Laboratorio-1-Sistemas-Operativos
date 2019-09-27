#ifndef FUNCIONES_H
#define FUNCIONES_H

void usoArgumentos();

int obtenerCantLineas(char *nombreArchivo);

char** extraerLineas(char *nombre,int lineas);

char* quitarEspacios(char frase[]);

int** crearMatrizMascara(char** matriz,int lineas);
int** matrices(int** mtx1, int** mtx2);
int** crearMatrizVacia(int numero);
#endif
