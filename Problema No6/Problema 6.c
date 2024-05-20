/*
--------------------------------------------------
Robert Josue Huanca Clares
DAT - 241

Problema 6. En MPI realizar el cálculo de PI.
--------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {

    double tinicial, tfinal;
    int proceso, procesadores;
    
    int n = 1E9;
    double h = 1.0 / (double)n;
    double sum = 0.0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &proceso);
    MPI_Comm_size(MPI_COMM_WORLD, &procesadores);

    tinicial = MPI_Wtime();

    // Cada proceso calcula su parte de la suma
    double suma_local = 0.0;
    for (int i = proceso + 1; i <= n; i += procesadores) {
        double x = h * ((double)i - 0.5);
        suma_local += (4.0 / (1.0 + x * x));
    }

    // Reduce todas las sumas locales en el proceso raíz
    MPI_Reduce(&suma_local, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    tfinal = MPI_Wtime();

    if (proceso == 0) {
        double pi = sum * h;
        printf("Procesadores: %d \nTiempo: %f segundos \nPI: %f\n", procesadores, tfinal-tinicial, pi);
    }

    MPI_Finalize();
    return 0;
}

