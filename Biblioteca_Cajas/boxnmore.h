/*
 * (C) Copyright 2017 MartInez Ortiz Saul UNAM
 *
  *This program is free software: you can redistribute it and/or modify
  *Tt under the terms of the GNU General Public License as published by
  *the Free Software Foundation, either version 3 of the License, or
  *(at your option) any later version.
 *
  *This program is distributed in the hope that it will be useful,
  *but WITHOUT ANY WARRANTY; without even the implied warranty of
  *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  *GNU General Public License for more details.
 *
  *You should have received a copy of the GNU General Public License
  *along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef _BOXNMORE_H
#define _BOXNMORE_H

#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

//  ##### PRIVATE DECLARATIONS #####

#ifdef _WIN32
    #define HS "\xCD"    // Horizontal side
    #define VS "\xBA"    // Vertical side

    #define UL "\xC9"    // Upper left corner
    #define UR "\xBB"    // Upper right corner
    #define LL "\xC8"    // Lower left corner
    #define LR "\xBC"    // Lower right corner
#else // not _WIN32
    #define HS "\u2550"  // Horizontal side
    #define VS "\u2551"  // Vertical side

    #define UL "\u2554"  // Upper left corner
    #define UR "\u2557"  // Upper right corner
    #define LL "\u255A"  // Lower left corner
    #define LR "\u255D"  // Lower right corner
#endif // end __WIN32

// Macro that simply concatenates
#define C(a,b) a b

// Macro that concatenates the string and the
// bounds (String With Bounds)
#define SWB VS " %s " VS "\n"

// Macro that concatenates new line to string
// (Concatenate New Line)
#define CNL(s) s "\n"

#ifdef __unix__
/* 
 * cntExtraBytes: const char  *_str, int len -> int
 * This function is used to know the printable lenght of a
 * string, since utf-8 uses variable lenght chars we
 * have to count how many bytes don't have to be considered
 * when dealing with the string.
 */
int cntExtraBytes(const char *_str, int len) {
    int i;
    int extra = 0;

    for(i = 0; i < len; ++i) {
        if( (_str[i] & 240 ) == 240 ) {
            extra += 3;
            i     += 3;
        }else if( (_str[i] & 224 ) == 224 ) {
            extra += 2;
            i     += 2;
        }else if( (_str[i] & 192 ) == 192 ) {
            ++extra;
            ++i;
        }
    }

    return extra;
}
#endif // end __unix__

/*
 * _unln: char *_str, int _space -> void
 * Description: Prints the string of the
 * argument underlined by underscores and
 * separated "_space" tabs from the start
 * of the screen
 */
void _unln(const char *_str, int _space) {
    int i;
    int len = strlen(_str);

#ifdef __unix__
    len -= cntExtraBytes(_str, len);
#endif // end __unix__

    for(i = 0; i < _space; ++i) putchar('\t');
    printf("%s\n", _str);

    for(i = 0; i < _space; ++i) putchar('\t');
    for(i = 0; i < len; ++i) putchar('_');

    putchar('\n');
}

/*
 *  _pbox: char *_str, int _space -> void
 *  Description: Function that receives a
 *  string "_str" to print it inside a box
 *  separated by "_space" tabs from the left
 *  of the screen.
 */
void _pbox(const char *_str, int _space) {
    int i;
    int len = strlen(_str) + 2;

#ifdef __unix__
    len -= cntExtraBytes(_str, len - 2);
#endif

    // Print the top
    for(i = 0; i < _space; ++i) putchar('\t');
    printf(UL);
    for(i = 0; i < len; ++i) printf(HS);
    printf(CNL(UR));

    // Print the middle ( the string would be here)
    for(i = 0; i < _space; ++i) putchar('\t');
    printf(SWB, _str);

    // Print the bottom
    for(i = 0; i < _space; ++i) putchar('\t');
    printf(LL);
    for(i = 0; i < len; ++i) printf(HS);
    printf(CNL(LR));

}

/*
 *  _pmbox: char *_str, int _space , int _box_size-> void
 *  Description: Function that tokenizes a the "_str"
 *  argument by its \n (New line characters) and print
 *  everyone of the tokens in a line of "_box_size" width
 *  surrounded by a box.
 *  The box can be separated "_space" tabs from the left of
 *  the screen
 */
