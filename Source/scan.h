#ifndef _SCAN_H_
#define _SCAN_H_

# include "type.h"

/* define DFA state*/
typedef enum dfa_state{
    While, If, Then, Else, Do, End, In, Out, Plus, Minus, Times, Divide, Lp, Rp, Equal, Assign, Lt, Gt, Semi,
    Int10, Int8, Int16, f10, f8, f16, Id, Error,
    /* WHILE's middle state*/
    mw, mwh, mwhi, mwhil,
    /* IF's middle state*/
    mi,
    /* THEN's middle state and accept state*/
    mt, mth, mthe,
    /* ELSE's middle state and accept state*/
    me, mel, mels,
    /* DO's middle state and accept state*/
    md,
    /* END's middle state and accept state, END share me state with ELSE*/
    men,
    /* IN's middle state and accept state, IN share mi state with IF*/
    /* Out's middle state and accept state*/
    mo, mou,
    /* Special number's middle state and accept state */
    /* +, -, *, /, (, ), ==, =, <, >, ; 这里 = 与 == 之间存在转换关系 */ 
    /* Integer Number's middle state and accept state */
    zero, ox,
    /* Integer Number's middle state and accept state */
    dtf, htf, otf,
    /* Identifier's middle state and accept state */
    /* start state s0*/
    start,
    /* Error state*/
    /*END Of File*/
    Eof
}State;

FILE * read;
FILE * output;

/* define max length of identifier or number length */
#ifndef Max_Va_Length
#define Max_Va_Length 32
#endif

extern char String_buffer[Max_Va_Length];
extern int string_position;

/* getToken get token and return TokenType */
TokenType getToken();

/* check if the character is in range x to y in ascii*/
/* 0-9 1-9 0-7 a-z A-Z*/
int In_range( char temp, char x, char y);

/*判断在中间状态下 是否为间隔符*/
int Isinter( char temp);

/*判断是否为ID状态下的合法字符*/
int Isid( char temp );

/* print token type */
//void printToken( State );
void printToken( int );

/* print input string */
void printString();

/* copy variable string*/
char * copyString( );

/* strcat implementation in security mode*/
char * str_conjunction(char * pre_array, const char * appendex);

#endif