#include <stdint.h>
#include "./Biblioteca_Entrada/easyin.h"

int main(void) {
    int i;
    float f;
    char c;
    char cadena[100];

    i = pedirEntero("");
    printf("El entero es: %d\n", i);

    c = pedirCaracter("");
    printf("El caracter es: %c\n", c);

    pedirPalabra(cadena);
    printf("La cadena es: %s\n", cadena);

    f = pedirDoble("");
    printf("El doble es %f\n", f);

    pedirCadenaScr(cadena, .hidden = true);
    printf("La linea es %s\n", cadena);

    getchar();
    return 0;
}
