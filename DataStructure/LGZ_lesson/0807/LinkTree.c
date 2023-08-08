#include "LinkTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

/// @brief  创建一个新的树节点。
/// 该函数分配内存并初始化一个新的树节点，然后返回该节点的指针。
/// 新节点包含了一个数据元素，还会初始化父节点、子节点以及兄弟节点指针。
/// @param element 节点所包含的数据元素。
/// @return 返回新创建的树节点的指针。如果内存分配失败，返回NULL。
LTNode *CreateTreeNode(ElementType element)
{
    LTNode *newNode = (LTNode *)malloc(sizeof(LTNode));
    if (newNode == NULL)
    {
        printf("create malloc fail");
        return NULL;
    }

    // 初始化新节点的数据和指针
    newNode->data = element;
    newNode->firstChild = NULL;
    newNode->nextSibling = NULL;
    newNode->parent = NULL;
    return newNode;
}

// LTNode *CreateTreeNode(ElementType element)
// {
//     return NULL;
// }
// LTNode *CreateTreeNode(ElementType element)
// {
//     LTNode *newNode = (LTNode *)malloc(sizeof(LTNode));

//     if (newNode == NULL)
//     {
//         printf("CREATE NODE ERROR\n");
//         return NULL;
//     }

//     newNode->data = element;0
//     newNode->firstChild = NULL;
//     newNode->nextSibling = NULL;
//     newNode->parent = NULL;
// }

/// @brief 在树结构中连接子节点到父节点。
/// 该函数在给定的父节点和子节点之间建立了父子关系。子节点成为父节点的子节点，
/// 如果在已有子节点后连接，则子节点可能也有兄弟节点。
/// @param parent  指向要连接子节点的父节点的指针。
/// @param child 指向要连接到父节点的子节点的指针。
void ConnectBranch(LTNode *parent, LTNode *child)
{
    // 要建立连接，父节点和子节点指针都必须有效（非NULL）。
    if (parent == NULL || child == NULL)
    {
        return;
    }
    // 将子节点连接为父节点的第一个子节点(头插)
    child->nextSibling = parent->firstChild;
    parent->firstChild = child;
    // 设置子节点的父节点
    child->parent = parent;
}

/// @brief 断开父节点和子节点之间的连接。
/// 该函数断开父节点和子节点之间的连接关系。它会搜索父节点的子节点列表，
/// 找到要断开连接的子节点，并更新相应的指针，从而从树中移除子节点。
/// @param parent  要断开连接的父节点的指针。
/// @param child 要断开连接的子节点的指针。
void DisConnetcBranch(LTNode *parent, LTNode *child)
{
    // 检查父节点、子节点以及父节点的第一个子节点是否为NULL
    if (parent == NULL || child == NULL || parent->firstChild == NULL)
    {
        return;
    }

    // 初始化遍历指针为父节点的第一个子节点
    LTNode *travePoint = parent->firstChild;
    // 如果子节点是父节点的第一个子节点
    if (travePoint == child)
    {
        // 更新父节点的第一个子节点为子节点的下一个兄弟节点
        parent->firstChild = child->nextSibling;

        // 断开子节点与父节点之间的连接
        child->parent = NULL;
        child->nextSibling = NULL;
        return;
    }

    // 遍历父节点的子节点列表
    while (travePoint->nextSibling != NULL)
    {
        // 如果找到要断开连接的子节点
        if (travePoint->nextSibling == child)
        {
            // 更新兄弟节点指针，跳过要断开连接的子节点
            travePoint->nextSibling = child->nextSibling;
            // 断开子节点与父节点之间的连接
            child->parent = NULL;
            child->nextSibling = NULL;
            return;
        }
        // 移动遍历指针到下一个兄弟节点
        travePoint = travePoint->nextSibling;
    }
}

/// @brief  释放树节点及其子树占用的内存。
/// 该函数用于递归地释放树节点及其子树所占用的内存。它首先释放给定节点的所有子节点，
/// 然后释放给定节点本身的内存。
/// @param treeNode 要释放内存的树节点的指针。
void FreeNode(LTNode *treeNode)
{
    if (treeNode == NULL)
    {
        return;
    }
    /*
    LTNode *travePoint = treeNode->firstChild;
    while(travePoint != NULL)
    {
        LTNode *nextNode = travePoint->nextSibling;
        FreeNode(travePoint);
        travePoint = nextNode;
    }*/

    // 递归地释放节点的子节点
    FreeNode(treeNode->firstChild);
    FreeNode(treeNode->nextSibling);
    free(treeNode);
}

/// @brief 释放整棵树及其节点占用的内存。
/// 该函数用于释放整棵树及其节点占用的内存。它首先递归地释放树的根节点及其子树，
/// 然后将树的根节点置为NULL，表示树已被完全释放。
/// @param tree 要释放的树的指针。
void FreeTree(LTree *tree)
{
    // 释放根节点及其子树占用的内存
    FreeNode(tree->root);
    tree->root = NULL;
}

/// @brief 初始化一棵树。
///  该函数用于初始化一棵树，分配内存并创建一个根节点，并将根节点的数据元素初始化为
/// 一个默认的通用类型（UniversalType），然后返回树的状态。
/// @param tree 要初始化的树的指针。
/// @return  初始化成功返回1，初始化失败返回0。
int InitTree(LTree *tree)
{
    struct UniversalType typedata = {NULL, -1};
    tree->root = CreateTreeNode(typedata);
    // tree->root = CreateTreeNode("");
    if (tree->root == NULL)
    {
        return false;
    }
    else
    {
        return true;
    }

    return 0;
}

