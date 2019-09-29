#ifndef CONVOLUCION_H
#define CONVOLUCION_H


int obtenerCantLineas(char *nombreArchivo);

char** extraerLineas(char *nombre,int lineas);

char* quitarEspacios(char frase[]);

int** crearMatrizMascara(char** matriz,int lineas);

int** matrices(int** mtx1, int** mtx2);

int sumarMatriz(int** matriz);

int** obtenerMatriz(int** m, int filas, int columnas, int x, int y);

int convolucion(int** matriz1, int** matriz2, int filas, int columnas, int x, int y);

int** matrizConvolucion(int** matriz1, int** matriz2, int filas, int columnas);

int** normalizarMatriz(int** matrizConv, int filas, int columnas);

#endif