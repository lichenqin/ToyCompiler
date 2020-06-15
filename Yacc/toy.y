/****************/
/* Yacc For Toy */
/****************/

%{
#define YYPARSER

#include "type.h"
#include "scan.h"
#include "parse.h"

#define YYSTYPE TreeNode *
static char * savedName;
static TreeNode * savedTree;
%}

%token ENDFI 0	/*End file symbol*/
%token WHILE 1 IF 2 THEN 3 ELSE 4 DO 5 END 6 IN 7 OUT 8	/*Reserved word symbol*/
%token PLUS 9 MINUS 10 TIMES 11 DIVIDE 12 LP 13 RP 14 
%token EQUAL 15 ASSIGN 16 LT 17 GT 18 SEMI 19
%token INT10 20 INT8 21 INT16 22 FLO10 23 FLO8 24 FLO16 25
%token ID 26
%token ERROR 27

%%

program	: stmt_seq
		{ savedTree = $1; }
	;
stmt_seq: stmt_seq SEMI stmt
		{ YYSTYPE t = $1;
			if(t != NULL)
			{	while(t->sibling != NULL )
					t = t->sibling;
				t->sibling = $3;
				$$ = $1;
			}
			else	$$ = $3;}
	| stmt
		{ $$ = $1; }
	;
stmt	: if_stmt { $$ = $1; }
     	| whi_stmt { $$ = $1; }
	| ass_stmt { $$ = $1; }
	| in_stmt { $$ = $1; }
	| out_stmt { $$ = $1; }
	| error { $$ = NULL; }
	;
if_stmt	: IF exp THEN stmt_seq END
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
whi_stmt: WHILE exp DO stmt_seq
		{ $$ = newStmtNode(WhileK);
		  $$->child[0] = $2;
		  $$->child[1] = $4;
		}
	;
ass_stmt: ID 	{ savedName = copyString();}
	  ASSIGN exp
		{ $$ = newStmtNode(AssignK);
		  $$->child[0] = $3;
		  $$->attr.name = saveName;
		}
	;
in_stmt	: IN ID
		{ $$ = newStmtNode(Ink);
		  $$->attr.name = copyString();
		}
	;
out_stmt: OUT exp
		{ $$ = newStmtNode(OutK);
		  $$->child[0] = $2;
		}
	;
exp	: exp LT exp1
    		{ $$ = newExpNode(OpK);
		  $$->child[0] = $1;
		  $$->child[1] = $3;
		  $$->addr.op = LT;
		}
    	| exp GT exp1
		{ $$ = newExpNode(OpK);
		  $$->child[0] = $1;
		  $$->child[1] = $3;
		  $$->attr.op = GT;
		}
    	| exp EQUAL exp1
		{ $$ = newExpNode(OpK);
		  $$->child[0] = $1;
		  $$->child[1] = $3;
		  $$->attr.op = EQUAL;
		}
	;
exp1	: exp1 PLUS exp2
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
	;
exp2	: exp2 TIMES exp3
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
	;
exp3	: LP exp RP
     		{ $$ = $2; }
     	| INT10
		{ $$ = newExpNode(InterK);
		  savedName = copyString();
		  $$->attr.ival = convertI(savedName, 10, 0);
		  free(savedName);
		}
	| INT8
		{ $$ = newExpNode(InterK);
		  savedName = copyString();
		  $$->attr.ival = convertI(savedName, 8, 1);
		  free(savedName);
		}
	| INT16
		{ $$ = newExpNode(InterK);
		  savedName = copyString();
		  $$->attr.ival = convertI(savedName, 16, 2)
		  free(savedName);
		}
	| FLO10
		{ $$ = newExpNode(FloK);
		  savedName = copyString();
		  $$->attr.fval = convertF(savedName, 10, 0);
		  free(savedName);
		}
	| FLO8
		{ $$ = newExpNode(FloK);
		  savedName = copyString();
		  $$->attr.fval = convertF(savedName, 8, 1);
		  free(savedName);
		}
	| FLO16
		{ $$ = newExpNode(FloK);
		  savedName = copyString();
		  $$->attr.fval = convertF(savedName, 16, 2);
		  free(savedName);
		}
	| ID
		{ $$ = newExpNode(IdK);
		  $$->attr.name = copyString();
		}
	| ERROR
		{ $$ = NULL;}
	;

%%

int yyerror( char * message ){
	printf("Syntax error %s\n",message);
	printf("Current token: ");
	printToken(yychar);
	Error = True;
	return 0;
}

static int yylex( void ){
	return getToken();
}

TreeNode * parse( void ){
	yyparse();
	return savedTree;
}
