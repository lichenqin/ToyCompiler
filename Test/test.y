%token A 1 B 2 C 3

%%

start	:start ';' sq
	|sq
	;
sq	:A '+' term
   	|term
	;
term	:B
     	|C
	;
%%
