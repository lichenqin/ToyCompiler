#ifndef _SCAN_H_
#define _SCAN_H_

# include "type.h"

/* define DFA state*/
typedef enum{
    /* start state s0*/
    start,
    /* WHILE's middle state and accept state*/
    mw, mwh, mwhi, mwhil, WHILE,
    /* IF's middle state and accept state*/
    mi, IF,
    /* THEN's middle state and accept state*/
    mt, mth, mthe, THEN,
    /* ELSE's middle state and accept state*/
    me, mel, mels, ELSE,
    /* DO's middle state and accept state*/
    md, DO,
    /* Special number's middle state and accept state */
    /* +, -, *, /, (, ), ==, =, <, >, ; 这里 = 与 == 之间存在转换关系 */ 
    PLUS, MINUS, TIMES, DIVIDE, LP, RP, EQUAL, ASSIGN, LT, GT, SEMI,
    /* Integer Number's middle state and accept state */
    zero, INT10, ox, INT16, INT8,
    /* Integer Number's middle state and accept state */
    dtf, F10, htf, F16, otf, F8,
    /* Identifier's middle state and accept state */
    ID,
    /* Error state*/
    ERROR,
    /*END File*/
    END
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
inline int In_range( char temp, char x, char y);

/*判断在中间状态下 是否为间隔符*/
inline int Isinter( char temp);

/*判断是否为ID状态下的合法字符*/
inline int Isid( char temp );

/* print token type */
void printToken( TokenType token);

/* print input string */
void printString();

/* strcat implementation in security mode*/
char * str_conjunction(char * pre_array, const char * appendex);

#endif