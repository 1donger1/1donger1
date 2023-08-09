#ifndef __BINARYSORTTREE_H_
#define __BINARYSORTTREE_H_

#define ElementType void *

typedef struct BinarySortTreeNode
{
    ElementType data;
    struct BinarySortTreeNode *left;
    struct BinarySortTreeNode *right;
    struct BinarySortTreeNode *parent;
} BSTNode;

typedef struct BinarySortTree
{
    BSTNode *root;
} BSTree;

BSTNode *CreateTreeNode(ElementType element);

int InitBSTree(BSTree *tree);

void InsertNode(BSTNode *node, ElementType element, int (*func)(ElementType, ElementType));
void InsertElement(BSTree *tree, ElementType element, int (*func)(ElementType, ElementType));

void FreeNode(BSTNode *node);
void FreeTree(BSTree *tree);

// void PrevPrint(BSTNode *node);
// void PrevTravel(BSTree *tree);

void MidPrint(BSTNode *node, void (*func)(ElementType));
void MidTravel(BSTree *tree, void (*func)(ElementType));

// void PostPrint(BSTNode *node);
// void PostTravel(BSTree *tree);

BSTNode *findNode(BSTNode *node, ElementType element, int (*func)(ElementType, ElementType));
BSTNode *FindElement(BSTree *tree, ElementType element, int (*func)(ElementType, ElementType));

void DeleteElement(BSTree *tree, ElementType element, int (*func)(ElementType, ElementType));

int GetLeafNode(BSTNode *node);
int GetLeafNum(BSTree *tree);

#endif