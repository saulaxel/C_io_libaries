#include <stdint.h>
#include <ctype.h> // Para funciones de validación de caracteres
#include "./Biblioteca_Entrada/easyin.h"

int esCinco_o_A(int caracter) {
    return caracter == '5' || caracter == 'a' || caracter == 'A';
}

int main(void) {

    printf("Leyendo enteros:\n");
    int i;

    i = getInt("Dame un entero: ");
    printf("El entero es: %d\n\n", i);

    i = getInt("Ahora dame un entero entre 10 y 25: ", .min=10, .max=25,
                .error_message="¡Te he dicho que entre 10 y 25 >:v!\n"
                               " > ");
    printf("El entero es: %d\n\n", i);


    printf("Leyendo dobles:\n");
    double f;
    f = getDouble("Ingresa un número real: ");
    printf("El doble es %f\n\n", f);

    f = getDouble("Ahora ingresa un real entre E y PI: ",
                  .min=2.71728182, .max=3.14159265,
                  .error_message="E=2.71728182 y PI=3.14159265 por si no te acuerdas\n"
                                 " > ");
    printf("El doble es %f\n\n", f);

    printf("Leyendo caracteres: \n");
    char c;
    c = getChar("Ahora ingresa cualquier carácter: ");
    printf("El carácter es: %c\n\n", c);

    c = getChar("Ahora ingresa una letra mayúscula: ", .valid_char=isupper);
    printf("El carácter es: %c\n\n", c);

    c = getChar("Ingresa un 5 o una a: ", .valid_char=esCinco_o_A,
                .error_message="¡¡Te dije que solo 5 o a!!\n"
                               "> ");
    printf("El carácter es: %c\n\n", c);

    c = getChar("Ingresa un carácter secreto: ", .hidden=true);
    printf("El carácter es: %c\n\n", c);

    printf("Leyendo cadenas: \n");

    char cadena[100];
    getWord(cadena, "Ingresa una palabra: ");
    printf("La cadena es: %s\n", cadena);
    getchar();

    getString(cadena, "Ingresa una contraseña de entre 8 y 16 caracteres: ",
            .hidden=true,
            .valid_char=isgraph,
            .min=8, .max=16,
            .error_message="Las contraseñas se forman de caracteres ascii imprimibles\n",
            .range_message="La cadena debe de tener entre 8 y 16 caracteres\n");

    printf("La contraseña es es %s\n", cadena);

    getchar();
    return 0;
}
