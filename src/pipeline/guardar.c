#include "../../incl/cabeceras.h"

// Sexta etapa del pipeline
int main(int argc, char *argv[])
{
    // Cantidad de imagenes a procesar
    int cantImagenes = atoi(argv[1]);

    printf("Resultado del umbral de negro.\nEsta la imagen por sobre el umbral?\n");

    int img = 1;
    char nombreSalida[15];
    char nombreIMG[15];
    while (img <= cantImagenes)
    {
        int resultadoUmbral;
        read(STDIN_FILENO, &resultadoUmbral, sizeof(int));

        int dimensiones[2];
        read(STDIN_FILENO, dimensiones, 2 * sizeof(int));

        int matriz[dimensiones[0]][dimensiones[1]];
        read(STDIN_FILENO, matriz, dimensiones[0] * dimensiones[1] * sizeof(int));

        sprintf(nombreSalida, "salida%i.png", img);

        FILE *nuevaIMG = fopen(nombreSalida, "wb");
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

        if (argv[2] != NULL)
        {
            sprintf(nombreIMG, "imagen %d", img);
            printf("%s\t->\t", nombreIMG);
            if (resultadoUmbral == 0)
            {
                printf("no\n");
            }
            else
            {
                printf("si\n");
            }
        }
        img++;
    }
    return 0;
}