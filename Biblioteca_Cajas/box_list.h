/*************************************************************/
/* Biblioteca : caracteres_espaciales.                       */
/* DescripciOn: Define un conjunto de macros que             */
/*              representan los carActeres especiales de     */
/*              uso frecuente en el espaniol. Principalmente */
/*              las vocales acentuadas y tambiEn algunos     */
/*              sImbolos de dibujo. La definiciOn            */
/*              se hace tomando en cuenta el sistema.        */
/*************************************************************/

#ifndef _CARACTERES_ESPECIALES_H
#define _CARACTERES_ESPECIALES_H

/*========================*
 * CarActeres para dibujo *
 *========================*/

/**
 * Dibujo de cajas:
 *
 *      0    8     4          1
 *      +----------+----------+     0 - Esquina superior izquierda
 *      |          |          |     1 - Esquina superior derecha
 *      |          |          |     2 - Esquina inferior derecha
 *      |          |          |9    3 - Esquina inferior izquierda
 *      |          |          |     4 - Truncamiento superior
 *     7|----------+10--------|5    5 - Truncamiento derecho
 *      |          |          |     6 - Truncamiento inferior
 *      |          |          |     7 - Truncamiento izquierdo
 *      |          |          |     8 - Barra horizontal
 *      |          |          |     9 - Barra vertical
 *      +---------------------+     10- Centro
 *      3          6          2
 */

#define ESQUINA_SUPERIOR_IZQUIERDA  0
#define ESI                         0

#define ESQUINA_SUPERIOR_DERECHA    1
#define ESD                         1

#define ESQUINA_INFERIOR_DERECHA    2
#define EID                         2

#define ESQUINA_INFERIOR_IZQUIERDA  3
#define EII                         3

#define TRUNCAMIENTO_SUPERIOR       4
#define TSU                         4

#define TRUNCAMIENTO_DERECHO        5
#define TDE                         5

#define TRUNCAMIENTO_INFERIOR       6
#define TIN                         6

#define TRUNCAMIENTO_IZQUIERDO      7
#define TIZ                         7

#define BARRA_HORIZONTAL            8
#define BHZ                         8

#define BARRA_VERTICAL              9
#define BVE                         9

#define CRUZ_CENTRO                 10
#define CEN                         10

extern const char * CAJA1[11];
extern const char * CAJA2[11];
extern const char * CAJA3[11];


#endif // Fin _CARACTERES_ESPECIALES_H
