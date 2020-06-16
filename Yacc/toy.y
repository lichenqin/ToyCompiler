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

%token YWHILE 1 YIF 2 YTHEN 3 YELSE 4 YDO 5 YEND 6 YIN 7 YOUT 8	/*Reserved word symbol*/
%token YPLUS 9 YMINUS 10 YTIMES 11 YDIVIDE 12 YLP 13 YRP 14 
%token YEQUAL 15 YASSIGN 16 YLT 17 YGT 18 YSEMI 19
%token YINT10 20 YINT8 21 YINT16 22 YFLO10 23 YFLO8 24 YFLO16 25
%token YID 26
%token YERROR 27

%%
program	: stmt_seq
		{savedTree = $1;
		 printf("Syntax Tree Construct Successful!\n");
		}
	;
stmt_seq: stmt_seq YSEMI stmt
		{YYSTYPE t = $1;
		if(t != NULL){
			while(t->sibling != NULL)
				t = t->sibling;
			t->sibling = $3;
			$$ = $1;
		}
		else
			$$ = $3;
		}
	| stmt
		{$$ = $1;
		 printf("State: stmt\n");
		}
	;
stmt	: if_stmt
		{$$ = $1;
		 printf("State: if_stmt\n")
		}
     	| whi_stmt
		{$$ = $1;
		 printf("State: whi_stmt\n");
		}
	| ass_stmt
		{$$ = $1;
		 printf("State: ass_stmt\n");
		}
	| in_stmt
		{$$ = $1;
		 printf("State: in_stmt\n")
		}
	| out_stmt
		{$$ = $1;
		 printf("State: out_stmt\n");
		}
	| YERROR
		{$$ = NULL;}
	;
if_stmt	: YIF exp YTHEN stmt_seq YEND
		{$$ = newStmtNode(IfK);
		 $$->child[0] = $2;
		 $$->child[1] = $4;
		}
	| YIF exp YTHEN stmt_seq YELSE stmt_seq YEND
		{$$ = newStmtNode(IfK);
		 $$->child[0] = $2;
		 $$->child[1] = $4;
		 $$->child[2] = $6;
		}
	;
whi_stmt: YWHILE exp YDO stmt_seq YEND
		{$$ = newStmtNode(WhileK);
		 $$->child[0] = $2;
		 $$->child[1] = $4;
		}
	;
ass_stmt: YID
		{savedName = copyString();}
	  YASSIGN exp
		{$$ = newStmtNode(AssignK);
		 $$->attr.name = savedName;
		 $$->child[0] = $3;
		}
	;
in_stmt	: YIN YID
		{$$ = newStmtNode(InK);
		 $$->attr.name = copyString();
		 printf("State: IN\n");
		 printf("token:");
		 printToken(yychar);
		}
	;
out_stmt: YOUT exp
		{$$ = newStmtNode(OutK);
		 $$->child[0] = $2;
		}
	;
exp	: exp YEQUAL exp1
		{ $$ = newExpNode(OpK);
		  $$->child[0] = $1;
		  $$->child[1] = $3;
		  $$->attr.op = EQUAL;
		}
   	| exp YLT exp1
		{ $$ = newExpNode(OpK);
		  $$->child[0] = $1;
		  $$->child[1] = $3;
		  $$->attr.op = LT;
		}
   	| exp YGT exp1
		{ $$ = newExpNode(OpK);
		  $$->child[0] = $1;
		  $$->child[1] = $3;
		  $$->attr.op = GT;
		}
   	| exp1
		{$$ = $1;}
   	;
exp1	: exp1 YPLUS exp2
		{ $$ = newExpNode(OpK);
		  $$->child[0] = $1;
		  $$->child[1] = $3;
		  $$->attr.op = PLUS;
		}
    	| exp1 YMINUS exp2
		{ $$ = newExpNode(OpK);
		  $$->child[0] = $1;
		  $$->child[1] = $3;
		  $$->attr.op = MINUS;
		}
    	| exp2
		{$$ = $1;}
    	;
exp2	: exp2 YTIMES exp3
		{ $$ = newExpNode(OpK);
		  $$->child[0] = $1;
		  $$->child[1] = $3;
		  $$->attr.op = TIMES;
		}
    	| exp2 YDIVIDE exp3
		{ $$ = newExpNode(OpK);
		  $$->child[0] = $1;
		  $$->child[1] = $3;
		  $$->attr.op = DIVIDE;
		}
    	| exp3
		{$$ = $1;}
    	;
exp3	: YLP exp YRP
		{$$ = $2;}
    	| YINT10
		{ $$ = newExpNode(InterK);
		  savedName = copyString();
		  $$->attr.ival = convertI(savedName, 10, 0);
		  printf("State:");
		  printToken(yychar);
		  printf("Name:");
		  printf("%s\n",savedName);
		  free(savedName);
		}
    	| YINT8
		{ $$ = newExpNode(InterK);
		  savedName = copyString();
		  $$->attr.ival = convertI(savedName, 8, 1);
		  printf("State:");
		  printToken(yychar);
		  printf("Name:");
		  printf("%s\n",savedName);
		  free(savedName);
		}
    	| YINT16
		{ $$ = newExpNode(InterK);
		  savedName = copyString();
		  $$->attr.ival = convertI(savedName, 16, 2);
		  printf("State:");
		  printToken(yychar);
		  printf("Name:");
		  printf("%s\n",savedName);
		  free(savedName);
		}
    	| YFLO10
		{ $$ = newExpNode(FloK);
		  savedName = copyString();
		  $$->attr.fval = convertF(savedName, 10, 0);
		  printf("State:");
		  printToken(yychar);
		  printf("Name:");
		  printf("%s\n",savedName);
		  free(savedName);
		}
    	| YFLO8
		{ $$ = newExpNode(FloK);
		  savedName = copyString();
		  $$->attr.fval = convertF(savedName, 8, 1);
                  printf("State:");
		  printToken(yychar);
		  printf("Name:");
		  printf("%s\n",savedName);
		  free(savedName);
		}
    	| YFLO16
		{ $$ = newExpNode(FloK);
		  savedName = copyString();
		  $$->attr.fval = convertF(savedName, 16, 2);
                  printf("State:");
		  printToken(yychar);
		  printf("Name:");
		  printf("%s\n",savedName);
		  free(savedName);
		}
    	| YID
		{ $$ = newExpNode(IdK);
		  $$->attr.name = copyString();
                  printf("State:");
		  printToken(yychar);
		}
    	| YERROR
		{$$ = NULL;}
    	;

%%

int yyerror( char * message ){
	printf("Syntax error %s\n",message);
	printf("Current token: ");
	printToken(yychar);
	return 0;
}

int yylex( void ){
	return getToken();
}

TreeNode * parse(void)
{ yyparse();
  return savedTree;
}
