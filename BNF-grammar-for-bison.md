#### 用于Yacc分析的BNF语法

s‘ -->	s

s  -->	s; statement

​			| statement

statement --> if-stm 

​					| while-stm 

​					| in-stm 

​					| out-stm 

​					| p0

if-stm --> `if` exp-stm `then` statement_sequence `end`

​				| `if` exp-stm `then` statement_sequence `else` statement_sequence `end`

while-stm -->	`while` exp-stmt `do` statement_sequence `end`

in-stm -->	`in` `ID`

out-stm --> `out` `ID`

​					| `out` `number`

p0 -->	p0 assign p1 | p1

assign -->	`=`

p1 -->	p1 equal p2 | p2

equal -->	`==`

p2 -->	p2 compare p3 | p3

compare -->	`>` | `<`

p3 -->	p3 addop p4 | p4

addop -->	`+` | `-`

p4 -->	p4 mulop p5 | p5

mulop -->	`*` | `/`

p5 -->	`(` p0 `)` | `number` | `ID`