/*
 * (C) Copyright 2017 MartInez Ortiz Saul - UNAM FI
 *
 * This program is free software: you can redistribute it and/or modify
 * Tt under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*=========================================================*
 * Library     : easyin                                    *
 * Description : Some functions to read data from the user *
 *               without painox                            * 
 *=========================================================*/

#ifndef _EASY_IN_H
#define _EASY_IN_H

//  ##### Dependencies #####  \\

#include <stdio.h>     // Data output (printf, fgets)
#include <stdlib.h>    // Allocating memory (malloc)
#include <string.h>    // Managin strings (strlen, strcpy)
#include <ctype.h>     // Type-checking functions (isgraph and any other)
#include <stdbool.h>   // _Bool as bool
#include <limits.h>    // Limits of the integer types
#include <float.h>     // Limits of the float types

#ifdef _WIN32
    #include <conio.h> // Immediate reading (getch)
    #define CLEAR "cls"
#else
    // getch equivalent from:
    // http://stackoverflow.com/questions/7469139/what-is-equivalent-to-getch-getche-in-linux

    #include <termios.h>
    static struct termios normal, no_buffer;

    static inline void config_termios(bool echo) {
        tcgetattr(0, &normal);

        no_buffer = normal;
        no_buffer.c_lflag &= ~ICANON;

        if( echo )  { no_buffer.c_lflag |= ECHO;  }
        else        { no_buffer.c_lflag &= ~ECHO; }
    }

    char getch(void) {
        char c;

        config_termios(true);

        tcsetattr(0, TCSANOW, &no_buffer);

        c = getchar();

        tcsetattr(0, TCSANOW, &normal);

        return c;
    }
    #define CLEAR "clear"
#endif // end _WIN32

typedef struct {
    char * request;
    char * error_message;
    int min_value;
    int max_value;
}int_request_t;

typedef struct {
    char * request;
    char * error_message;
    int (* valid_char)(int);
} char_request_t;

typedef struct {
    char * request;
    char * error_message;
    double min_value;
    double max_value;
} double_request_t;

typedef struct {
    char * s;
    char * request;
    int max_len;
} string_request_t;

typedef struct {
    char * s;
    char * request;
    char * error_message;
    char * range_message;

    int (* valid_char)(int);

    int min_len;
    int max_len;

    bool hidden;
} stringscr_request_t;

// ##### FUNCTION PROTOTYPES ##### \\

static int _askfint(const char * restrict, const char * restrict,
        const int _minval, const int _maxval);
static double _askfdouble(const char * restrict, const char * restrict,
        const double _minval, const double _maxval);
static char _askfchar(const char * restrict, const char * restrict,
        int (* _valid_char)(int));
static void _askfwrd(char * restrict, const char * restrict,
        const int _max_size);
static void _askfline(char * restrict, const char * restrict,
        const int _max_size);

static void _pedir_cadena(bool line, string_request_t args);
static double _pedir_doble(double_request_t args);
static char _pedir_caracter(char_request_t args);
static int _pedir_entero( int_request_t args );

extern void clean_buffer(void);

//  ##### PRIVATE DECLARATIONSDECLARATIONS #######
//  # Functions and variables for indirect use,  #
//  # these are only visible in the translation  #
//  # unit the library was included in.          #
//  ##############################################

static bool _valid_input; // Boolean flag to validate input

/*
 * Function: _askfint
 * Description: Asks the user for an int with the 
 * "_request" message. If the input cannot be read 
 * into an integer type or the min/max values are not
 * respected the "_err_msg" will be displayed and
 * the program will read again from the stdin until 
 * the user writes a valid entry.
 */
static int _askfint(
        const char * restrict _request,
        const char * restrict _err_msg,
        const int _minval,
        const int _maxval
) {
    int d;

    printf("%s",_request);

    _valid_input = scanf("%d", &d) && d >= _minval && d <= _maxval;
    clean_buffer();

    while( !_valid_input ) {
        printf("%s",_err_msg);

        _valid_input = scanf("%d", &d) & d >= _minval && d <= _maxval;
        clean_buffer();
    }

    return d;
}

/*
 * _askfdouble:
 *      const double *_request, const char *_err_msg,
 *      double _minval, double _maxval 
 *      -> float
 * Description: Asks the user for a float with the 
 * "_request" message. If the input cannot be read 
 * into a float type or the read value is not
 * within the range the "_err_msg" will be displayed and
 * the program will read again from the stdin untill 
 * the user writes a valid entry.
 */
static double _askfdouble(
        const char * restrict _request,
        const char * restrict _err_msg,
        const double _minval,
        const double _maxval
) {
    double lf;

    printf("%s",_request);
    _valid_input = scanf("%lf", &lf) && lf >= _minval && lf <= _maxval;
    clean_buffer();

    while( !_valid_input ) {
        _valid_input = scanf("%lf", &lf) && lf >= _minval && lf <= _maxval;
        clean_buffer();
    }

    return lf;
}

/*
 * _askfchar: 
 *      const char *_request, const char *_err_msg,
 *      char _minval, char _maxval 
 *      -> char
 * Description: Asks the user for a char with the 
 * "_request" message. If the input cannot be read 
 * into a char type or the read value is not
 * within the range the "_err_msg" will be displayed and
 * the program will read again from the stdin untill 
 * the user writes a valid entry.
 */
static char _askfchar(
        const char * restrict _request,
        const char * restrict _err_msg,
        int (* _valid_char)(int)
) {
    char c;

    printf("%s",_request);
    c = getch();
    putchar('\n');

    _valid_input = (*_valid_char)(c);

    while( !_valid_input ) {
        printf("%s", _err_msg);
        c = getch();
        putchar('\n');

        _valid_input = (*_valid_char)(c);
    }

    return c;
}

