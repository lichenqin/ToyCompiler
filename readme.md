## Project: Toy Compiler

#### 说明:

暂时有三个文件夹:

- Source中是源码部分
- Test是测试部分 因为Linux上要写cmake太麻烦 所以写在一个test.c里测试
- Yacc中保存了 `toy language` 的Yacc实现语法和 `toy.y` 

Source中有:

- type.h 定义token类型 定义抽象语法书结构 导入<stdlib.h> <stdio.h> 是所有文件的基础
- scan.h 声明scanner部分所用函数与结构
- scan.c 实现 其中getToken()最重要
- parse.h 声明parse过程用到的函数
- parse.c 实现 其中parse()最重要
- main.c 主函数 串连scanner parser code三部分
- etc

Test中有:

- test.c
- test 编译生成的可执行文件
- leec.tiny 测试用文件
- etc

Yacc中有:

- Yacc/Bison BNF文法: toy描述
- toy.y
- etc



#### 符号定义规则:

**Identifier:** 字母开头, 可以包括数字、字母、下划线，最多31位

**Number:** 包括int_10、int_8、int_16、float_10、float_8、float_16，最多31位

**Special Number:** 包括 + - * / ( ) > < = == 其余均不包含

**Reserve Word:** 包括IF THEN ELSE DO WHILE IN OUT END



#### 用法

```
>> toy filename.tiny
```

控制台输出TokenType以及对应的字符串, 相关语法树。

同时包含 <kbd>filename.tiny.out</kbd>的输出文件 输出内容与控制台显示内容相同(暂未实现)。



#### BNF语法:

- 添加了三个新的关键字: `end` `in` `out`

- 在exp状态下，既要保持左优先性，也要保持双目运算符号的优先级



start -->	statement_sequence

statement_sequence -->	statement_sequence; statement| statement

statement --> if-stm | while-stm | in-stm | out-stm | assign-stm

if-stm --> `if` exp `then` statement_sequence `end`

​				| `if` exp `then` statement_sequence `else` statement_sequence `end`

while-stm -->	`while` exp `do` statement_sequence `end`

in-stm -->	`in` `ID`

out-stm --> `out` `ID`

​					| `out` `number`

assign-stm --> `ID` `=` exp

exp -->	exp1 compare exp1 | exp1 equal exp1 | exp1

equal -->	`==`

compare -->	`>` | `<`

exp1 -->	exp2 addop exp2 | exp2

addop -->	`+` | `-`

exp2 -->	exp3 mulop exp3 | exp3

mulop -->	`*` | `/`

exp3 -->	`(` exp `)` | `INT10` | `INT8` | `INT16` | `FLO10` | `FLO8` | `FLO16` | `ID`



#### 细节说明

16进制只能包含大写字母

所有Statement产生式之间以`;`相连，最后一句Statement不能以`;`结尾

运算符优先级为(优先级自高至低):

- `()`
- `*` `/`
- `+` `-`
- `>` `<` `=`

**toy**语言文件以 .toy 结尾