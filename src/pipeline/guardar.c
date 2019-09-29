#include "../../incl/cabeceras.h"

// Sexta etapa del pipeline
int main(int argc, char *argv[])
{
    int resultadoUmbral;
    read(STDIN_FILENO, &resultadoUmbral, sizeof(int));

    int dimensiones[2];
    read(STDIN_FILENO, dimensiones, 2 * sizeof(int));

    int matriz[dimensiones[0]][dimensiones[1]];
    read(STDIN_FILENO, matriz, dimensiones[0] * dimensiones[1] * sizeof(int));

    FILE *nuevaIMG = fopen("salida.ppm", "wb");
    fprintf(nuevaIMG, "P6\n%i %i 255\n", dimensiones[1], dimensiones[0]);
    int i, j;
    for (i = 0; i < dimensiones[0]; i++)
    {
        for (j = 0; j < dimensiones[1]; j++)
        {
            fputc(matriz[i][j], nuevaIMG);
            fputc(matriz[i][j], nuevaIMG);
            fputc(matriz[i][j], nuevaIMG);
        }
    }
    fclose(nuevaIMG);

    if (argv[1] != NULL)
    {
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
    }

    return 0;
}