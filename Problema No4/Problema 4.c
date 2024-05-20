/*
--------------------------------------------------
Robert Josue Huanca Clares
DAT - 241

Problema 4. Realizar en OPENMP la multiplicación 
de una matriz NxN, con un vector de dimensión N.
--------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    long long N = 1E4; // La asignación de memoria solo funciona hasta aquí o 45000 = 30 seg pero < 1E5
    int M = omp_get_max_threads();
    
    // Reservamos memoria para la matriz y el vector
    int *mat = (int*)malloc(N * N * sizeof(int));
    int *vec = (int*)malloc(N * sizeof(int));
    int *res = (int*)malloc(N * sizeof(int));
    if (mat == NULL || vec == NULL || res == NULL) {
        fprintf(stderr, "No se pudo reservar memoria para N=%d\n", N);
        return 1;
    }
    
    // Medimos tiempo de inicio
    double tinicial, tfinal;
    tinicial = omp_get_wtime();
    
    
    // Inicializamos la matriz y el vector
    #pragma omp parallel for
    for (long long i = 0; i < N; i++) {
        for (long long j = 0; j < N; j++) {
            mat[i * N + j] = i + j;  // Usando esto como ejemplo
        }
        vec[i] = i; // Usando esto como ejemplo
    }
    
    // Se hace la multiplicación
    #pragma omp parallel for
    for (long long i = 0; i < N; i++) {
        long long s = 0;
        for (long long j = 0; j < N; j++) {
            s += mat[i * N + j] * vec[j];
        }
        res[i] = s;
    }


    // Medimos el tiempo final
    tfinal = omp_get_wtime();  
    printf("Procesadores: %d \nN: %lld \nTiempo: %f segundos\n", M, N, tfinal - tinicial);
    
    /*// Imprimimos la matriz resultante
    printf("\nMultiplicación:\n");
    for (long long i = 0; i < N; i++) {
        printf("%d ", res[i]);
    }
    printf("\n");*/

    // Liberamos la memoria
    free(mat);
    free(vec);
    free(res);

    return 0;
}

