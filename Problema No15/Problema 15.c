/*
--------------------------------------------------
Robert Josue Huanca Clares
DAT - 241

Problema 15. Despliegue “hola mundo” en la 
librería de su gusto.
--------------------------------------------------
*/

#include <stdio.h>
#include <omp.h>

int main() {

	int M = omp_get_max_threads();
	
    #pragma omp parallel num_threads(M)
    {
    printf("hola mundo\n");
    }
    
    return 0;
}

