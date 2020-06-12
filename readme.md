## Project: Compiler (名字暂无)

#### 说明:

暂时有两个文件夹:

- Source中是源码部分
- Test是测试部分 因为Linux上要写cmake太麻烦 所以写在一个test.c里测试

Source中有:

- type.h 定义token类型 导入<stdlib.h> <stdio.h> 是所有文件的基础
- scan.h 定义scanner部分所用函数与结构
- scan.c scan.h的实现 其中getToken()最重要
- Tiny.c 主函数 串连scanner parser code三部分

Test中有:

- test.c
- test 编译生成的可执行文件
- leec.tiny 测试用文件



#### 符号定义规则:

**Identifier:** 字母开头, 可以包括数字、字母、下划线，最多31位

**Number:** 包括int_10、int_8、int_16、float_10、float_8、float_16，最多31位

**Special Number:** 包括 + - * / ( ) > < = == 其余均不包含

**Reserve Word:** 包括IF THEN ELSE DO WHILE IN OUT END



#### 用法

```
>> Tiny filename.tiny
```

控制台输出TokenType以及对应的字符串。

同时包含 <kbd>filename.tiny.out</kbd>的输出文件 输出内容与控制台显示内容相同。

也可通过调用 `getToken()` 函数，单次获取一个Token的对应信息。



#### BNF语法:

- 添加了三个新的关键字: `end` `in` `out`

- 在exp状态下，既要保持左优先性，也要保持双目运算符号的优先级



start -->	statement_sequence

statement_sequence -->	statement_sequence; statement| statement

statement --> if-stm | while-stm | in-stm | out-stm | p0

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



> 尚未进行去除左递归工作，去除左递归后，进行LL(1)语义分析，构建first_follow集

#### 消除左递归 提取左因子后的语法

<kbd>消除左递归</kbd>

1. statement_sequence	--->	statement	statement_sequence'

2. statement_sequence'	-->	`;`	statement	statement_sequence'

3. statement_sequence'	-->	$\epsilon$

4. statement	--->	if-statement

5. statement	--->	while-statement

6. statement	--->	In-statement

7. statement	--->	Out-statement

8. statement	--->	exp

<kbd>提取左因子</kbd>

9. if-statement	--->	 `if`	exp	`then`	statement_sequence	else-part	`end`

10. else-part   --->	`else`	statement_sequence

11. else-part	-->	$\epsilon$

12. while-statement	--->	`while`	exp	`do`	statement_sequence	`end`

13. In-statement	--->	`In`	`ID`

<kbd>提取左因子</kbd>

14. Out-statement	--->	`Out`	Out-statement'

15. Out-statement'	--->	`ID`

16. Out-statement'	--->	`number`	

<kbd>左递归消除</kbd>

17. exp	---->	exp_1	exp'

18. exp'	--->	**mid**	exp_1	exp'

19. exp'	--->	$\epsilon$

20. **mid** -->	`=` **extern**

21. **extern**	--->	`=`	|	$\epsilon$

22. exp_1 --->	exp_2	exp_1'

23. exp_1'--->	**compare**	exp_2	exp_1'

24. exp_1'--->	$\epsilon$

25. **compare**	--->	`>`

26. **compare**	--->	`<`

27. exp_2 -->	exp_3	exp_2'

28. exp_2'-->	**addop**	exp_3	exp_2'

29. exp_2'-->	$\epsilon$

30. **addop**		--->	`+`

31. **addop**		--->	`-`

32. exp_3	---->	exp_4	exp_3'

33. exp_3'	--->	**mulop**	exp_4	exp_3'

34. exp_3'	--->	$\epsilon$

35. **mulop**	-->	`x`

36. **mulop**	-->	`/`

37. exp_4	---->	`(`	exp	`)`

38. exp_4	---->	`number`

39. exp_4	---->	`identifier`



#### 构建First Follow集

| First Set |      |      |      |
| --------  | ---- | ---- | ---- |
| statement_sequence | if | while | in |
|  | out | ID | number |
|  | ( |  |  |
| statement_sequence' | ; | epsilon |      |
| statement | if | while | in |
|  | out | ID | number |
|  | ( |  |  |
| if-statement | if |      |      |
| else-part    | else | epsilon |      |
| while-statement | while |  | |
| In           | In |      |      |
| Out          | Out |      |      |
| Out'         | ID | number |      |
| exp | ID | number | ( |
| exp' | = | epsilon | |
| mid		   | = |		 |		|
| extern	| = | epsilon |	|
| exp_1	| ID | number | ( |
| exp_1'	| > | < | epsilon |
| compare	| > | < |	|
| exp_2	| ID | number | ( |
| exp_2'	| + | - | epsilon |
| add	| + | - |	|
| exp_3	| ID | number | ( |
| exp_3'	| * | / | epsilon |
| mul	| * | / |	|
| exp_4	| ID | number | ( |



| Follow Set          |               |      |      |      |
| ------------------- | ------------- | ---- | ---- | ---- |
| statement_sequence  | $             | else | end  |      |
| statement_sequence' | $             | else | end  |      |
| statement           | ;             | $    | else | end  |
| if-statement        | ;             | $    | else | end  |
| else-part           | end           |      |      |      |
| while-statement     | ;             | $    | else | end  |
| In                  | ;             | $    | else | end  |
| Out                 | ;             | $    | else | end  |
| Out'                | ;             | $    | else | end  |
| exp                 | ;             | $    | else | end  |
|                     | then          | do   | (    |      |
| exp_1               | follow(exp)   | =    |      |      |
| exp'                | follow(exp)   |      |      |      |
| mid                 | number        | ID   | (    |      |
| extern              | number        | ID   | (    |      |
| exp_2               | follow(exp_1) | >    | <    |      |
| exp_1'              | follow(exp_1) |      |      |      |
| compare             | number        | ID   | (    |      |
| exp_3               | follow(exp_2) | +    | -    |      |
| exp_2'              | follow(exp_2) |      |      |      |
| addop               | number        | ID   | (    |      |
| exp_4               | follow(exp_3) | *    | /    |      |
| exp_3'              | follow(exp_3) |      |      |      |
| mulop               | number        | ID   | (    |      |



#### 构造LL(1)表

production A->α	Following two rules:

- For each token a in First(α), add A->α to the entry M[A,a]
- If $\epsilon$ is in First(α), for each element a of follow(A), add A->α to M[A,a]



statement_sequence 只有First(statement)

statement_sequence' 有First(;) 还有Follow(statement_sequence')

statement 有 First(If) First(While) First(In) First(On) First(exp)

if-statement 只有 First(if)

else-part 有 First(else) 还有 Follow(else-part)

while-statement 只有 First(while)

In-statement 只有 First(In)

Out-statement 只有 First(Out)

Out-statement' 有 First(ID) First(number)

exp 有 First(exp_1)

exp' 有 First(mid) 和 Follow(exp')

exp_1 有 First(exp_2)

exp_1' 有 First(compare) 和 Follow(exp_1')

exp_2 有 First(exp_3)

exp_2' 有 First(addop) 和 Follow(exp_2')

exp_3 有 First(exp_4)

exp_3' 有 First(mulop) 和 Follow(exp_3')

exp_4 只有 First(exp_4)