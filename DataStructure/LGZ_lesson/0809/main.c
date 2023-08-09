#include <stdio.h>
#include <stdlib.h>
#include "BinarySortTree.h"
#define false 0
#define true 1

struct Student
{
    int id;
    char *name;
};

struct Student *CreateStudent(int id, const char *name)
{
    struct Student *stu = (struct Student *)malloc(sizeof(struct Student));
    if (stu == NULL)
    {
        printf("student malloc fail\n");
        return NULL;
    }
    stu->id = id;
    stu->name = (char *)name;
    return stu;
}

void FreeStudent(struct Student *stu)
{
    if (stu != NULL)
    {
        free(stu);
    }
}

int SortByID(ElementType value1, ElementType value2)
{
    struct Student *stu1 = (struct Student *)value1;
    struct Student *stu2 = (struct Student *)value2;

    if (stu1->id < stu2->id)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Print(ElementType value)
{
    struct Student *stu = (struct Student *)value;
    printf("stu id:%d stu name:%s\n", stu->id, stu->name);
}

int CompareID(ElementType value1, ElementType value2)
{
    struct Student *stu1 = (struct Student *)value1;
    struct Student *stu2 = (struct Student *)value2;
    return stu1->id - stu2->id;
}

int main(int argc, char *argv[])
{
    BSTree tree;
    InitBSTree(&tree);
#if 0
    int a[] = {2023, 8, 17, 1999, 6, 19};

    for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
    {
        InsertElement(&tree, a[i]);
    }

    PrevTravel(&tree);
    MidTravel(&tree);
    PostTravel(&tree);

    BSTNode *node = FindElement(&tree, 1999);
    if(node != NULL)
    {
        node->data = 2004;
    }
    PrevTravel(&tree);
    MidTravel(&tree);
    PostTravel(&tree);

    FreeTree(&tree);
#endif

    InsertElement(&tree, CreateStudent(2, "Donger"), SortByID);
    InsertElement(&tree, CreateStudent(3, "chuang"), SortByID);
    InsertElement(&tree, CreateStudent(1, "Nan"), SortByID);
    InsertElement(&tree, CreateStudent(4, "Bao"), SortByID);
    InsertElement(&tree, CreateStudent(8, "jiangsu"), SortByID);
    InsertElement(&tree, CreateStudent(7, "nanjing"), SortByID);
    InsertElement(&tree, CreateStudent(9, "pukou"), SortByID);

    MidTravel(&tree, Print);

    // struct Student stu = {1, ""};
    // DeleteElement(&tree, &stu ,CompareID);
    // MidTravel(&tree, Print);

    printf("tree number: %d\n", GetLeafNum(&tree));
    return 0;
}