/*
 * _askfwrd: char *s, const char *_request, int _max_size
 * Description: Asks the user for a string with the 
 * "_request" message and stores it in "s". If the input
 * string is larger than "_max_size" or it has invisible
 * charactes the sting will be cut off.
 */
static void _askfwrd(
        char * restrict s,
        const char * restrict _request,
        const int _max_size
) {
    char * restrict input = (char *) malloc(_max_size * sizeof(char));
    int strip = 0;

    printf("%s",_request);
    fgets(input, _max_size, stdin);

    while( input[strip] && isgraph(input[strip]) ) ++strip;

    input[strip] = '\0';

    strcpy(s, input);

    free(input);
}
/* * _askfline: char *s, const char *_request, int _max_size
 * Description: Asks the user for a string whit the 
 * "_request" message and stores it in "s". If the input 
 * string is larger than "_max_size" the string will be cut
 * but the invisible characters won't be able to do so.
 */
static void _askfline(
        char * restrict s,
        const char * restrict _request,
        const int _max_size
) {
    printf("%s",_request);

    fgets(s, _max_size, stdin);
    s[ strlen(s) - 1 ] = '\0';
}

static void _askfstrscr(
        char * restrict s,
        const char * restrict _request,
        const char * restrict _err_msg,
        const char * restrict _rng_msg,
        int (* _valid_char)(int),
        const int _min_len,
        const int _max_len,
        bool hidden
) {
#define RE_PRINT system(CLEAR); printf("%s", _request); \
             for(int a = 0; a < i; a++) putchar(hidden ? '*' : s[a])
    int i = 0;
    char c;

    config_termios(false);

    tcsetattr(0, TCSANOW, &no_buffer);

    system(CLEAR);
    printf("%s", _request);

    while( 1 ) {
        c = getchar();

        if( c == 127 ) {
            i -= (i) ? 1 : 0;

            RE_PRINT;
        } else if( _valid_char(c) ) {
            if( i == _max_len ) {

                if( c == '\n' ) break;

                printf("\n%s", _rng_msg);

                getchar();
                RE_PRINT;
            } else {
                putchar( hidden ? '*' : c );
                s[i++] = c;
            }

        } else if( c == '\n' ) {
            if( i >= _min_len) break;
            else {
                printf("\n%s", _rng_msg);

                getchar();
                RE_PRINT;
            }
        } else {
            printf("\n%s", _err_msg);
            getchar();

            RE_PRINT;
        }
    }

    s[i] = '\0';

    tcsetattr(0, TCSANOW, &normal);
}

#undef RE_PRINT

int _pedir_entero( int_request_t args ) {
    args.min_value = args.min_value ? args.min_value : INT_MIN;
    args.max_value = args.max_value ? args.max_value : INT_MAX;

    return _askfint(args.request       ? args.request       : " > ",
                    args.error_message ? args.error_message : " > ",
                    args.min_value     , args.max_value);
}

char _pedir_caracter(char_request_t args) {
    args.valid_char = args.valid_char ? args.valid_char : isgraph;

    return _askfchar(args.request       ? args.request       : " > ",
                     args.error_message ? args.error_message : " > ",
                     args.valid_char);
}

double _pedir_doble(double_request_t args) {
    args.min_value = args.min_value ? args.min_value : -FLT_MAX;
    args.max_value = args.max_value ? args.max_value :  FLT_MAX;

    return _askfdouble(args.request       ? args.request       : " > ",
                       args.error_message ? args.error_message : " > ",
                       args.min_value, args.max_value);
}

void _pedir_cadena(bool line, string_request_t args) {
    if( args.s ) {
        args.max_len = args.max_len ? args.max_len : 100;

        if( line ) {
            _askfline(args.s,
                     args.request ? args.request : " > ",
                     args.max_len);
        } else {
            _askfwrd(args.s,
                     args.request ? args.request : " > ",
                     args.max_len);
        }

        return;
    }

    fprintf(stderr, "The function requires a place to store the string\n");
}

void _pedir_cadenascr( stringscr_request_t args ) {
    if( args.s ) {
        args.valid_char = args.valid_char ? args.valid_char : isgraph;

        args.min_len = args.min_len ? args.min_len : 0;
        args.max_len = args.max_len ? args.max_len : 100;

        _askfstrscr(args.s,
                         args.request ? args.request : " > ",
                         args.error_message ? args.error_message : "Invalid character",
                         args.range_message ? args.range_message : "String out of range",
                         args.valid_char,
                         args.min_len, args.max_len,
                         args.hidden);
        return;
        }

    fprintf(stderr, "The function requires a place to store the string\n");

}

//  ##### PUBLIC DECLARATIONSDECLARATIONS #########
//  # Macrofunctions and functions for direct use,#
//  # these are visible among all                 #
//  # compiled-together translation units         #
//  ###############################################

#define pedirEntero(...) _pedir_entero((int_request_t){__VA_ARGS__})

#define pedirCaracter(...) _pedir_caracter((char_request_t){__VA_ARGS__})

#define pedirDoble(...) _pedir_doble((double_request_t){__VA_ARGS__})

#define pedirPalabra(...) _pedir_cadena(false, (string_request_t){__VA_ARGS__})
#define pedirLinea(...)   _pedir_cadena( true, (string_request_t){__VA_ARGS__})

#define pedirCadenaScr(...) _pedir_cadenascr((stringscr_request_t){__VA_ARGS__})

inline void clean_buffer(void) {
    char c;

    while( (c = getchar()) != '\n' &&  c != EOF );
}

#endif // end _EASY_IO_H
