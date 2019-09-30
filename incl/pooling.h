#ifndef POOLING_H
#define POOLING_H

//Entradas: Un arreglo int** que representa una matriz que contiene una matriz normalizada, dos int que representan las filas y las columnas de la matriz nombrada. Finalmente, dos int x e y que representan coordenadas.
//Funcionamiento: Función que obtiene una matriz de 3x3, dependiendo de las coordenadas x e y que se le asignen.
//Salidas: Un arreglo int** que contiene una matriz de 3x3.
int** obtenerMtx(int** m, int filas, int columnas, int x, int y);

//Entradas: Un arreglo int** que contiene una matriz de 3x3 que representa un trozo de la matriz normalizada.
//Funcionamiento: Función que genera un arreglo int* que contiene 9 números de una matriz.
//Salidas: Un arreglo int* que contiene 9 números de una matriz.
int* matrizPooling(int** matriz);

//Entradas: Un arreglo de 9 números de una matriz.
//Funcionamiento: Función que encuentra el mayor elemento de un arreglo.
//Salidas: Un int con el mayor elemento de un arreglo int*.
int buscarMayor(int* arreglo);

//Entradas: Un arreglo int** que representa una matriz que contiene una matriz normalizada, dos int que representan las filas y las columnas de la matriz nombrada. Finalmente, dos int x e y que representan coordenadas. 
//Funcionamiento: Función que le aplica pooling a una porción de la matriz normalizada, dependiendo de las coordenadas x e y.
//Salidas: Un int que contiene el mayor elemento de una matriz.
int pooling(int** matriz1, int filas, int columnas, int x, int y);

//Entradas: Un arreglo int** que representa una matriz que contiene una matriz normalizada, dos int que representan las filas y las columnas de la matriz nombrada.
//Funcionamiento: Función que aplica la función pooling() iterativamente para aplicar pooling en toda la matriz normalizada.
//Salidas: Un arreglo int** con la matriz que se le aplicó pooling.
int** generarPooling(int** matriz1, int filas, int columnas);

#endif