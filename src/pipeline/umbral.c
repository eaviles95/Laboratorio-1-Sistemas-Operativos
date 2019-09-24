#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "../../incl/pipeline/umbral.h"

// Quinta etapa del pipeline
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
        char *args[] = {"guardar.out", NULL};
        execvp("src/pipeline/guardar.out", args);
    }
    else
    {
        printf("soy umbral\n");
    }

    return 0;
}