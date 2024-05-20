/*
--------------------------------------------------
Robert Josue Huanca Clares
DAT - 241

Problema 2. Lleve el anterior código en c++.
--------------------------------------------------
*/

#include <iostream>

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
    // Calculamos el resultado
    int resultado = 0;
    int i = (*b > 0) ? -(*b) : (*b);
    for (i; i < 0; i++) {
        resultado += *a;
    }
    // Arreglo final para que funcione en los 4 casos
    int final = ((*b < 0 && *a > 0) || (*a > 0 && *b > 0)) ? resultado : -resultado;
    return final * signo;
}

int division(int *a, int *b) {
    // Hallamos el signo
    int signo = determinar_signo(*a, *b);
    // Mostramos la excepción
    if (*b == 0) {
        std::cout << "División sobre 0" << std::endl;
        return 0;
    }
    // Calculamos el resultado ajustando signos
    int resultado = 0;
    int dividendo = (*a < 0) ? -(*a) : (*a); // Hacemos que sean
    int divisor = (*b < 0) ? -(*b) : (*b); // positivos
    // Realizamos la división
    while (dividendo >= divisor) {
        resultado++;
        dividendo -= divisor;
    }
    return resultado * signo;
}


int main() {

    int a, b;
    std::cout << "Introduzca el valor de a: ";
    std::cin >> a;
    std::cout << "Introduzca el valor de b: ";
    std::cin >> b;
    
    std::cout << "Suma: \t\t\t\t " << a << " + " << b << " = " << suma(&a, &b) << std::endl;
    std::cout << "Resta: \t\t\t\t " << a << " - " << b << " = " << resta(&a, &b) << std::endl;
    std::cout << "Multiplicación: \t\t " << a << " * " << b << " = " << multiplicacion(&a, &b) << std::endl;
    std::cout << "División: \t\t\t " << a << " / " << b << " = " << division(&a, &b) << std::endl;
    
    return 0;
}

