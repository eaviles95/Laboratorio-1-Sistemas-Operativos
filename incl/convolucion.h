#ifndef CONVOLUCION_H
#define CONVOLUCION_H

//Entradas: Un arreglo de tipo char con el nombre del archivo a leer.
//Funcionamiento: Función que lee un archivo de texto y cuenta la cantidad de líneas.
//Salidas: Un entero que representa la cantidad de líneas que tiene un archivo de texto.
int obtenerCantLineas(char *nombreArchivo);

//Entradas: Un arreglo de tipo char con el nombre del archivo a leer, un entero que representa la cantidad de líneas de un archivo de texto.
//Funcionamiento: Función que genera un arreglo de char** con lo leído del archivo de texto.
//Salidas: Arreglo char** con lo leído del archivo de texto.
char** extraerLineas(char *nombre,int lineas);

//Entradas: Un arreglo  char que contiene espacios.
//Funcionamiento: Función que quita los espacios de un arreglo.
//Salidas: Un arreglo char* sin espacios.
char* quitarEspacios(char frase[]);

//Entradas: Un arreglo char** que representa lo leído en el archivo de texto como máscara y un int que representa la cantidad de líneas del archivo de texto.
//Funcionamiento: Función que crea un arreglo int** con la máscara leída del archivo de texto que es recibido por un char**.
//Salidas: Un arreglo int** con la máscara leída del archivo de texto.
int** crearMatrizMascara(char** matriz,int lineas);

//Entradas: Un arreglo int** que representa un trozo de la matriz de la imagen y otro arreglo int** que representa la máscara.
//Funcionamiento: Función que multiplica dos matrices de 3x3.
//Salidas: Un arreglo int** con el resultado de la multiplicación de dos matrices de 3x3.
int** matrices(int** mtx1, int** mtx2);

//Entradas: Un arreglo int** que representa el resultado de la multiplicación de dos matrices de 3x3.
//Funcionamiento: Función que suma todos los elementos de una matriz.
//Salidas: Un int que representa la suma de todos los elementos de una matriz.
int sumarMatriz(int** matriz);

//Entradas: Un arreglo int** que representa una matriz que contiene una imagen, dos int que representan las filas y las columnas de la matriz nombrada. Finalmente, dos int x e y que representan coordenadas.
//Funcionamiento: Función que obtiene una matriz de 3x3, dependiendo de las coordenadas x e y que se le asignen.
//Salidas: Un arreglo int** que contiene una matriz de 3x3.
int** obtenerMatriz(int** m, int filas, int columnas, int x, int y);

//Entradas: Un arreglo int** que representa un trozo de la matriz de la imagen y otro arreglo int** que representa la máscara, dos int que representan las filas y las columnas de la matriz nombrada. Finalmente, dos int x e y que representan coordenadas.
//Funcionamiento: Función que aplica la convolución para una porción de la imagen.
//Salidas: Un int que representa el resultado de la convolución.
int convolucion(int** matriz1, int** matriz2, int filas, int columnas, int x, int y);

//Entradas: Un arreglo int** que representa la matriz de la imagen y otro arreglo int** que representa la máscara, dos int que representan las filas y las columnas de la matriz nombrada.
//Funcionamiento: Función que ocupa la función convolucion() iterativamente para aplicar convolución en toda la matriz de la imagen.
//Salidas: Un arreglo int** con la matriz de convolución.
int** matrizConvolucion(int** matriz1, int** matriz2, int filas, int columnas);

//Entradas: Un arreglo int** que representa la matriz de convolución.
//Funcionamiento: Función que normaliza la matriz de convolución, si sus números son negativos, los reemplaza por un 0.
//Salidas: Un arreglo int** con la matriz normalizada.
int** normalizarMatriz(int** matrizConv, int filas, int columnas);

#endif