/*
--------------------------------------------------
Robert Josue Huanca Clares
DAT - 241

Problema 5. Realizar en MPI la multiplicación de 
una matriz NxN, con un vector de dimensión N.
--------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 1000

void multiplicacion_mat_vec(int mat[N][N], int vec[N], int res[N], int procesador, int procesadores) {
    int local_res[N] = {0};

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            local_res[i] += mat[i][j] * vec[j];
        }
    }
    // Recopilar los resultados locales de cada proceso en el proceso raíz
    MPI_Gather(local_res, N, MPI_INT, res, N, MPI_INT, 0, MPI_COMM_WORLD);
}

int main(int argc, char *argv[]) {

    double tinicial, tfinal;
    tinicial = MPI_Wtime();
    
    int procesador, procesadores;
    int mat[N][N];
    int vec[N];
    int res[N];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &procesador);
    MPI_Comm_size(MPI_COMM_WORLD, &procesadores);

    // Solo el proceso raíz inicializa la matriz y el vector
    if (procesador == 0) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                mat[i][j] = i + j;  // Usando esto como ejemplo
            }
            vec[i] = i; // Usando esto como ejemplo
        }
    }

    // Multiplicación de la matriz por el vector
    multiplicacion_mat_vec(mat, vec, res, procesador, procesadores);
    
    tfinal = MPI_Wtime();
    
    // Imprimimos los resultados en el proceso raíz
    if (procesador == 0) {
    	printf("Procesadores: %d \nN: %d \nTiempo: %f segundos\n", procesadores, N, tfinal - tinicial);
        /*printf("\nMultiplicación:\n");
        for (int i = 0; i < N; i++) {
            printf("%d ", res[i]);
        }
        printf("\n");*/
    }

    MPI_Finalize();

    return 0;
}

