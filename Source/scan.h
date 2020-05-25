#ifndef _SCAN_H_
#define _SCAN_H_

# include "type.h"

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
    /* Special number's middle state and accept state */
    /* +, -, *, /, (, ), ==, =, <, >, ; 这里 = 与 == 之间存在转换关系 */ 
    PLUS, MINUS, TIMES, DIVIDE, LP, RP, EQUAL，ASSIGN, LT, GT, SEMI,
    /* Integer Number's middle state and accept state */
    ZERO, INT10, OX, INT16, INT8,
    /* Integer Number's middle state and accept state */
    DTF, F10, HTF, F16, OTF, F8,
    /* Identifier's middle state and accept state */
    ID_, ID
}State;

FILE * read;
FILE * output;

/* define max length of identifier or number length */
#ifndef Max_Va_Length
#define Max_Va_Length 32
#endif

/* define max length of line buff. */
/* Note: the real number of accept character are Max_Line-2 */
#ifndef Max_Line
#define Max_Line 256
#endif

/* getToken get token and return TokenType */
TokenType getToken();

/* check if the character is in range x to y in ascii*/
/* 0-9 1-9 0-7 a-z A-Z*/
inline bool In_range( char temp, char x, char y);

/* print token type */
void printToken( TokenType token);

/* print input string */
void printString();

/* strcat implementation in security mode*/
char * str_conjunction(char * pre_array, const char * appendex);

#endif