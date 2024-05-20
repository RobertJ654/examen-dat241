/*
--------------------------------------------------
Robert Josue Huanca Clares
DAT - 241

Problema 3. En openMP realice la multiplicación y 
división en base a sumas y restas.
--------------------------------------------------
*/

#include <stdio.h>
#include <omp.h>

int det_signo(int a, int b) {
	int signo = (a > 0 && b > 0) || (a < 0 && b < 0) ? 1 : -1;
}

int multiplicacion_omp(int a, int b) {
	// Valor absoluto y signo
    int signo = det_signo(a, b);
	a = (a < 0) ? -a : a;
    b = (b < 0) ? -b : b;
    // Proceso paralelo para la multiplicación por sumas
	int multi = 0;
    #pragma omp parallel for reduction(+:multi)
    for (int i = 0; i < b; i++) {
        multi = multi + a;
    }
    return multi * signo;
}

int division_omp(int a, int b) {
	// Valor absoluto y signo + excepción
    int signo = det_signo(a, b);
	a = (a < 0) ? -a : a;
    b = (b < 0) ? -b : b;
	if (b == 0) {
        printf("División sobre 0\n");
        return 0;
    }
    // Proceso paralelo para la división por restas
	int cociente = 0;
	#pragma omp parallel for reduction(-:a)
    for (int i = a; i >= b; i -= b) {
        cociente++;
        a -= b;
    }
    return cociente * signo;
}

int main() {
    int a, b;
    
    printf("a: ");
    scanf("%d", &a);
    printf("b: ");
    scanf("%d", &b);

    printf("Multiplicación: %d\n", multiplicacion_omp(a, b));
    printf("División: %d\n", division_omp(a, b));
    
    return 0;
}
