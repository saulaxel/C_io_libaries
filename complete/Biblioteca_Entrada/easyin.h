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

char _usr_input[100]; // Just read up to 100 chars from the buffer
bool _valid_input; // Boolean flag to validate input

/*
 * _read_line: int i -> void
 * Description: This function reads un to "i" chars 
 * (up to 100) from the stdin and stores in the
 * "_usr_input" variable
 */
void _read_line(int i) {
    i %= 101;
    fgets(_usr_input, i, stdin);
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
int _askfint(
        const char *_request,
        const char *_err_msg,
        int _minval,
        int _maxval
) {
    int d;

    printf("%s",_request);
    _read_line(100);
    _valid_input = sscanf(_usr_input, "%d", &d);
    _valid_input = _valid_input && d >= _minval && d <= _maxval;

    while( !_valid_input ) {
        printf("%s",_err_msg);

        _read_line(100);
        _valid_input = sscanf(_usr_input, "%d", &d);
        _valid_input = _valid_input && d >= _minval && d <= _maxval;
    }

    return d;
}

/*
 * _askffloat: 
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
float _askffloat(
        const char *_request,
        const char *_err_msg,
        float _minval,
        float _maxval
) {
    float f;

    printf("%s",_request);
    _read_line(100);
    _valid_input = sscanf(_usr_input, "%f", &f);
    _valid_input = _valid_input && f >= _minval && f <= _maxval;

    while( !_valid_input ) {
        printf("%s",_err_msg);

        _read_line(100);
        _valid_input = sscanf(_usr_input, "%f", &f);
        _valid_input = _valid_input && f >= _minval && f <= _maxval;
    }

    return f;
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
        const char *_request,
        const char *_err_msg,
        char _minval,
        char _maxval
) {
    char c;

    printf("%s",_request);
    c = getch();
    putchar('\n');

    _valid_input = (c >= _minval) && (c <= _maxval);

    while( !_valid_input ) {
        printf("%s",_err_msg);
        c = getch();
        putchar('\n');

        _valid_input = (c >= _minval) && (c <= _maxval);
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
        char *s,
        const char *_request,
        int _max_size
) {
    printf("%s",_request);
    _read_line(_max_size);
    sscanf(_usr_input, "%s", s);
}

/*
 * _askfline: char *s, const char *_request, int _max_size
 * Description: Asks the user for a string whit the 
 * "_request" message and stores it in "s". If the input 
 * string is larger than "_max_size" the string will be cut
 * but the invisible characters won't be able to do so.
 */
void _askfline(
        char *s,
        const char *_request,
        int _max_size
) {
    _max_size %= 101;

    char _format_[10];
    sprintf(_format_,"%%%d[^\n]", _max_size);

    printf("%s",_request);
    _read_line(_max_size);

    sscanf(_usr_input, _format_, s);
}

//  ##### PUBLIC DECLARATIONS #####  \\

/*
 * pedirEntero: char *peticion -> int
 * Description: Request an int from the user while the entry
 * is not valid and return its value.
 */
int pedirEntero(char *peticion) {
    _askfint(peticion, "", INT_MIN, INT_MAX);
}

/*
 * pedirEnteroErr: char *peticion, char *mensaje_error -> int
 * Description: Like pedirEntero but also displays an 
 * error message for every invalid entry.
 */
int pedirEnteroErr(char *peticion, char *mensaje_error) {
    _askfint(peticion, mensaje_error, INT_MIN, INT_MAX);
}

/*
 * pedirEnteroLim: char *peticion, int min, int max -> int
 * Description: Like pedirEntero but also validates the range
 * of the value withe the "min" and "max" values.
 */
int pedirEnteroLim(char *peticion, int min, int max) {
    _askfint(peticion, "", min, max);
}

/*
 * pedirEnteroErrLim: 
 *      char *peticion, char *mensaje_error,
 *      int min, int max
 *      -> int
 * Description: Does both of the added functionalities of the 
 * previous int functions.
 */
int pedirEnteroErrLim(char *peticion, char *mensaje_error, int min, int max) {
    _askfint(peticion, mensaje_error, min, max);
}

/*
 * pedirCaracter: char *peticion -> char
 * Description: Request a char from the user and return its value
 */
char pedirCaracter(char *peticion) {
    _askfchar(peticion, "", SCHAR_MIN, SCHAR_MAX);
}

/*
 * pedirCaracterLim: char *peticion, char *mensaje_error -> char
 * Description: Similar to pedirCaracter but also validates
 * if the entry is within a range of values.
 */
char pedirCaracterLim(char *peticion, char min, char max) {
    _askfchar(peticion, "", min, max);
}

/*
 * pedirCaracterErrLim:
 *      char *peticion, char *mensaje_error,
 *      char min, char max
 *      -> char
 * Description: Request a char from the user, validates if the range 
 * is valid and if not so displays a message and request another value 
 * into a cicle.
 */
char pedirCaracterErrLim(char *peticion, char *mensaje_error, char min, char max) {
    _askfchar(peticion, mensaje_error, min, max);
}

/*
 * pedirFlotante: char *peticion -> float
 * Description: Request a float from the user while the entry
 * is not valid and return its value.
 */
float pedirFlotante(char *peticion) {
    _askffloat(peticion, "", -FLT_MAX, FLT_MAX);
}

/*
 * pedirEnteroErr: char *peticion, char *mensaje_error -> float
 * Description: Like pedirFlotante but also displays an 
 * error message for every invalid entry.
 */
float pedirFlotanteErr(char *peticion, char *mensaje_error) {
    _askffloat(peticion, mensaje_error, -FLT_MAX, FLT_MAX);
}

/*
 * pedirFlotanteLim: char *peticion, float min, float max -> float
 * Description: Like pedirFlotante but also validates the range
 * of the value withe the "min" and "max" values.
 */
float pedirFlotanteLim(char *peticion, float min, float max) {
    _askffloat(peticion, "", min, max);
}

/*
 * pedirFlotanteErrLim: 
 *      char *peticion, char *mensaje_error,
 *      float min, float max
 *      -> float
 * Description: Does both of the added functionalities of the 
 * previous  float functions.
 */
float pedirFlotanteErrLim(char *peticion, char *mensaje_error, float min, float max) {
    _askffloat(peticion, mensaje_error, min, max);
}

/*
 * pedirPalabra: char *cadena, char *peticion -> void
 * Description: Request a string that stores in "cadena".
 * If the string has more than 100 chars or it has invisible
 * characters it will be cut off before them.
 */
void pedirPalabra(char *cadena, char *peticion) {
    _askfwrd(cadena, peticion, 100);
}

/*
 * pedirLinea: char *cadena, char *peticion, int largo_maximo -> void
 * Description: Request a string that stores in "cadena".
 * If the string has more than 100 chars its cut off.
 */
void pedirLinea(char *cadena, char *peticion, int largo_maximo) {
    _askfline(cadena, peticion, largo_maximo);
}

#endif // end _EASY_IO_H
