#include "../../incl/cabeceras.h"

// Sexta etapa del pipeline
int main(int argc, char *argv[])
{
    int resultadoUmbral;
    read(STDIN_FILENO, &resultadoUmbral, sizeof(int));
    
    char *nombre = "imagen";

    printf("Resultados. Es la imagen cercana a negro?\n");
    printf("Imagen\t->\t");
    if (resultadoUmbral == 0)
    {
        printf("no\n");
    }
    else
    {
        printf("si\n");
    }

    return 0;
}