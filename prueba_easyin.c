#include <stdint.h>
#include "./Biblioteca_Entrada/easyin.h"

int main() {
    int i;
    float f;
    char c;
    char cadena[100];

    printf("Las funciones de esta biblioteca se demuestran a continuaciOn\n\n");

    printf("ejemplo 1: pedirEntero();\n");
    i = pedirEntero();
    printf("El valor ingresado es: %d\n\n", i);

    printf("ejemplo 2: pedirEntero(\"Dame un entero porfa: \", \"No ese no, otro: \");\n");
    i = pedirEntero("Dame un entero porfa: ", "No ese no, otro: ");
    printf("El valor ingresado es: %d\n\n", i);

    printf("ejemplo 3: pedirFlotante(.error_message=\"fuera de rango, escriba otro\",\n"
            " .min_value=6, .max_value=8 );\n");
    f = pedirDoble(.error_message="fuera de rango, escriba otro ", .min_value=6, .max_value=8);
    printf("El valor ingresado es: %f\n\n", f);

    printf("pedirCaracter();\n");
    c = pedirCaracter();
    printf("El valor ingresado es: %c\n\n", c);

    printf("pedirPalabra(cadena_para_guardar_palabra);\n");
    pedirPalabra(cadena);
    printf("El valor ingresado es: %s\n\n", cadena);

    printf("pedirLinea(cadena_para_guardar_linea);\n");
    pedirLinea(cadena);
    printf("El valor ingresado es: %s\n\n", cadena);

    getchar();
    return 0;
}
