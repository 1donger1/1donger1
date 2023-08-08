#include "LinkTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define true 1
#define false 0

struct student
{
    int id;
    char *name;
    int score;
};

/**
 * @brief 创建一个新的学生对象。
 * 该函数分配内存并初始化一个新的学生对象，然后返回该对象的指针。
 * @param id 学生的ID编号。
 * @param name 学生的姓名。
 * @param score 学生的分数。
 * @return 返回新创建的学生对象的指针。如果内存分配失败，返回NULL。
 */
struct student *CreateStudent(int id,  char *name, int score)
{
    struct student *stu = (struct student *)malloc(sizeof(struct student));
    if (stu == NULL)
    {
        return NULL;
    }
    stu->id = id;
    // strcpy(stu->name, name);
    stu->name = name;
    stu->score = score;
}

/// @brief 释放学生对象占用的内存。
/// 该函数用于释放学生对象占用的内存。
/// @param stu 要释放内存的学生对象的指针。
void FreeStudent(struct student *stu)
{
    if (stu == NULL)
    {
        return;
    }
    free(stu);
}

/// @brief 打印数据元素的内容。
/// 该函数根据数据元素的类型打印相应的内容。如果数据元素是指向学生结构体的指针，
/// 打印学生的ID、姓名和分数；如果数据元素是指向字符的指针，直接打印字符
/// @param data  要打印的数据元素。
void print(ElementType data)
{
    if (data.type == structPoint)
    {
        struct student *stu = (struct student *)data.value;
        if (stu != NULL)
        {
            printf("id: %d, name: %s, score: %d\n", stu->id, stu->name, stu->score);
        }
    }
    else if (data.type == charPoint)
    {
        char *temp = (char *)data.value;
        printf("%s\n", temp);
    }
}

/// @brief 比较两个数据元素是否相等。
/// 该函数用于比较两个数据元素是否相等。如果数据元素都是指向学生结构体的指针，
/// 比较学生的ID是否相等；如果数据元素都是指向字符的指针，比较字符内容是否相等。
/// @param data1 第1个要比较的数据元素。
/// @param data2 第2个要比较的数据元素。
/// @return 如果两个数据元素相等，返回 true；否则返回 false。
int IsEqual(ElementType data1, ElementType data2)
{
    if (data1.type == structPoint && data2.type == structPoint)
    {
        // 将数据元素转换为学生结构体指针
        struct student *stu = (struct student *)data1.value;
        struct student *stu2 = (struct student *)data2.value;
        if (stu->id == stu2->id)
        {
            return true;
        }
        return false;
    }
    else if (data1.type == charPoint && data2.type == charPoint)
    {
        // 将数据元素转换为字符指针
        char *temp = (char *)data1.value;
        char *temp2 = (char *)data2.value;
        if (strcmp(temp, temp2) == 0)
        {
            return true;
        }
        return false;
    }
}

int main(int argc, char *argv[])
{
    LTree tree;
    InitTree(&tree);

    struct UniversalType TypeValue;
    TypeValue.value = "西苑";
    TypeValue.type = charPoint;
    LTNode *node1 = CreateTreeNode(TypeValue);

    TypeValue.value = CreateStudent(1, "donger", 100);
    TypeValue.type = structPoint;
    LTNode *node2 = CreateTreeNode(TypeValue);

    TypeValue.value = CreateStudent(2, "Nan", 100);
    TypeValue.type = structPoint;
    LTNode *node3 = CreateTreeNode(TypeValue);
    // LTNode *node1 = CreateTreeNode("东苑操场");
    // LTNode *node2 = CreateTreeNode("中苑操场");
    // LTNode *node3 = CreateTreeNode("西苑操场");
    // LTNode *node4 = CreateTreeNode("图书馆东");
    // ConnectBranch(node1, node2);
    // ConnectBranch(node1, node3);
    // ConnectBranch(node1, node4);

    // LTNode *node1 = CreateTreeNode("room");
    // LTNode *node2 = CreateTreeNode(CreateStudent(1, "donger", 100));
    // LTNode *node3 = CreateTreeNode(CreateStudent(2, "nan", 99));
#if 1
    ConnectBranch(node1, node2);
    ConnectBranch(node1, node3);

    // LTNode *node5 = CreateTreeNode("东苑宿舍");
    // LTNode *node6 = CreateTreeNode("中苑宿舍");
    // LTNode *node7 = CreateTreeNode("西苑宿舍");
    // LTNode *node8 = CreateTreeNode("图书馆西");
    // ConnectBranch(node5, node6);
    // ConnectBranch(node5, node7);
    // ConnectBranch(node5, node8);

    ConnectBranch(tree.root, node1);
    // ConnectBranch(tree.root, node5);

    // Travel(&tree, print);
    // printf("height: %d\n", GetTreeHeight(&tree));

    // LTNode *classNode = FindTreeNode(&tree, "文园");
    // if (classNode != NULL)
    // {
    //     LTNode *newNode = CreateTreeNode("17幢");
    //     ConnectBranch(classNode, newNode);
    // }

    Travel(&tree, print);

    TypeValue.type = charPoint;
    TypeValue.value = "西苑";
    LTNode *findnode = FindTreeNode(&tree, TypeValue, IsEqual);
    if (findnode != NULL)
    {
        char *className = "东苑";
        findnode->data.value = className;
    }
    Travel(&tree, print);

    TypeValue.type = structPoint;
    TypeValue.value = CreateStudent(1, "", 0);
    findnode = FindTreeNode(&tree, TypeValue, IsEqual);
    if (findnode != NULL)
    {
        struct student *stu = (struct student *)findnode->data.value;
        stu->score = 99;
    }
    Travel(&tree, print);
#endif
    return 0;
}