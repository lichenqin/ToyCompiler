## 实验报告



### 综合报告

#### 1.1 系统功能概述

本项目通过设计一组语言及相应文法，并实现相关编译器，可以读取一段代码，输出相应的 Token String, 并根据这一组 Token String 进行抽象树构造，语法分析，而后利用整体框架生成三地址代码。

其中在项目文件夹下的Source文件夹中，包含所有项目实现相关代码，Test文件夹下包含一些函数的测试，Yacc中包含相应BNF文法的Yacc实现。

#### 1.2 项目构造

type.h--------包含token表，抽象树的数据结构

scan.h scan.c 设计实现读取文件中的代码并返回相应token，主要函数为getToken()

parse.h parse.c 通过递归下降算法实现语法分析与抽象树的构造，主要函数为parse()

main.c 主体函数，调用其他函数实现文件代码读取，token string生成，语法分析，抽象树构造，三地址代码生成

#### 1.3 组内分工与贡献介绍



### 词法分析程序子系统

 #### 2.1 词法正规氏描述

为方便描述，进行如下定义:

​	letter = (a|b|c|...|z) | (A|B|C|...|Z)

​	digit = (0|1|2|3|...|9)

​	positive = (1|2|3|...|9)

​	hex = (0|1|2|...|9) | (A|B|...|F)

**描述**

INT10: positive (digit)*

INT8:	0 (0|1|2|...|8) (0|1|2|...|8)*

INT16: 0X hex (hex)*

FLO10: positive (digit)* '.' digit (digit)*

FLO8: 0 (0|1|2|...|8) (1|2|...|8)* '.' (0|1|2|...|8) (0|1|2|...|8)*

FLO16: 0X hex (hex)* '.' hex (hex)*

ID: ( '_' | letter ) ('\_' | letter | digit )*

#### 2.4 主要数据结构和算法

```c
/********Scanner Part Token Type Table********/
//define Token Type
typedef enum token{
    /* End File*/
    ENDFI,
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
    INTER
}TokenType;
```

根据DFA制作状态图，根据状态图实现状态转换算法:

```c
/*大体结构*/
switch(state){
	state 0:
			/* code */
			state = x;
			break;
	state 1:
			/* code */
			state = y;
			break;
	.
	.
	.
	state n:
			/* code */
			state = accept;
			break;
}
```



### 语法分析子系统



#### 语法分析方法描述

语法分析通过读取 token string 以及 相关文法，对token string是否合法进行判断，同时构建语法分析树。本项目采用递归下降算法实现语法分析与语法分析树的搭建，同时也实现了基于Yacc的 LALR(1)语法分析，并未整合到项目中，具体编写可以进入项目文件夹--Yacc 打开toy.y 查看。

**相关BNF语法**

start -->	statement_sequence

statement_sequence -->	statement; statement_sequence| statement

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

此文法已经去除左递归，可用于递归下降语法分析算法的编写。

#### 主要数据结构和算法

```c
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
```

根据BNF语法消除左递归后，进行递归下降。

```c
/* 大体结构 */

TreeNode * s(){
	match(token);
	s_q();
	match(token);
}

TreeNode * s_q(){
	match(token)
	t->newNode();
	return t;
}
```



### 思考题

1. 词法分析能否采用空格来区分单词？

   答：可以，根据正则表达式的描述，标识符，数字，保留字内部不存在以空格相连的情况，所以出现空格可视为某单词结束。

2. 程序设计中哪些环节影响词法分析的效率？如何提高效率？

   答：保留字的识别会影响词法分析的效率，每次识别一个标识符后，要进行一次匹配，会造成效率降低。具体的改进措施是将保留字划入状态图中，这样一次词法分析过程即可精确识别保留字，但这样做工作量较大。

3. 生成的三地址代码可否直接输出？

4. 如何保证四则运算的优先关系和左结合性？

   答：构建语法树时，深度越深，优先级越高，为实现这一目标，优先级高的运算符号经过多次function call才到达，表现在文法中则是同级运算为同一状态，高级运算在下一状态。左结合型表达在文法中为左递归，这里不需要担心循环递归的问题，因为最后一级面对的首字符为终结符。

5. 如何采用代码段相对地址代替三地址代码序列中的标号？

6. 完成一个实验，是否都涉及的这三个类工作，在大学学习的这几年的实验，是不是都或多或少设计了这三类工作