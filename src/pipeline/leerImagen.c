#include "../../incl/cabeceras.h"

// Primera etapa del pipeline
int main(int argc, char *argv[])
{
    // Creacion de pipe leerImagen->convolucion
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

        // Se realiza un EXEC para reemplazar este proceso con la segunda etapa del pipeline
        char *args[] = {"convolucion.out", argv[2], argv[3], argv[4], NULL};
        execvp("src/pipeline/convolucion.out", args);
    }
    else // Soy el padre
    {
        // Cantidad de imagenes a procesar
        int cantImagenes = atoi(argv[1]);

        // Se conecta el STDOUT del padre con el write del pipe
        dup2(tuberia[1], STDOUT_FILENO);
        close(tuberia[0]);
        close(tuberia[1]);

        // Proceso de lectura de la imagen
        FILE *fp;
        png_structp pngPtr;
        png_infop infoPtr;
        png_uint_32 ancho;
        png_uint_32 alto;
        png_bytepp filas;
        png_bytep fila;
        png_byte pixel;

        char *nombre = "imagen.png";
        int i, j;

        fp = fopen(nombre, "rb");
        pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        infoPtr = png_create_info_struct(pngPtr);

        png_init_io(pngPtr, fp);
        png_read_png(pngPtr, infoPtr, 0, 0);
        png_get_IHDR(pngPtr, infoPtr, &ancho, &alto, NULL, NULL, NULL, NULL, NULL);

        int matriz[alto][ancho];
        int dimensiones[2];
        
        dimensiones[0] = alto;
        dimensiones[1] = ancho;

        filas = png_get_rows(pngPtr, infoPtr);
        for (i = 0; i < alto; i++)
        {
            fila = filas[i];
            for (j = 0; j < ancho; j++)
            {
                pixel = fila[j];
                matriz[i][j] = pixel;
            }
        }

        // Envio de la matriz por el pipe
        write(STDOUT_FILENO, dimensiones, 2*sizeof(int));
        write(STDOUT_FILENO, matriz, alto * ancho * sizeof(int));
        wait(NULL);
    }

    return 0;
}