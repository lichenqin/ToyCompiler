#ifndef _TYPE_H_
#define _TYPE_H_

# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>


//define Token Type
typedef enum token{
    /* Reserve Word*/
    WHILE, IF, THEN, ELSE, DO, END, IN, OUT,    /*add three new reserve word: end, in, out*/
    /* Special Symbol*/
    //PLUS, SUB, MULTIPLE, DIVIDE, BIGGER, LESSER, ASSIGN, EQUAL, SEMI,
    PLUS, MINUS, TIMES, DIVIDE, LP, RP, EQUAL, ASSIGN, LT, GT, SEMI,
    /* Integer Decimal Octal Hex*/
    INT10, INT8, INT16,
    /* Float Decimal Octal Hex*/
    FLO10, FLO8, FLO16,
    /* Identifier*/
    ID,
    /* Error*/
    ERROR,
    /* Interval*/
    INTER,
    /* End File*/
    ENDFI
}TokenType;

/* extern variable */
extern FILE * read;
extern FILE * output;

#ifndef True
#define True 1
#endif

#ifndef False
#define False 0
#endif

#endif
