/*
--------------------------------------------------
Robert Josue Huanca Clares
DAT - 241

Problema 8. Genere la serie 2, 4, 6, 8, 10, 12, 
14, 16, 18… en M vectores(procesadores) para N 
términos con OPENMP.
--------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    long long N = 1E9; // Total número de elementos
    int M; // Número de procesadores

	// Inicializamos OpenMP y obtenemos el número de hilos
    M = omp_get_max_threads();

    // Medimos tiempo de inicio
    double tinicial, tfinal;
    tinicial = omp_get_wtime();

    // Utilizamos MALLOC para asignar memoria dinámica para el arreglo
    int *serie = (int*)malloc(N * sizeof(int));
    if (serie == NULL) {
        printf("No se pudo asignar memoria.\n");
        return 1;
    }

    // Definimos la región paralela con M hilos
    #pragma omp parallel num_threads(M)
    {
        // Cada hilo calculará un segmento del arreglo
        int activo = omp_get_thread_num();
        long long local_N = N / M;
        long long inicio = activo * local_N;
        long long fin = (activo == M - 1) ? N : inicio + local_N;

        // Calculamos y almacenamos los términos de la serie en cada hilo
        for (long long i = inicio; i < fin; i++) {
            serie[i] = 2 * (i + 1);
        }
    }

    // Medimos el tiempo final
    tfinal = omp_get_wtime();  
    printf("M (hilos): %d \nN: %lld \nTiempo: %f segundos\n", M, N, tfinal - tinicial);
    
    // Para imprimir la serie generada
    /*
    printf("Serie: ");
    for (long long i = 0; i < N; i++) {
        printf("%d ", serie[i]);
    }
    printf("\n");
    */

    free(serie);

    return 0;
}

