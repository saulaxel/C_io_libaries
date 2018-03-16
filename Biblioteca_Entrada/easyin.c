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

//  ##### Dependencies #####

#include "easyin.h"
#include <stdio.h>     // Data output (printf, fgets)
#include <stdlib.h>    // Allocating memory (malloc)
#include <string.h>    // Managin strings (strlen, strcpy)
#include <ctype.h>     // Type-checking functions (isgraph and any other)
#include <stdbool.h>   // _Bool as bool
#include <limits.h>    // Limits of the integer types
#include <float.h>     // Limits of the float types

#ifdef _WIN32
#include <conio.h> // Immediate reading (getch)
#define CLEAR() do {                                                        \
        if (system("cls") == -1)                                            \
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");       \
    } while (0)
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

    config_termios(false);

    tcsetattr(0, TCSANOW, &no_buffer);
    c = getchar();
    tcsetattr(0, TCSANOW, &normal);

    return c;
}
#define CLEAR() do {                                                        \
        if ( system("clear") == -1 )                                        \
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");       \
    } while (0)
#endif // end _WIN32

// ##### FUNCTION PROTOTYPES #####

static void clean_buffer(void);
static int valid_char_default(int);
static int valid_str_default(const char *s);

//  ##### PRIVATE DECLARATIONSDECLARATIONS #######
//  # Functions and variables for indirect use,  #
//  # these are only visible in the translation  #
//  # unit the library was included in.          #
//  ##############################################

/*
 * Function: get_int
 * Description: Asks the user for an int with the 
 * "prompt" message. If the input cannot be read 
 * into an integer type or the min/max values are not
 * respected the "err_msg" will be displayed and
 * the program will read again from the stdin until 
 * the user writes a valid entry.
 */
static int get_int (
        const char * restrict prompt,
        const char * restrict err_msg,
        const int minval,
        const int maxval
) {
    int d;
    bool valid_input;

    printf("%s",prompt);

    valid_input = scanf("%d", &d) && d >= minval && d <= maxval;
    clean_buffer();

    while( !valid_input ) {
        printf("%s",err_msg);

        valid_input = scanf("%d", &d) && d >= minval && d <= maxval;
        clean_buffer();
    }

    return d;
}

int get_int_helper( int_request_t args ) {
    args.min = args.min ? args.min : INT_MIN;
    args.max = args.max ? args.max : INT_MAX;

    return get_int(args.prompt       ? args.prompt       : " > ",
                   args.error_message ? args.error_message : " > ",
                   args.min     , args.max);
}

/*
 * get_double:
 *      const double *prompt, const char *err_msg,
 *      double minval, double maxval 
 *      -> float
 * Description: Asks the user for a float with the 
 * "prompt" message. If the input cannot be read 
 * into a float type or the read value is not
 * within the range the "err_msg" will be displayed and
 * the program will read again from the stdin untill 
 * the user writes a valid entry.
 */
static double get_double (
        const char * restrict prompt,
        const char * restrict err_msg,
        const double minval,
        const double maxval
) {
    double lf;
    bool valid_input;

    printf("%s", prompt);
    valid_input = scanf("%lf", &lf) && lf >= minval && lf <= maxval;
    clean_buffer();

    while( !valid_input ) {
        printf("%s", err_msg);
        valid_input = scanf("%lf", &lf) && lf >= minval && lf <= maxval;
        clean_buffer();
    }

    return lf;
}

double get_double_helper(double_request_t args) {
    args.min = args.min ? args.min : -FLT_MAX;
    args.max = args.max ? args.max :  FLT_MAX;

    return get_double(args.prompt       ? args.prompt       : " > ",
                      args.error_message ? args.error_message : " > ",
                      args.min, args.max);
}

/*
 * get_char: 
 *      const char *prompt, const char *err_msg,
 *      char minval, char maxval 
 *      -> char
 * Description: Asks the user for a char with the 
 * "prompt" message. If the input cannot be read 
 * into a char type or the read value is not
 * within the range the "err_msg" will be displayed and
 * the program will read again from the stdin untill 
 * the user writes a valid entry.
 */
static char get_char (
        const char * prompt,
        const char * err_msg,
        int (* _valid_char)(int),
        const char * sep,
        bool hidden
) {
    char c;
    bool valid_input;

    printf("%s", prompt);
    c = getch();

    if ( !hidden )
        putchar(c);

    printf("%s", sep);

    valid_input = (*_valid_char)(c);

    while( !valid_input ) {
        printf("%s", err_msg);
        c = getch();

        if ( !hidden )
            putchar(c);

        printf("%s", sep);

        valid_input = (*_valid_char)(c);
    }

    return c;
}

