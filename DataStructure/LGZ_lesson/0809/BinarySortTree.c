#include "BinarySortTree.h"
#include <stdio.h>
#include <stdlib.h>
#define false 0
#define true 1

BSTNode *CreateTreeNode(ElementType element)
{
    BSTNode *newNode = (BSTNode *)malloc(sizeof(BSTNode));
    if (newNode == NULL)
    {
        printf("CreateTreeNode malloc fail\n");
        return NULL;
    }

    newNode->data = element;
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

int InitBSTree(BSTree *tree)
{
    tree->root = NULL;
    return true;
}

void InsertNode(BSTNode *node, ElementType element, int (*func)(ElementType, ElementType))
{
    if (node == NULL)
    {
        return;
    }
    if (func(element, node->data))
    {
        if (node->left != NULL)
        {
            InsertNode(node->left, element, func);
        }
        else
        {
            node->left = CreateTreeNode(element);
            if (node->left == NULL)
            {
                printf("CreateNode fail!\n");
                return;
            }
            node->left->parent = node;
        }
    }
    else
    {
        if (node->right != NULL)
        {
            InsertNode(node->right, element, func);
        }
        else
        {
            node->right = CreateTreeNode(element);
            if (node->right == NULL)
            {
                printf("CreateNode fail!\n");
                return;
            }
            node->right->parent = node;
        }
    }
}

void InsertElement(BSTree *tree, ElementType element, int (*func)(ElementType, ElementType))
{
    if (tree->root == NULL)
    {
        tree->root = CreateTreeNode(element);
        if (tree->root == NULL)
        {
            printf("Create root fail\n");
            return;
        }
    }
    else
    {
        InsertNode(tree->root, element, func);
    }
}

void FreeNode(BSTNode *node)
{
    if (node == NULL)
    {
        return;
    }
    FreeNode(node->left);
    FreeNode(node->right);
    free(node->data);
    free(node);
}
void FreeTree(BSTree *tree)
{
    FreeNode(tree->root);
    tree->root = NULL;
}

// void PrevPrint(BSTNode *node)
// {
//     if (node != NULL)
//     {
//         printf("%d ", node->data);
//         PrevPrint(node->left);
//         PrevPrint(node->right);
//     }
// }
// void PrevTravel(BSTree *tree)
// {
//     printf("prev:");
//     PrevPrint(tree->root);
//     printf("\n");
// }

void MidPrint(BSTNode *node, void (*func)(ElementType))
{
    if (node != NULL)
    {
        MidPrint(node->left, func);
        // printf("%d ", node->data);
        func(node->data);
        MidPrint(node->right, func);
    }
}
void MidTravel(BSTree *tree, void (*func)(ElementType))
{
    printf("Mid:");
    MidPrint(tree->root, func);
    printf("\n");
}

// void PostPrint(BSTNode *node)
// {
//     if (node != NULL)
//     {
//         PostPrint(node->left);
//         PostPrint(node->right);
//         printf("%d ", node->data);
//     }
// }
// void PostTravel(BSTree *tree)
// {
//     printf("post:");
//     PostPrint(tree->root);
//     printf("\n");
// }

BSTNode *findNode(BSTNode *node, ElementType element, int (*func)(ElementType, ElementType))
{
    if (node == NULL)
    {
        return NULL;
    }
    if (func(node->data, element) == 0)
    {
        return node;
    }
    else if (func(node->data, element) < 0)
    {
        return findNode(node->right, element, func);
    }
    else
    {
        return findNode(node->left, element, func);
    }
}
void DeleteElement(BSTree *tree, ElementType element, int (*func)(ElementType, ElementType))
{
    BSTNode *targetNode = FindElement(tree, element, func);
    if (targetNode == NULL)
    {
        return;
    }
    if (targetNode->left == NULL && targetNode->right == NULL)
    {
        if (targetNode->parent == NULL)
        {
            // free(targetNode);
            tree->root = NULL;
        }
        else if (targetNode->parent->left == targetNode)
        {
            targetNode->parent->left = NULL;
        }
        else
        {
            targetNode->parent->right = NULL;
        }
        free(targetNode);
    }
    else if (targetNode->right == NULL)
    {
        if (targetNode->parent == NULL)
        {
            tree->root = targetNode->left;
            // free(targetNode);
        }
        else if (targetNode->parent->left == targetNode)
        {
            targetNode->parent->left = targetNode->left;
        }
        else
        {
            targetNode->parent->right = targetNode->left;
        }
        free(targetNode->data);
        free(targetNode);
    }
    else if (targetNode->left == NULL)
    {
        if (targetNode->parent == NULL)
        {
            tree->root = targetNode->right;
        }
        else if (targetNode->parent->left == targetNode)
        {
            targetNode->parent->left = targetNode->right;
        }
        else
        {
            targetNode->parent->right = targetNode->left;
        }
        free(targetNode->data);
        free(targetNode);
    }
    else
    {
        BSTNode *MinNode = targetNode->right;
        while (MinNode->left != NULL)
        {
            MinNode = MinNode->left;
        }
        ElementType *temp = targetNode->data;
        targetNode->data = MinNode->data;
        MinNode->data = temp;

        if (MinNode->parent == targetNode)
        {
            targetNode->right = MinNode->right;
        }
        else
        {
            MinNode->parent->left = MinNode->right;
        }

        free(MinNode->data);
        free(MinNode);
    }
}

int GetLeafNode(BSTNode *node)
{
    if (node == NULL)
    {
        return 0;
    }
    if(node->right == NULL && node->left == NULL)
    {
        return 1;
    }
    int leftNum = GetLeafNode(node->left);
    int rightNum = GetLeafNode(node->right);

    return leftNum + rightNum;
}
int GetLeafNum(BSTree *tree)
{
    return GetLeafNode(tree->root);
}

BSTNode *FindElement(BSTree *tree, ElementType element, int (*func)(ElementType, ElementType))
{
    return findNode(tree->root, element, func);
}
