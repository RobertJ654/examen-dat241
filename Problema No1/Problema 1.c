/*
--------------------------------------------------
Robert Josue Huanca Clares
DAT - 241

Problema 1. En C implemente las funciones básicas 
(+.-.*./); utilice punteros (Ej. Multiplicación 
en base a sumas, división en base a restas).
--------------------------------------------------
*/

#include <stdio.h>

int determinar_signo(int a, int b) {
    return (a > 0 && b > 0) || (a < 0 && b < 0) ? 1 : -1;
}

int suma(int *a, int *b) {
    return *a + *b;
}

int resta(int *a, int *b) {
    return *a - *b;
}

int multiplicacion(int *a , int *b) {
    // Determinamos el signo
    int signo = determinar_signo(*a, *b);
    // Calculamoss el resultado
    int resultado = 0;
    int i = (*b > 0) ? -(*b) : (*b);
    for (i; i < 0; i++) {
        resultado += *a;
    }
    // Arreglo final para que funcione en los 4 casos
    int final = ((*b<0 && *a>0) || (*a>0 && b>0)) ? resultado : -resultado;
    return final * signo;
}

int division(int *a, int *b) {
    // Hallamos el signo
    int signo = determinar_signo(*a, *b);
    // Mostramos la excepción
    if (*b == 0) {
        printf("División sobre 0\n");
        return 0;
    }
    // Calculamos el resultado ajustando signos
    int resultado = 0;
    int dividendo = (*a < 0) ? -(*a) : (*a); // Hacemos que sean
    int divisor = (*b < 0) ? -(*b) : (*b);  // positivos
    // Realizamos la división
    while (dividendo >= divisor) {
        resultado++;
        dividendo -= divisor;
    }
    return resultado * signo;
}

int main() {
    
    int a, b;
    printf("Introduzca el valor de a: ");
    scanf("%d", &a);
    printf("Introduzca el valor de b: ");
    scanf("%d", &b);
    
    printf("Suma: \t\t\t\t %d + %d = %d \n", a, b, suma(&a, &b));
    printf("Resta: \t\t\t\t %d - %d = %d \n", a, b, resta(&a, &b));
    printf("Multiplicación: \t\t %d * %d = %d \n", a, b, multiplicacion(&a, &b));
    printf("División: \t\t\t %d / %d = %d \n", a, b, division(&a, &b));
    
    return 0;
}

