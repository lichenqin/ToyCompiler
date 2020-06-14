/****************************************************/
/* File: tiny.y                                     */
/* The TINY Yacc/Bison specification file           */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/
%{
#define YYPARSER /* distinguishes Yacc output from other code files */

#include "type.h"
#include "scan.h"
#include "parse.h"

#define YYSTYPE TreeNode *
static char * savedName; /* for use in assignments */
static int savedLineNo;  /* ditto */
static TreeNode * savedTree; /* stores syntax tree for later return */

%}

%token WHILE IF THEN ELSE DO END IN OUT
%token PLUS MINUS TIMES DIVIDE LP RP EQUAL ASSIGN LT GT SEMI
%token INT10 INT8 INT16 FLO10 FLO8 FLO16
%token ID
%token ERROR 

%% /* Grammar for TINY */

program     : stmt_seq
                 { savedTree = $1;} 
            ;
stmt_seq    : stmt_seq SEMI stmt
                 { YYSTYPE t = $1;
                   if (t != NULL)
                   { while (t->sibling != NULL)
                        t = t->sibling;
                     t->sibling = $3;
                     $$ = $1; }
                     else $$ = $3;
                 }
            | stmt  { $$ = $1; }
            ;
stmt        : if_stmt { $$ = $1; }
            | while_stmt { $$ = $1; }
	    | assign_stmt { $$ = $1; }
            | in_stmt { $$ = $1; }
            | out_stmt { $$ = $1; }
            | error  { $$ = NULL; }
            ;
if_stmt     : IF exp THEN stmt_seq END
                 { $$ = newStmtNode(IfK);
                   $$->child[0] = $2;
                   $$->child[1] = $4;
                 }
            | IF exp THEN stmt_seq ELSE stmt_seq END
                 { $$ = newStmtNode(IfK);
                   $$->child[0] = $2;
                   $$->child[1] = $4;
                   $$->child[2] = $6;
                 }
            ;
while_stmt : WHILE exp DO stmt_seq
                 { $$ = newStmtNode(WhileK);
                   $$->child[0] = $2;
                   $$->child[1] = $4;
                 }
            ;
assign_stmt : ID { savedName = copyString(tokenString);
                   savedLineNo = lineno; }
              ASSIGN exp
                 { $$ = newStmtNode(AssignK);
                   $$->child[0] = $3;
                   $$->attr.name = savedName;
                   $$->lineno = savedLineNo;
                 }
            ;
in_stmt   : IN ID
                 { $$ = newStmtNode(InK);
                   $$->attr.name =
                     copyString(tokenString);
                 }
            ;
out_stmt  : OUT exp
                 { $$ = newStmtNode(OutK);
                   $$->child[0] = $2;
                 }
            ;
exp         : exp1 LT exp1 
                 { $$ = newExpNode(OpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->attr.op = LT;
                 }
            | exp1 GT exp1 
                 { $$ = newExpNode(OpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->attr.op = GT;
                 }
            | exp1 EQUAL exp1
                 { $$ = newExpNode(OpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->attr.op = EQUAL;
                 }
            | exp1 { $$ = $1; }
            ;
exp1        : exp1 PLUS exp2 
                 { $$ = newExpNode(OpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->attr.op = PLUS;
                 }
            | exp1 MINUS exp2
                 { $$ = newExpNode(OpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->attr.op = MINUS;
                 } 
            | exp2 { $$ = $1; }
            ;
exp2        : exp2 TIMES exp3 
                 { $$ = newExpNode(OpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->attr.op = TIMES;
                 }
            | exp2 DIVIDE exp3
                 { $$ = newExpNode(OpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->attr.op = DIVIDE;
                 }
            | exp3 { $$ = $1; }
            ;
exp3        : LP exp RP
                 { $$ = $2; }
            | INT10
                 { $$ = newExpNode(InterK);
                   $$->attr.val = atoi(tokenString);
                 }
            | INT8
                 { $$ = newExpNode(InterK);
                   $$->attr.val = atoi(tokenString);
                 }
            | INT16
                 { $$ = newExpNode(InterK);
                   $$->attr.val = atoi(tokenString);
                 }
            | FLO10
                 { $$ = newExpNode(FloK);
                   $$->attr.val = atoi(tokenString);
                 }
            | FLO8
                 { $$ = newExpNode(FloK);
                   $$->attr.val = atoi(tokenString);
                 }
            | FLO16
                 { $$ = newExpNode(FloK);
                   $$->attr.val = atoi(tokenString);
                 }
            | ID { $$ = newExpNode(IdK);
                   $$->attr.name =
                         copyString(tokenString);
                 }
            | error { $$ = NULL; }
            ;

%%

int yyerror(char * message)
{ fprintf(listing,"Syntax error at line %d: %s\n",lineno,message);
  fprintf(listing,"Current token: ");
  printToken(yychar,tokenString);
  Error = TRUE;
  return 0;
}

/* yylex calls getToken to make Yacc/Bison output
 * compatible with ealier versions of the TINY scanner
 */
static int yylex(void)
{ return getToken(); }

TreeNode * parse(void)
{ yyparse();
  return savedTree;
}

