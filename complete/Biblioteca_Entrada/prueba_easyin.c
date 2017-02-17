#include "easyin.h"
#include <stdint.h>

int main() {
    int i;
    float f;
    char c;
    char cadena[100];
    int16_t a = -32768;

    printf("%d\n", -a);

    printf("La biblioteca easyin.h nos permite pedir datos al usuario de forma facil\n");

    printf("Las funciones principales son 5, de las cuales 3 entran en\n");
    printf("un ciclo mientras que no se ingrese un valor valido\n\n");

    printf("Las funciones se demuestran a continuaciOn\n");

    printf("pedirEntero(\"\");\n");
    i = pedirEntero("");
    printf("El valor ingresado es: %d\n\n", i);

    printf("pedirFlotante(\"\");\n");
    f = pedirFlotante("");
    printf("El valor ingresado es: %f\n\n", f);

    printf("pedirCaracter(\"\");\n");
    c = pedirCaracter("");
    printf("El valor ingresado es: %c\n\n", c);

    printf("pedirPalabra(cadena_para_guardar_palabra, \"\");\n");
    pedirPalabra(cadena, "");
    printf("El valor ingresado es: %s\n\n", cadena);

    printf("pedirLinea(cadena_para_guardar_linea, \"\");\n");
    pedirPalabra(cadena, "");
    printf("El valor ingresado es: %s\n\n", cadena);

    getchar();

    printf("Si fuiste observador(a) te habrAs dado cuenta de que\n");
    printf("todas las funciones reciben una cadena como parametro el\n");
    printf("cual se desplegarA antes de empezar a pedir datos del teclado\n\n");

    getchar();

    printf("AdemAs, tanto pedirPalabra como pedirLinea leen\n");
    printf("y su Unica diferencia es que pedir palabra se detiene con espacios\n");
    printf("o tabuladores mientras que pedirLinea solo se detiene\n");
    printf("con un salto de lInea\n\n");

    getchar();

    printf("Las funciones numEricas tambiEn tienen versiones que despliegan\n");
    printf("un mensaje de error cada vez que se inserte un valor invalido:\n\n");

    printf("pedirEnteroErr(\"Dame entero: \", \"Ese no, otro:\");\n");
    i = pedirEnteroErr("Dame entero: ", "Ese no, otro: ");
    printf("El valor ingresado es: %d\n\n", i);

    printf("pedirFlotanteErr(\"Dame flotante: \", \"Ese no, otro: \");\n");
    f = pedirFlotanteErr("Dame flotante: ", "Ese no, otro: ");
    printf("El valor ingresado es: %f\n\n", f);

    getchar();

    printf("En las funciones numEricas y de caracteres tienen una variante\n");
    printf("que limita sus valores a un rango en especifico.\n");
    printf("Por su parte las funciones de cadena pueden\n");
    printf("Ser delimitadas en longitud usando la misma variante en sus nombres\n\n");

    printf("pedirEnteroLim(\"Dame entero: \", 8, 123);\n");
    i = pedirEnteroLim("Dame entero: ", 8, 123)
    printf("El valor ingresado es: %d\n\n", i);

    printf("pedirFlotanteLim(\"Dame flotante: \", 0.435, 0.961);\n");
    f = pedirFlotanteLim("Dame flotante: ", 0.435, 0.961);
    printf("El valor ingresado es: %f\n\n", f);

    printf("pedirCaracterLim(\"Dame letra mayuscula: \", 'A', 'Z');\n");
    c = pedirCaracterLim("Dame letra mayuscula: ", 'A', 'Z');
    printf("El valor ingresado es: %c\n\n", c);

    getchar();

    printf("Por Ultimo, se pueden usar las dos caracteristicas anteriores juntas:\n\n");

    printf("pedirEnteroErrLim(\"Dame entero: \", \"Ese no, otro: \", 8, 123);\n");
    i = pedirEnteroErrLim("Dame entero: ", "Ese no, otro: ", 8, 123);
    printf("El valor ingresado es: %d\n\n", i);

    printf("pedirFlotanteErrLim(\"Dame flotante: \",\"Ese no, otro: \", 0.435, 0.961);\n");
    f = pedirFlotanteErrLim("Dame flotante: ", "Ese no, otro: ", 0.435, 0.961);
    printf("El valor ingresado es: %f\n\n", f);

    printf("pedirCaracterErrLim(\"Dame letra mayuscula\", \"Esa no, otra: \", 'A', 'Z');\n");
    c = pedirCaracterErrLim("Dame letra mayuscula: ", "Esa no, otra: ", 'A', 'Z');
    printf("El valor ingresado es: %c\n\n", c);

    getchar();
    return 0;
}