/// @brief 遍历树节点并对每个节点执行指定函数。
/// 该函数用于深度优先遍历树节点及其子树，对每个节点执行指定的函数操作。
/// @param node 当前遍历的树节点的指针。
/// @param depth 当前节点在树中的深度。
/// @param func 要执行的函数指针，函数接受一个 ElementType 参数。
void TravelTreeNode(LTNode *node, int depth, void (*func)(ElementType))
{
    if (node == NULL)
    {
        return;
    }
    // // for (int i = 0; i < depth - 1; i++)
    // // {
    // //     printf(" ");
    // // }
    // // if (node->parent != NULL)
    // // {
    // //     printf("|__");
    // // }
    // for (int i = 0; i < depth; i++)
    // {
    //     printf(" ");
    //     printf("|__");
    // }
    // printf("%s\n", node->data);
    // /*
    // LTNode *travelPoint = node->firstChild;
    // while(travelPoint != NULL)
    // {
    //     TravelTreeNode(travelPoint);
    //     travelPoint = travelPoint->nextSibling;
    // }*/

    // 如果指定的函数不为空，则对当前节点执行指定函数操作
    if (func != NULL)
    {
        func(node->data);
    }
    // 递归遍历当前节点的子节点和兄弟节点
    TravelTreeNode(node->firstChild, depth + 1, func);
    TravelTreeNode(node->nextSibling, depth, func);
}

/// @brief 遍历整棵树并对每个节点执行指定函数。
/// 该函数用于从树的根节点开始，
/// 深度优先遍历整棵树的所有节点，对每个节点执行指定的函数操作。
/// @param tree 要遍历的树的指针。
/// @param func 要执行的函数指针，函数接受一个 ElementType 参数。
void Travel(LTree *tree, void (*func)(ElementType))
{
    // 从树的根节点开始遍历
    TravelTreeNode(tree->root, 0, func);
}

/// @brief 获取树节点的高度。
/// 该函数计算树节点的高度，即从给定节点到其最远的叶子节点的最长路径的边数。
/// @param treeNode 要计算高度的树节点的指针。
/// @return 返回树节点的高度。如果节点为NULL，则返回0。
int GetNodeHeight(LTNode *treeNode)
{
    if (treeNode == NULL)
    {
        return 0;
    }
    int height = 0;
    LTNode *travePoint = treeNode->firstChild;
    while (travePoint != NULL)
    {
        int childHeight = GetNodeHeight(travePoint);
        height = height > childHeight ? height : childHeight;
        travePoint = travePoint->nextSibling;
    }
    return height + 1;
}

/// @brief 获取树的高度。
/// 该函数计算整棵树的高度，即从根节点到所有叶子节点的最长路径的边数。
/// @param tree 要计算高度的树的指针。
/// @return 返回树的高度。如果树为空（根节点为NULL），则返回0。
int GetTreeHeight(LTree *tree)
{
    return GetNodeHeight(tree->root);
}

/// @brief 在树中查找具有特定属性的节点。
/// 该函数用于在树中查找具有特定属性的节点，可以根据给定的比较函数和目标属性值来查找节点。
/// @param node  当前遍历的树节点的指针。
/// @param element 目标属性值，用于与节点的属性进行比较。
/// @param func 比较函数的指针，用于执行属性比较。函数返回 true 表示匹配，false 表示不匹配。
/// @return 如果找到匹配的节点，则返回匹配的节点指针；如果没有找到匹配的节点或节点为NULL，则返回NULL。
LTNode *FindNode(LTNode *node, ElementType element, int (*func)(ElementType, ElementType))
{
    if (node == NULL)
    {
        return NULL;
    }
    // if (strcmp(node->data, element) == 0)
    // {
    //     return node;
    // }

    // 如果给定的比较函数不为空，并且返回 true 表示匹配
    if (func != NULL && func(node->data, element) == true)
    {
        return node;
    }

    LTNode *childNode = node->firstChild;
    LTNode *targetNode = NULL;

    // 递归遍历当前节点的子节点和兄弟节点
    while (childNode != NULL)
    {
        targetNode = FindNode(childNode, element, func);
        if (targetNode != NULL)
        {
            return targetNode;
        }
        childNode = childNode->nextSibling;
    }
    // if ((targetNode = FindNode(node->firstChild, element)) != NULL)
    // {
    //     return targetNode;
    // }
    // if ((targetNode = FindNode(node->nextSibling, element)) != NULL)
    // {
    //     return targetNode;
    // }
    return targetNode;
}
/// @brief 在树中查找具有特定属性的节点。
/// @param tree 该函数用于在整棵树中查找具有特定属性的节点，可以根据给定的比较函数和目标属性值来查找节点。
/// @param element 目标属性值，用于与节点的属性进行比较。
/// @param func 比较函数的指针，用于执行属性比较。函数返回 true 表示匹配，false 表示不匹配。
/// @return 如果找到匹配的节点，则返回匹配的节点指针；如果没有找到匹配的节点或节点为NULL，则返回NULL。
LTNode *FindTreeNode(LTree *tree, ElementType element, int (*func)(ElementType, ElementType))
{
    // 在树的根节点开始查找
    return FindNode(tree->root, element, func);
}
