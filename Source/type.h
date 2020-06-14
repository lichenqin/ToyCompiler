#ifndef _TYPE_H_
#define _TYPE_H_

# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>

/* extern variable */
extern FILE * read;
extern FILE * output;

#ifndef True
#define True 1
#endif

#ifndef False
#define False 0
#endif

extern int lineno; /* source line number for listing */

/********Scanner Part Token Type Table********/
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

/********Parser Part TreeNode Structure********/
typedef enum {StmtK,ExpK} NodeKind;
typedef enum {IfK,WhileK,AssignK,InK,OutK} StmtKind;
typedef enum {OpK,InterK,FloK,IdK} ExpKind;

/* ExpType is used for type checking */
typedef enum {Void,Integer,Float} ExpType;

#define MAXCHILDREN 3

typedef struct treeNode{ 
    struct treeNode * child[MAXCHILDREN];
    struct treeNode * sibling;
    NodeKind nodekind;
    union { StmtKind stmt; ExpKind exp;} kind;
    union { TokenType op;
             int ival;
             float fval;
             char * name;
    }attr;
    ExpType type; /* for type checking of exps */
}TreeNode;

#endif