#include "../../incl/cabeceras.h"

// Segunda etapa del pipeline
int main(int argc, char *argv[])
{
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
        char *args[] = {"normalizacion.out", NULL};
        execvp("src/pipeline/normalizacion.out", args);
    }
    else // Soy el padre
    {
        // Se conecta el STDOUT del padre con el write del pipe
        dup2(tuberia[1], STDOUT_FILENO);
        close(tuberia[0]);
        close(tuberia[1]);

        int dimensiones[2]; // [alto][ancho]
        read(STDIN_FILENO, dimensiones, 2*sizeof(int));

        int matriz[dimensiones[0]][dimensiones[1]];
        read(STDIN_FILENO, matriz, dimensiones[0] * dimensiones[1] * sizeof(int));
        
        /* De aqui en adelante ya se puede trabajar sobre la matriz */



        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

        // Envio de la matriz por el pipe
        write(STDOUT_FILENO, dimensiones, 2*sizeof(int));
        write(STDOUT_FILENO, matriz, dimensiones[0] * dimensiones[1] * sizeof(int));
        wait(NULL);
    }


    return 0;
}