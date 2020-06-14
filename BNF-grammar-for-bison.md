#### 用于Yacc分析的BNF语法

s‘ -->	sq

sq -->	sq; statement

​			| statement

statement --> if-stm 

​					| while-stm

​					|assign-stm

​					| in-stm 

​					| out-stm 

if-stm --> `if` exp `then` sq `end`

​				| `if` exp `then` sq `else` sq `end`

while-stm -->	`while` exp `do` sq `end`

assign-stm---> `ID` `==` exp

in-stm -->	`in` `ID`

out-stm --> `out` `ID`

​					| `out` `number`

exp -->	exp equal p2 

​				| p2

​				| exp compare p2

equal -->	`==`

compare -->	`>` | `<`

p2 -->	p2 addop p3 | p3

addop -->	`+` | `-`

p3 -->	p3 mulop p4 | p4

mulop -->	`*` | `/`

p4 -->	`(` exp `)` | `number` | `ID`

