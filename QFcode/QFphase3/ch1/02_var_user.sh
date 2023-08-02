#!/bin/bash

#定义变量
#shell脚本中没有数据类型可言，所以定义变量时不需要加数据类型
#shell脚本中，赋值操作时不能在等号两边加空格
#NUM = 100 #错误
NUM=100

#引用变量
# $变量名 取一个变量的值
i=$NUM

#显示变量
echo $NUM
echo $i

#清除变量
unset NUM
echo "*************"
echo $NUM

#使用read从终端读取数据保存在变量中
read str
echo "str = $str"

#使用readonly创建一个只读的变量
readonly n=999
echo "n = $n"

#指定变量初始化后不能再次修改变量的值，只能使用
#n=666
#echo "n = $n"