#include <stdio.h>
#include "./Biblioteca_Cajas/boxout.h"

int main(void) {
    printf("Sección 1: Subrayados");
    PrintUnderlined(NULL, .line="========");

    PrintUnderlined("Cadena subrayada 1");
    PrintUnderlined("Cadena subrayada 2", .space=30);
    PrintUnderlined("Cadena subrayada 3", .line="*", .space=60);
    getchar();

    printf("Sección 2: Cajas     ");
    PrintUnderlined(NULL, .line="========");

    PrintInsideBox("Cadena en un cuadro");
    PrintInsideBox("Palabras\nen\nbloque", .dir=DIR_CENTER, .space=20, .box_size=40);
    PrintInsideBox("Cadena alineada a la derecha", .dir=DIR_RIGHT, .box_size=40, .space=40);
    getchar();

    printf("Sección 3: Puntos    ");
    PrintUnderlined(NULL, .line="========");

    PrintDotted("Hola que hace", .space=35, .end="\n");
    PrintDotted("we", .space=40, .end="\n");
    PrintDotted("??????", .space=38);

    getchar();
    return 0;
}
