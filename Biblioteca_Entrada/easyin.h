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


#ifndef _EASY_IN_H
#define _EASY_IN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <limits.h>
#include <float.h>

#ifdef _WIN32
    #include <conio.h>
#else
    // getch equivalent from:
    // http://stackoverflow.com/questions/7469139/what-is-equivalent-to-getch-getche-in-linux

    #include <termios.h>

    char getch() {
        static struct termios old, new;
        char c;

        tcgetattr(0, &old);
        new = old;
        new.c_lflag &= ~ICANON;
        tcsetattr(0, TCSANOW, &new);

        c = getchar();

        tcsetattr(0, TCSANOW, &old);

        return c;
    }
#endif // end _WIN32

//  ##### PRIVATE DECLARATIONS #####  \\

static bool valid_input; // Boolean flag to validate input

static void clean_buffer(void) {
    char c;

    while( (c = getchar()) != '\n' &&  c != EOF );
}

/*
 * _askfint: 
 *      const char *_request, const char *_err_msg,
 *      int _minval, int _maxval 
 *      -> int
 * Description: Asks the user for an int with the 
 * "_request" message. If the input cannot be read 
 * into an integer type or the min/max values are not
 * respected the "_err_msg" will be displayed and
 * the program will read again from the stdin untill 
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

    valid_input = scanf("%d", &d) && d >= _minval && d <= _maxval;
    clean_buffer();

    while( !valid_input ) {
        printf("%s",_err_msg);

        valid_input = scanf("%d", &d) & d >= _minval && d <= _maxval;
        clean_buffer();
    }

    return d;
}

/*
 * _askfdouble:
 *      const char *_request, const char *_err_msg,
 *      float _minval, float _maxval 
 *      -> float
 * Description: Asks the user for a float with the 
 * "_request" message. If the input cannot be read 
 * into a float type or the read value is not
 * within the range the "_err_msg" will be displayed and
 * the program will read again from the stdin untill 
 * the user writes a valid entry.
 */
float _askfdouble(
        const char * restrict _request,
        const char * restrict _err_msg,
        const double _minval,
        const double _maxval
) {
    double lf;

    printf("%s",_request);
    valid_input = scanf("%lf", &lf) && lf >= _minval && lf <= _maxval;
    clean_buffer();

    while( !valid_input ) {
        printf("%s", _err_msg);

        valid_input = scanf("%lf", &lf) && lf >= _minval && lf <= _maxval;
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
char _askfchar(
        const char * restrict _request,
        const char * restrict _err_msg,
        int (* _validate_char)(int)
) {
    char c;

    printf("%s",_request);
    c = getch();
    putchar('\n');

    valid_input = (*_validate_char)(c);

    while( !valid_input ) {
        printf("%s", _err_msg);
        c = getch();
        putchar('\n');

        valid_input = (*_validate_char)(c);
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
void _askfwrd(
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

/*
 * _askfline: char *s, const char *_request, int _max_size
 * Description: Asks the user for a string whit the 
 * "_request" message and stores it in "s". If the input 
 * string is larger than "_max_size" the string will be cut
 * but the invisible characters won't be able to do so.
 */
void _askfline(
        char * restrict s,
        const char * restrict _request,
        const int _max_size
) {
    printf("%s",_request);

    fgets(s, _max_size, stdin);
    s[ strlen(s) - 1 ] = '\0';
}

//  ##### PUBLIC DECLARATIONS #####  \\

typedef struct {
    char * request;
    char * error_message;
    int min_value;
    int max_value;
}int_request_t;

#define pedirEntero(...) _pedir_entero((int_request_t){__VA_ARGS__})

int _pedir_entero( int_request_t args ) {
    args.min_value = args.min_value ? args.min_value : INT_MIN;
    args.max_value = args.max_value ? args.max_value : INT_MAX;

    return _askfint(args.request       ? args.request       : "",
                    args.error_message ? args.error_message : "",
                    args.min_value     , args.max_value);
}

typedef struct {
    char * request;
    char * error_message;
    int (* validate_char)(int);
} char_request_t;

#define pedirCaracter(...) _pedir_caracter((char_request_t){__VA_ARGS__})

char _pedir_caracter(char_request_t args) {
    args.validate_char = args.validate_char ? args.validate_char : isgraph;

    return _askfchar(args.request       ? args.request       : "",
                     args.error_message ? args.error_message : "",
                     args.validate_char);
}

typedef struct {
    char * request;
    char * error_message;
    double min_value;
    double max_value;
} double_request_t;

#define pedirDoble(...) _pedir_doble((double_request_t){__VA_ARGS__})

double _pedir_doble(double_request_t args) {
    args.min_value = args.min_value ? args.min_value : -FLT_MAX;
    args.max_value = args.max_value ? args.max_value :  FLT_MAX;

    return _askfdouble(args.request       ? args.request       : "",
                       args.error_message ? args.error_message : "",
                       args.min_value, args.max_value);
}

typedef struct {
    char * s;
    char * request;
    int max_len;
} string_request_t;

#define pedirPalabra(...) _pedir_cadena(false, (string_request_t){__VA_ARGS__})
#define pedirLinea(...)   _pedir_cadena( true, (string_request_t){__VA_ARGS__})

void _pedir_cadena(bool line, string_request_t args) {
    if( args.s ) {
        args.max_len = args.max_len ? args.max_len : 100;

        if( line ) {
            _askfline(args.s,
                     args.request ? args.request : "",
                     args.max_len);
        } else {
            _askfwrd(args.s,
                     args.request ? args.request : "",
                     args.max_len);
        }

        return;
    }

    fprintf(stderr, "The function requires a place to store the string\n");
}


#endif // end _EASY_IO_H
