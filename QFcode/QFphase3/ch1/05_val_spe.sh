#!/bin/bash

name="zhangsan"
#双引号里面的特殊字符，会使用其特殊含义
string1="good moring $name"
#单引号里面的特殊字符，都会失去特殊含义
string2='good moring $name'

echo $string1
echo $string2

#反引号：获取一个shell命令的输出结果，一般对有输出结果的命令经常去使用，也可以使用$()与反引号等价
echo ____________________________________
echo "today is date"
echo "today is `date`"
echo 'today is `date`'
#echo "My dir is $(ls)"
echo "My pwd is $(pwd)"

#转义字符：使用时，需要在echo后面加上-e选项
echo "**************"
echo "this \n is\ta\ntest"
echo -e "this \n is\ta\ntest"
echo "**************"

num=100
#(命令序列)由子shell来完成,不影响当前shell中的变量
( num=999;echo "1 $num" )
echo 1:$num
#{命令序列}在当前shell中执行，会影响当前变量
{ num=666; echo "2 $num"; }
echo 2:$num

