#ifndef _TYPE_H_
#define _TYPE_H_

# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>


//define Token Type
typedef enum{
    /* Reserve Word*/
    WHILE, IF, THEN, ELSE, DO,
    /* Special Symbol*/
    //PLUS, SUB, MULTIPLE, DIVIDE, BIGGER, LESSER, ASSIGN, EQUAL, SEMI,
    +, -, *, /, (, ), EQUAL, ASSIGN, LT, GT, SEMI,
    /* Integer Decimal Octal Hex*/
    INT10, INT8, INT16,
    /* Float Decimal Octal Hex*/
    FLO10, FLO8, FLO16,
    /* Identifier*/
    ID,
    /* Error*/
    ERROR
}TokenType;

/* define DFA state*/
typedef enum{
    /* start state s0*/
    start,
    /* WHILE's middle state and accept state*/
    W, WH, WHI, WHIL, WHILE,
    /* IF's middle state and accept state*/
    I, IF,
    /* THEN's middle state and accept state*/
    T, TH, THE, THEN,
    /* ELSE's middle state and accept state*/
    E, EL, ELS, ELSE,
    /* DO's middle state and accept state*/
    D, DO,
    /* Special number's middle state and accept state 这里缺少:=中的中间状态*/
    PLUS, MINUS, TIMES, DIVIDE, LP, RP, EQUAL, ASSIGN, LT, GT, SEMI,
    /* Integer Number's middle state and accept state*/
    ZERO, INT10, OX, INT16, INT8,
    /* Integer Number's middle state and accept state*/
    DTF, F10, HTF, F16, OTF, F8,
    /* Identifier's middle state and accept state*/
    ID_, ID
}State;

/* extern variable */
extern FILE * read;
extern FILE * output;

#endif
