#include <stdio.h>
#include "./Biblioteca_Cajas/boxnmore.h"

int main() {
    printf("Bienvenido a la prueba de la biblioteca \"boxnmore.h\"\n");
    printf("Esta biblioteca es la evoluciOn de \"cuadrito.h\"\n");

    printf("\nDado que contiene muchas funciones probablemente innecesarias\n");
    printf("es recomendable simplemente checarla y usar unicamente el\n");
    printf("contenido que sea de utilidad\n\n");
    getchar();

    printf("Las cuatro funciones principales de esta biblioteca estAn\n");
    printf("destinadas a imprimir mensajes puntuales de forma mAs\n");
    printf("elegante de lo normal. La biblioteca es completamente\n");
    printf("compatible entre Windows y Unix por lo que se puede usar\n");
    printf("con confianza\n\n");
    getchar();

    printf("Las funciones mencionadas son:\n");
    printf("\na) subraya(\"Cadena subrayada\"):\n");
    subraya("Cadena subrayada");
    printf("\nb) imprimeEnCuadro(\"Cadena en cuadro\"):\n");
    imprimeEnCuadro("Cadena en un cuadro");
    printf("\nc) imprimeEnBloque(\"Palabras\\nen\\nbloque\"):\n");
    imprimeEnBloque("Palabras\nen\nbloque");
    printf("\nd) imprimeConPuntos(\"Cadena entre puntos\"):\n");
    imprimeConPuntos("Cadena entre puntos");

    getchar();

    printf("A su vez para cada funciOn existe una funciOn analoga pero\n");
    printf("que ademAs permite especificar la separaciOn con que queremos\n");
    printf("que se imprima a partir del inicio de la pantalla.\n");
    printf("Estas funciones se llaman igual exepto por que tienen una\n");
    printf("S (ese mayuscula) al final que significa \"SeparaciOn\".\n\n");

    printf("\na) subrayaS(\"Cadena subrayada\", 3):\n");
    subrayaS("Cadena subrayada", 3);
    printf("\nb) imprimeEnCuadroS(\"Cadena en cuadro\", 3):\n");
    imprimeEnCuadroS("Cadena en un cuadro", 3);
    printf("\nc) imprimeEnBloqueS(\"Palabras\\nen\\nbloque\", 1):\n");
    imprimeEnBloqueS("Palabras\nen\nbloque", 1);
    printf("\nd) imprimeConPuntosS(\"Cadena entre puntos\", 2):\n");
    imprimeConPuntosS("Cadena entre puntos", 2);

    getchar();

    printf("La funciOn imprimeEnBloque tiene ademAs una variante que nos\n");
    printf("permite indicar el tamanio de la caja aniadiendole una T de\n");
    printf("tamanio al finAl.\n\n");

    printf("imprimeEnBloqueT(\"Palabras\\nen\\nbloque\", 10)\n");
    imprimeEnBloqueT("Palabras\nen\nbloque", 10);

    getchar();

    printf("Por Ultimo, tambiEn existe la funcion imprimeEnBloque con S y T\n");
    printf("(separaciOn y tamanio en ese orden):\n\n");

    printf("imprimeEnBloqueST(\"Palabras\\n   en\\n bloque\", 10, 3)\n");
    imprimeEnBloqueST("Palabras\n   en\n bloque", 3, 10);

    getchar();
    return 0;
}
