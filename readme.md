## Project: Compiler (名字暂无)

#### 说明:

暂时有两个文件夹:

- Source中是源码部分
- Test是测试部分 因为Linux上要写cmake太麻烦 所以写在一个test.c里测试

Source中有:

- type.h 定义token类型 导入<stdlib.h> <stdio.h> 是所有文件的基础
- scan.h 定义scanner部分所用函数与结构
- scan.c scan.h的实现 其中getToken()最重要 还未完成
- Tiny.c 主函数 串连scanner parser code三部分

Test中有:

- test.c
- test 编译生成的可执行文件
- leec.tiny 测试用文件
