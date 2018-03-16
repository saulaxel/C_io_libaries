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
    int _;
    const char * prompt;
    const char * error_message;
    int min;
    int max;
} int_request_t;

typedef struct {
    int _;
    const char * prompt;
    const char * error_message;
    double min;
    double max;
} double_request_t;

typedef struct {
    int _;
    char * s;
    const char * prompt;
    int max;
} string_request_t;

typedef struct {
    int _;
    const char * prompt;
    const char * error_message;
    int (* valid_char)(int);
    const char * sep;
    bool hidden;
} char_request_t;

typedef struct {
    int _;
    char * s;
    const char * prompt;
    const char * error_message;
    const char * range_message;

    int (* valid_char)(int);
    int (* valid_str)(const char *);

    int min;
    int max;

    bool hidden;
} stringscr_request_t;

// ##### FUNCTION PROTOTYPES #####

void get_string_helper(stringscr_request_t args);
void get_word_line_helper(bool line, string_request_t args);
double get_double_helper(double_request_t args);
char get_char_helper(char_request_t args);
int get_int_helper( int_request_t args );

//  ###############################################
//  # Macrofunctions for direct use               #
//  ###############################################

#define getInt(...)                                                         \
        get_int_helper((int_request_t) { ._=0, __VA_ARGS__ })

#define getChar(...)                                                        \
        get_char_helper((char_request_t) { ._=0, __VA_ARGS__ })

#define getDouble(...)                                                      \
        get_double_helper((double_request_t) { ._=0, __VA_ARGS__})

#define getWord(...)                                                        \
        get_word_line_helper(false, (string_request_t) { ._=0,  __VA_ARGS__ })

#define getLine(...)                                                        \
        get_word_line_helper_helper(true, (string_request_t){ ._=0, __VA_ARGS__ })

#define getString(...)                                                      \
        get_string_helper((stringscr_request_t){ ._=0, __VA_ARGS__ })

#endif // end _EASY_IO_H
