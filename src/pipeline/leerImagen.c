#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "../../incl/pipeline/leerImagen.h"

// Primera etapa del pipeline
int main(int argc, char *argv[])
{
    pid_t pid = fork(); // Se crea el hijo

    if (pid < 0) // No se creo el hijo
    {
        perror("Fallo en el fork\n");
        exit(1);
    }
    else if (pid == 0) // Soy el hijo
    {
        // Se realiza un EXEC para reemplazar este proceso con la primera etapa del pipeline
        char *args[] = {"convolucion.out", NULL};
        execvp("src/pipeline/convolucion.out", args);
    }
    else
    {
        printf("soy leer imagen\n");
    }

    return 0;
}