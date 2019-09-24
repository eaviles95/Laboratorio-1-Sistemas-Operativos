#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "../../incl/pipeline/convolucion.h"

// Segunda etapa del pipeline
int main(int argc, char *argv[])
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Fallo en el fork\n");
        exit(1);
    }
    else if (pid == 0)
    {
        // Se realiza un EXEC para reemplazar este proceso con la primera etapa del pipeline
        char *args[] = {"normalizacion.out", NULL};
        execvp("src/pipeline/normalizacion.out", args);
    }
    else
    {
        printf("soy convolucion\n");
    }

    return 0;
}