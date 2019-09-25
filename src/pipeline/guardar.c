#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "../../incl/pipeline/guardar.h"

// Sexta etapa del pipeline
int main(int argc, char *argv[])
{
    // Mensaje de prueba del pipe
    char leer[100];
    read(STDIN_FILENO, leer, 100);
    strcat(leer, "!!!");

    printf("%s\n", leer);

    return 0;
}