void _pmbox(const char *_str, int _space, int _box_size) {
    char _size_in_str[4];

    char *str_cpy = (char *) malloc(sizeof(char)  *strlen(_str) + 1);
    strcpy(str_cpy, _str);

    char *line;
    int i;

    _box_size %= 150;

    // Stores the value of _box_size as a str in _size_str"
    sprintf(_size_in_str, "%d", _box_size - 2);

    char _format_[15] = "";
#ifdef _WIN32
    // Calculates the format string once
    strcat(_format_, C(VS, " %-"));
    strcat(_format_, _size_in_str);
    strcat(_format_, CNL( C("s ", VS) ) );
#endif // end _WIN32

    // Print the top
    for(i = 0; i < _space; ++i) putchar('\t');
    printf(UL);
    for(i = 0; i < _box_size; ++i) printf(HS);
    printf(CNL(UR));

    // Print the middle
    line = strtok(str_cpy, "\n");

    while( line != NULL ) {

#ifdef __unix__
        // Calculates the format string every time
        strcpy(_format_, "");
        sprintf(
                _size_in_str,
                "%d", _box_size - 2 + cntExtraBytes(line, strlen(line))
        );
        strcat(_format_, C(VS, " %-"));
        strcat(_format_, _size_in_str);
        strcat(_format_, CNL( C("s ", VS) ) );
#endif // end __unix__

        for(i = 0; i < _space; ++i) putchar('\t');
        printf(_format_, line);
        line = strtok(NULL, "\n");
    }

    // Print the bottom
    for(i = 0; i < _space; ++i) putchar('\t');
    printf(LL);
    for(i = 0; i < _box_size; ++i) printf(HS);
    printf(CNL(LR));

    free(str_cpy);
}

/*
 *  _pdotted: char *_str, int _space , int _box_size-> void
 *  Description: Function that tokenizes a the "_str"
 */
void _pdotted(const char *_str, int _space) {
    int i;
    int len = strlen(_str) + 8;

#ifdef __unix__
    len -= cntExtraBytes(_str, len - 2);
#endif
    void pDotLine(int d) {

        for(i = 0; i < _space; ++i) putchar('\t');
        if( d ) putchar(' ');
        for(i = 0; i < len / 2; ++i) printf(" *");
        putchar('\n');
        ++d;
    }

    pDotLine(0);
    pDotLine(1);

    // Print the middle
    for(i = 0; i < _space; ++i) putchar('\t');
    printf(" * *%s", _str);
    printf("%s\n", len % 2? "* *": " *");

    pDotLine(1);
    pDotLine(0);
}

//  ##### PUBLIC DECLARATIONS #####

/*
 * imprimeEnCuadro: char *cadena -> void
 * Description: This function calls the
 * _pbox function to print a string inside
 * a box with no separation from the start
 * of the screen
 */
void imprimeEnCuadro(char *cadena) {
    _pbox(cadena, 0);
}

/*
 * imprimeEnCuadroSeparadoPor:
 *          char *cadena, int n -> void
 * Description: Function that calls _pbox to
 * print string inside a box separated by separacion
 * tabs from the start of the screen
 */
void imprimeEnCuadroS(char *cadena, int separacion) {
    _pbox(cadena,separacion);
}

/*
 * imprimeEnBloque: char *cadena -> void
 * Description: Function that prints tokens of
 * a string separated by \n (New line) in a box
 * with 80 spaces of width
 */
void imprimeEnBloque(char *cadena) {
    _pmbox(cadena, 0, 60);
}

/*
 * imprimeEnBloqueTam: char *cadena -> void
 * Description: Similar to "imprimeEnBloque" function
 * but also lets specify the size of the box
 * to put the strins in.
 */
void imprimeEnBloqueT(char *cadena, int tamanio) {
    _pmbox(cadena, 0, tamanio);
}

/*
 * imprimeEnBloqueSep: char *cadena, int tabs -> void
 * Description: Similar to "imprimeEnBloque" function
 * but also lets specify the separation between
  *the start of the screen and the box int tabs.
 */
void imprimeEnBloqueS(char *cadena, int separacion) {
    _pmbox(cadena, separacion, 60);
}

/*
 * imprimeEnBloqueTS: char *cadena, int n, int tabs -> void
 * Description: Function to print the tokens (separated by new line)
 * of a string in a box and lets to specify the size of the box
 * and the separation of the left side of the screen.
 */
void imprimeEnBloqueST(char *cadena, int separacion, int tamanio) {
    _pmbox(cadena, separacion, tamanio);
}

/*
 * subraya: char *cadena -> void
 * Description: Prints the string of the argument
 * underlined by underscores
 */
void subraya(char *cadena) {
    _unln(cadena, 0);
}

/*
 * subrayaConEspacio: char *cadena, int n-> void
 * Description: Prints the string of the argument
 * underlined by underscores and separated "separacion" tabs
 * from the left of the screen
 */
void subrayaS(char *cadena, int separacion) {
    _unln(cadena, separacion);
}

/*
 * imprimeConPuntos: char *cadena -> void
 * Description: Prints the string
 * "cadena" surrounded by asterisks
 */
void imprimeConPuntos(char *cadena) {
    _pdotted(cadena,0);
}

/*
 * imprimeConPuntosS: char *cadena, int tabs -> void
 * Description: Prints the string "cadena"
 * surrounded by asterisks and separated by "separacion" tabs 
 */
void imprimeConPuntosS(char *cadena, int separacion) {
    _pdotted(cadena, separacion);
}

// Undoing definitions
#undef C
#undef SWB
#undef CNL

#endif // end _BOXNMORE_H
