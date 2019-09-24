#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "../../incl/pipeline/normalizacion.h"

// Tercera etapa del pipeline
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
        char *args[] = {"pooling.out", NULL};
        execvp("src/pipeline/pooling.out", args);
    }
    else
    {
        printf("soy normalizacion\n");
    }

    return 0;
}