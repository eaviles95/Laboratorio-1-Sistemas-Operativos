#include "../../incl/cabeceras.h"

// Quinta etapa del pipeline
int main(int argc, char *argv[])
{
    // Creacion de pipe umbral->guardar
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

        // Se realiza un EXEC para reemplazar este proceso con la sexta etapa del pipeline
        char *args[] = {"guardar.out", argv[2], NULL};
        execvp("src/pipeline/guardar.out", args);
    }
    else // Soy el padre
    {
        // Umbral de negrura
        int umbral = atoi(argv[1]);

        // Se conecta el STDOUT del padre con el write del pipe
        dup2(tuberia[1], STDOUT_FILENO);
        close(tuberia[0]);
        close(tuberia[1]);

        int dimensiones[2]; // [alto][ancho]
        read(STDIN_FILENO, dimensiones, 2*sizeof(int));

        int matriz[dimensiones[0]][dimensiones[1]];
        read(STDIN_FILENO, matriz, dimensiones[0] * dimensiones[1] * sizeof(int));
        
        /* De aqui en adelante ya se puede trabajar sobre la matriz */
        int i,j;
        int cercaDeNegro = 0;
        for (i = 0; i < dimensiones[0]; i++)
        {
            for (j = 0; j < dimensiones[1]; j++)
            {
                if (matriz[i][j] > 230)
                {
                    cercaDeNegro++;
                }
            }
        }
        
        int totalDePixeles = dimensiones[0] * dimensiones[1];
        int porcentajeDeNegrura = (cercaDeNegro / totalDePixeles) * 100;

        int resultado = 0;
        if (porcentajeDeNegrura >= umbral)
        {
            resultado = 1;
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

        // Envio de la matriz por el pipe
        write(STDOUT_FILENO, &resultado, sizeof(int));
        write(STDOUT_FILENO, dimensiones, 2*sizeof(int));
        write(STDOUT_FILENO, matriz, dimensiones[0] * dimensiones[1] * sizeof(int));
        wait(NULL);
    }


    return 0;
}