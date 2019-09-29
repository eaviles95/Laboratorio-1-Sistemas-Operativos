#include "../../incl/cabeceras.h"

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
        //dup2(tuberia[1], STDOUT_FILENO);
        close(tuberia[0]);
        close(tuberia[1]);

        int dimensiones[2]; // [alto][ancho]
        read(STDIN_FILENO, dimensiones, 2 * sizeof(int));

        int matriz[dimensiones[0]][dimensiones[1]];
        read(STDIN_FILENO, matriz, dimensiones[0] * dimensiones[1] * sizeof(int));


        int a, b;
        for (a = 0; a < dimensiones[0]; a++)
        {
            for (b = 0; b < dimensiones[1]; b++)
            {
                printf("%d ", matriz[a][b]);
            }
            printf("\n");
        }

        
        /* De aqui en adelante ya se puede trabajar sobre la matriz */
        /*
        int nuevoAlto, nuevoAncho, altoPool, anchoPool;

        altoPool = 3;  // Dimensiones de la mascara de pooling.
        anchoPool = 3; // Se pueden cambiar.

        nuevoAlto = dimensiones[0] / altoPool;
        nuevoAncho = dimensiones[1] / anchoPool;

        int nuevasDimensiones[2]; // Dimensiones de la matriz nueva
        nuevasDimensiones[0] = nuevoAlto;
        nuevasDimensiones[1] = nuevoAncho;

        int nuevaMatriz[nuevoAlto][nuevoAncho]; // Matriz con el resultado del pooling

        // Proceso de pooling
        int i, j, k, l, mayorValor;
        int contAlto = 0;
        int contAncho = 0;
        for (i = 0; i < altoPool; i++)
        {
            for (j = 0; j < anchoPool; j++)
            {
                // Se encuentra el mayor valor dentro del pedazo extraido y se guarda
                mayorValor = 0;
                for (k = contAlto; k < contAlto + altoPool; k++)
                {
                    for (l = contAncho; l < contAncho + anchoPool; l++)
                    {
                        if (matriz[k][l] > mayorValor)
                        {
                            mayorValor = matriz[k][l];
                        }
                    }
                }
                nuevaMatriz[i][j] = mayorValor;
                contAncho += 3;
            }
            contAlto += 3;
            contAncho = 0;
        }
        */
        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

        // Envio de la matriz por el pipe
        //write(STDOUT_FILENO, nuevasDimensiones, 2 * sizeof(int));
        //write(STDOUT_FILENO, nuevaMatriz, nuevoAlto * nuevoAncho * sizeof(int));
        wait(NULL);
    }

    return 0;
}