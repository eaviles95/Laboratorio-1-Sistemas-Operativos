#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include "../../incl/pipeline/leerImagen.h"

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
        char *args[] = {"convolucion.out", NULL};
        execvp("src/pipeline/convolucion.out", args);
    }
    else // Soy el padre
    {
        // Se conecta el STDOUT del padre con el write del pipe
        dup2(tuberia[1], STDOUT_FILENO);
        close(tuberia[0]);
        close(tuberia[1]);

        // Mensaje de prueba del pipe
        write(STDOUT_FILENO, "Este", 5);
        wait(NULL);
    }

    return 0;
}