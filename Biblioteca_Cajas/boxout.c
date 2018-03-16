/*===================================================*
 * boxout.h: Source code                             *
 * Some easy functions for printing decorated output *
 *===================================================*/

// ##### Auxiliar libraries #####
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "boxout.h"
#include "box_list.h"

//  ##### PRIVATE DECLARATIONS #####

#define putSpaces(n) fprintf(out, "%*s", (n), "")

#ifdef __unix__
/*
 * cntExtraBytes: const char  *str, int32_t len -> int32_t
 * This function is used to know the printable length of a
 * string, since utf-8 uses variable length chars we
 * have to count how many bytes don't have to be considered
 * when dealing with the string.
 */
static int32_t cntExtraBytes(const char *str) {
    int32_t extra = 0;

    for (int index = 0; str[index]; ++index) {
        if ( ( str[index] & 240 ) == 240 ) {
            extra += 3;
            index += 3;
        } else if ( ( str[index] & 224 ) == 224 ) {
            extra += 2;
            index += 2;
        } else if ( ( str[index] & 192 ) == 192 ) {
            ++extra;
            ++index;
        } else if (  str[index] == '\t' ) {
            extra -= 7;
        }
    }

    return extra;
}
#endif // end __unix__

/*
 * print_underlined: char *str, int32_t _space -> void
 * Description: Prints the string of the
 * argument underlined by underscores and
 * indenten "space" whitespaces from the
 * left part of the screen.
 */
static void print_underlined (
        const char * str,
        const char * end,
        int32_t space,
        const char * line_char,
        FILE * out
) {
    int32_t length = strlen(str);

#ifdef __unix__
    length -= cntExtraBytes(str);
#endif // end __unix__

    putSpaces(space);   // Indenting message
    fprintf(out, "%s\n", str);

    putSpaces(space);   // Indenting message

    for (int i = 0; i < length; ++i)
        printf("%s", line_char);

    fputs(end, out);
}

void print_underlined_helper(underlined_arg_t args) {
    print_underlined(args.str ? args.str : "          ",
                     args.end ? args.end : "\n\n",
                     args.space >= 0 ? args.space : 0,
                     args.line ? args.line : "_",
                     args.out ? args.out : stdout);

}

/*
 *  _print_inside_box_multiline: char *str, int32_t _space , int32_t box_size-> void
 *  Description: Function that tokenizes a the "str"
 *  argument by its \n (New line characters) and print
 *  everyone of the tokens in a line of "box_size" width
 *  surrounded by a box.
 *  The box can be separated "_space" tabs from the left of
 *  the screen
 */
static void print_inside_box (
        const char * str,
        const char * end,
        int32_t space,
        int32_t box_size,
        const char ** boxset,
        enum direction dir,
        FILE * out
) {
    char *str_cpy = (char *) malloc(sizeof(char) * strlen(str) + 1);
    strcpy(str_cpy, str);

    char *line; // For retrieving one line at a time

    // First, replaces tabs to spaces
    {
        char *pos = str_cpy;
        while ( (pos = strchr(pos, '\t')) != NULL )
            *pos = ' ';
    }

    // Print the top
    putSpaces(space);
    fprintf(out, "%s", boxset[ESI]);
    for (int i = 0; i < box_size; ++i)
        fprintf(out, "%s", boxset[BHZ]);
    fprintf(out, "%s\n", boxset[ESD]);

    // Print the middle
    line = strtok(str_cpy, "\n");

    while ( line != NULL ) {
        int phisical_line_len = strlen(line);
        int left_space, right_space;
#ifdef __unix__
        phisical_line_len -= cntExtraBytes(line);
#endif
        assert(((void)"La longitud de la cadena es mayor a la de la caja para para contenerlo", phisical_line_len <= box_size - 2));

        if ( dir == DIR_CENTER ) {
            left_space = right_space = (box_size - 2 - phisical_line_len) / 2;
            left_space += phisical_line_len % 2;
        } else if ( dir == DIR_RIGHT ) {
            left_space  = (box_size - 2 - phisical_line_len);
            right_space = 0;
        } else /* Default direction is left */ {
            left_space = 0;
            right_space = (box_size - 2 - phisical_line_len);
        }

        fprintf(out, "%*s", space, "");
        fprintf(out, "%s %*s%s%*s %s\n",
                boxset[BVE],
                left_space, "", line, right_space, "",
                boxset[BVE]);
        line = strtok(NULL, "\n");
    }

    // Print the bottom
    putSpaces(space);
    fprintf(out, "%s", boxset[EII]);
    for(int i = 0; i < box_size; ++i)
        fprintf(out, "%s", boxset[BHZ]);
    fprintf(out, "%s", boxset[EID]);

    fputs(end, out);
    free(str_cpy);
}

void print_inside_box_helper(struct box_arg args) {
    print_inside_box(args.str ? args.str : "",
                     args.end ? args.end : "\n\n",
                     args.space >= 0 ? args.space : 0,
                     args.box_size > 0 ? args.box_size : 78,
                     args.boxset ? args.boxset : CAJA2,
                     args.dir,
                     args.out ? args.out : stdout);
}

/*
 * _pdotted: char *str, int32_t _space , int32_t box_size-> void
 * Description: Function that print the string inside
 *  a lot of asterisks.
 */
static void print_dotted (
        const char * str,
        const char * end,
        int32_t space,
        FILE * out
) {
    int_fast32_t length = strlen(str) + 8;

#ifdef __unix__
    length -= cntExtraBytes(str);
#endif

#define DOT_LINE(even) ({                                               \
            fprintf(out, "%*s", space + even, "");                      \
            for (int i = 0; i < length / 2; i++) fprintf(out, " *");    \
        })

    DOT_LINE(false); putc('\n', out);

    DOT_LINE(true); putc('\n', out);

    // Print the middle
    fprintf(out, "%*s", space, "");
    fprintf(out, " * *%s", str);
    fprintf(out, "%s\n", length % 2? "* *": " * *");

    DOT_LINE(true); putc('\n', out);
    DOT_LINE(false);

    fputs(end, out);
}

void print_dotted_helper(struct dotted_arg args) {
    print_dotted(args.str ? args.str : "",
                 args.end ? args.end : "\n\n",
                  args.space >= 0 ? args.space : 0,
                  args.out ? args.out : stdout);
}