char get_char_helper(char_request_t args) {
    args.valid_char = args.valid_char ? args.valid_char : isgraph;

    return get_char(args.prompt       ? args.prompt       : " > ",
                    args.error_message ? args.error_message : " > ",
                    args.valid_char ? args.valid_char : isgraph,
                    args.sep ? args.sep : "\n",
                    args.hidden);
}

/*
 * get_word: char *s, const char *prompt, int _max_size
 * Description: Asks the user for a string with the 
 * "prompt" message and stores it in "s". If the input
 * string is larger than "_max_size" or it has invisible
 * charactes the sting will be cut off.
 */
static void get_word (
        char * restrict s,
        const char * restrict prompt,
        const int _max_size
) {
    char * restrict input = (char *) malloc(_max_size * sizeof(char));
    int strip = 0;

    printf("%s",prompt);
    if (!fgets(input, _max_size, stdin)) {
        fputs("Reading error", stderr);
        exit(EXIT_FAILURE);
    }

    while( input[strip] && isgraph(input[strip]) ) ++strip;

    input[strip] = '\0';

    strcpy(s, input);

    free(input);
}
/* * get_line: char *s, const char *prompt, int _max_size
 * Description: Asks the user for a string whit the 
 * "prompt" message and stores it in "s". If the input 
 * string is larger than "_max_size" the string will be cut
 * but the invisible characters won't be able to do so.
 */
static void get_line (
        char * restrict s,
        const char * restrict prompt,
        const int _max_size
) {
    printf("%s",prompt);

    if (!fgets(s, _max_size, stdin)) {
        fputs("Reading error", stderr);
        exit(EXIT_FAILURE);
    }

    s[ strlen(s) - 1 ] = '\0';
}

void get_word_line_helper(bool line, string_request_t args) {
    if ( args.s ) {
        args.max = args.max ? args.max : 100;

        if( line ) {
            get_line(args.s,
                     args.prompt ? args.prompt : " > ",
                     args.max);
        } else {
            get_word(args.s,
                     args.prompt ? args.prompt : " > ",
                     args.max);
        }

        return;
    }

    fprintf(stderr, "The function requires a place to store the string\n");
    exit(EXIT_FAILURE);
}

static void get_string (
        char * restrict s,
        const char * prompt,
        const char * err_msg,
        const char * _rng_msg,
        int (* _valid_char)(int),
        int (* _valid_str)(const char *),
        const int _min_len,
        const int _max_len,
        bool hidden
) {
#define RE_PRINT() CLEAR(); printf("%s", prompt); \
             for(int a = 0; a < i; a++) putchar(hidden ? '*' : s[a])
    int i = 0;
    char c;

    bool valid_input = false;
    CLEAR();
    printf("%s", prompt);

    while ( !valid_input ) {
        c = getch();

        if ( c == 127 ) {
            i -= (i) ? 1 : 0;

            RE_PRINT();
        } else if ( _valid_char(c) ) {
            if ( i == _max_len ) {

                if ( c == '\n' ) break;

                printf("\n%s", _rng_msg);

                getch();
                RE_PRINT();
            } else {
                putchar( hidden ? '*' : c );
                s[i++] = c;
            }

        } else if ( c == '\n' ) {
            if ( i >= _min_len)  {
                s[i] = '\0';

                if ( _valid_str(s) ) {
                    valid_input = true;
                } else {
                    i = 0;
                    break;
                }
            } else {
                printf("\n%s", _rng_msg);

                getch();
                RE_PRINT();
            }
        } else {
            RE_PRINT();
            printf("\n%s", err_msg);
            getch();

            RE_PRINT();
        }
    }

    putchar('\n');
}

void get_string_helper( stringscr_request_t args ) {
    if ( args.s ) {
        args.valid_char = args.valid_char ? args.valid_char : valid_char_default;

        args.min = args.min ? args.min : 0;
        args.max = args.max ? args.max : 100;

        get_string(args.s,
                   args.prompt ? args.prompt : " > ",
                   args.error_message ? args.error_message : "Invalid character",
                   args.range_message ? args.range_message : "String out of range",
                   args.valid_char,
                   args.valid_str ? args.valid_str : valid_str_default,
                   args.min, args.max,
                   args.hidden);
    } else {
        fprintf(stderr, "The function requires a place to store the string\n");
    }
}

static int valid_char_default(int c) { return c != '\n'; }
static int valid_str_default(const char *s) { return !*s; }

static inline void clean_buffer(void) {
    int c;
    while ( (c = getchar()) != '\n' &&  c != EOF );
}
