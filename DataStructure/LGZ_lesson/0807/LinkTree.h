#ifndef __LINKTREE_
#define __LINKTREE_
#define ElementType struct UniversalType

enum Type
{
    charPoint,
    intPoint,
    structPoint
};

struct UniversalType
{
    void *value;
    enum Type type;
};

typedef struct LinkTreeNode
{
    ElementType data;
    struct LinkTreeNode *firstChild;
    struct LinkTreeNode *nextSibling;
    struct LinkTreeNode *parent;
} LTNode;

typedef struct LinkTree
{
    LTNode *root;
} LTree;

// LTNode *CreateNode(ElementType element);
LTNode *CreateTreeNode(ElementType element);

void ConnectBranch(LTNode *parent, LTNode *child);
void DisConnetcBranch(LTNode *parent, LTNode *child);

void FreeNode(LTNode *treeNode);
void FreeTree(LTree *tree);

int InitTree(LTree *tree);

void TravelTreeNode(LTNode *node, int depth, void (*func)(ElementType));
void Travel(LTree *tree, void (*func)(ElementType));

int GetNodeHeight(LTNode *node);
int GetTreeHeight(LTree *tree);

LTNode *FindNode(LTNode *node, ElementType element, int (*func)(ElementType, ElementType));
LTNode *FindTreeNode(LTree *node, ElementType element, int (*func)(ElementType, ElementType));

#endif