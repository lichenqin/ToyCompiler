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

**Reserve Word:** 包括IF THEN ELSE DO WHILE

#### 用法

```
>> Tiny filename.tiny
```

控制台输出TokenType以及对应的字符串。

同时包含 <kbd>filename.tiny.out</kbd>的输出文件 输出内容与控制台显示内容相同。

也可通过调用 `getToken()` 函数，单次获取一个Token的对应信息。

