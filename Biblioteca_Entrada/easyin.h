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

//  ##### Dependencies #####

#include <stdio.h>     // Data output (printf, fgets)
#include <stdlib.h>    // Allocating memory (malloc)
#include <stdbool.h>   // _Bool as bool

typedef struct {
    char * request;
    char * error_message;
    int min_value;
    int max_value;
} int_request_t;

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

// ##### FUNCTION PROTOTYPES #####

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

//  ###############################################
//  # Macrofunctions for direct use               #
//  ###############################################

#define pedirEntero(...) _pedir_entero((int_request_t){__VA_ARGS__})

#define pedirCaracter(...) _pedir_caracter((char_request_t){__VA_ARGS__})

#define pedirDoble(...) _pedir_doble((double_request_t){__VA_ARGS__})

#define pedirPalabra(...) _pedir_cadena(false, (string_request_t){__VA_ARGS__})
#define pedirLinea(...)   _pedir_cadena( true, (string_request_t){__VA_ARGS__})

#define pedirCadenaScr(...) _pedir_cadenascr((stringscr_request_t){__VA_ARGS__})

#endif // end _EASY_IO_H
