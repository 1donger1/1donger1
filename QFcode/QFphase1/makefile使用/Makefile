#CC			C编译器的名称，默认值为cc
#CFLAGS		C编译器的选项
#$@ 		目标名
#$< 		依赖文件列表中的第一个文件
#$^ 		依赖文件列表中除去重复文件的部分


CC=gcc
obj=main
OBJ=main.o sub.o sum.o
CFLAGS=-Wall -g

$(obj):$(OBJ)
	$(CC) $^ -o $@

%*.o:%*.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm *.o a.out -rf