## LL(1) Table

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

| First Set           |       |         |         |
| ------------------- | ----- | ------- | ------- |
| statement_sequence  | if    | while   | in      |
|                     | out   | ID      | number  |
|                     | (     |         |         |
| statement_sequence' | ;     | epsilon |         |
| statement           | if    | while   | in      |
|                     | out   | ID      | number  |
|                     | (     |         |         |
| if-statement        | if    |         |         |
| else-part           | else  | epsilon |         |
| while-statement     | while |         |         |
| In                  | In    |         |         |
| Out                 | Out   |         |         |
| Out'                | ID    | number  |         |
| exp                 | ID    | number  | (       |
| exp'                | =     | epsilon |         |
| mid                 | =     |         |         |
| extern              | =     | epsilon |         |
| exp_1               | ID    | number  | (       |
| exp_1'              | >     | <       | epsilon |
| compare             | >     | <       |         |
| exp_2               | ID    | number  | (       |
| exp_2'              | +     | -       | epsilon |
| add                 | +     | -       |         |
| exp_3               | ID    | number  | (       |
| exp_3'              | *     | /       | epsilon |
| mul                 | *     | /       |         |
| exp_4               | ID    | number  | (       |



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

