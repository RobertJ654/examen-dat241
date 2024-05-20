/*
--------------------------------------------------
Robert Josue Huanca Clares
DAT - 241

Problema 9. Genere la serie 2, 4, 6, 8, 10, 12, 
14, 16, 18… en M vectores(procesadores) para N 
términos con MPI.
--------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {

    long long N = 1E9; // Total número de elementos
    int M; // Número de procesadores

    int proceso, procesadores;
    double tinicial, tfinal;

    // Iniciamos MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &proceso);
    MPI_Comm_size(MPI_COMM_WORLD, &procesadores);

    M = procesadores;
    tinicial = MPI_Wtime();

    // Cada proceso calculará un segmento del arreglo
    long long local_N = N / M;
    long long inicio = proceso * local_N;
    long long fin = inicio + local_N;

    // Utilizamos MALLOC para asignar memoria dinámica para el arreglo
    int *serie_local = (int*)malloc(local_N * sizeof(int));
    if (serie_local == NULL) {
        printf("No se pudo asignar memoria.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    int *serie = NULL;
    if (proceso == 0) {
        serie = (int*)malloc(N * sizeof(int));
        if (serie == NULL) {
            printf("No se pudo asignar memoria.\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    }


    // Calculamos y almacenamos los términos de la serie en cada proceso
    for (long long i = 0; i < local_N; i++) {
        serie_local[i] = 2 * (inicio + i + 1);
    }


    // Recolectamos los segmentos locales en el proceso raíz
    MPI_Gather(serie_local, local_N, MPI_INT, serie, local_N, MPI_INT, 0, MPI_COMM_WORLD);

    // Medimos el tiempo final y liberamos la memoria
    tfinal = MPI_Wtime();
    free(serie_local);
    
    // Para imprimir la serie generada  
    if (proceso == 0) {
        printf("M (procesadores): %d \nN: %d \nTiempo: %f segundos\n", M, N, tfinal - tinicial);
        /*
        printf("Serie: ");
        for (long long i = 0; i < N; i++) {
            printf("%d ", serie[i]);
        }
        printf("\n");
        */
        free(serie);
    }

    // Finalizamos MPI
    MPI_Finalize();

    return 0;
}

