/*===================================================*
 * boxout.h: Source code                             *
 * Some easy functions for printing decorated output *
 *===================================================*/

#ifndef _BOXNMORE_H
#define _BOXNMORE_H

// ##### Public libraries #####
#include <stdint.h>
#include <stdio.h>

//  ##### PUBLIC DECLARATIONS #####
enum direction {
    DIR_LEFT,
    DIR_CENTER,
    DIR_RIGHT,
};

typedef struct underlined_arg {
    int _;
    const char * str;
    const char *end;
    int32_t space;
    const char * line;
    FILE * out;
} underlined_arg_t;

typedef struct box_arg {
    int _;
    const char * str;
    const char * end;
    int32_t space;
    int32_t box_size;
    const char ** boxset;
    enum direction dir;
    FILE * out;
} box_arg_t;

typedef struct dotted_arg {
    int _;
    const char * str;
    const char * end;
    int space;
    FILE * out;
} dotted_arg_t;

void print_inside_box_helper(box_arg_t args);
void print_underlined_helper(underlined_arg_t args);
void print_dotted_helper(dotted_arg_t args);

#define PrintUnderlined(...)                                                \
        print_underlined_helper((underlined_arg_t){ ._=0, __VA_ARGS__ })
#define PrintInsideBox(...)                                                 \
        print_inside_box_helper((box_arg_t){ ._=0, __VA_ARGS__ })
#define PrintDotted(...)                                                    \
        print_dotted_helper((dotted_arg_t){ ._=0, __VA_ARGS__ })

#endif // end _BOXNMORE_H
