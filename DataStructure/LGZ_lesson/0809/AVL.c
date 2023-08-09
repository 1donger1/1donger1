#include <stdio.h>
#include <stdlib.h>

struct TreeNode
{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

/// @brief 右旋操作
/// @param 节点
struct TreeNode *RotateRight(struct TreeNode *node)
{
    struct TreeNode *t = node->left;
    node->left = t->right;
    t->right = node;
    return t;
}

/// @brief 左旋操作
/// @param 节点
struct TreeNode *RotateLeft(struct TreeNode *node)
{
    struct TreeNode *t = node->right;
    node->right = t->left;
    t->left = node;
    return t;
}

struct TreeNode *RotateLeftRight(struct TreeNode *node)
{
    node->left = RotateLeft(node->left);
    return RotateRight(node);
}

struct TreeNode *RotateRightLeft(struct TreeNode *node)
{
    node->right = RotateRight(node->right);
    return RotateLeft(node);
}

struct TreeNode *CreateTreeNode(int element)
{
    struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    if (newNode == NULL)
    {
        printf("CreateTreeNode malloc fail\n");
        return NULL;
    }

    newNode->data = element;
    newNode->left = newNode->right = NULL;
    return newNode;
}

int GetNodeHeight(struct TreeNode *node)
{
    if (node == NULL)
    {
        return 0;
    }
    int leftHeight = GetNodeHeight(node->left);
    int rightHeight = GetNodeHeight(node->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

struct TreeNode *InsertData(struct TreeNode *node, int data)
{
    if (node == NULL)
    {
        node = CreateTreeNode(data);
    }
    else if (data < node->data)
    {
        node->left = InsertData(node->left, data);
        if (GetNodeHeight(node->left) - GetNodeHeight(node->right) > 1)
        {
            if (data < node->left->data) // LL
            {
                node = RotateRight(node);
            }
            else
            {
                node = RotateLeftRight(node);
            }
        }
    }
    else
    {
        node->right = InsertData(node->right, data);
        if (GetNodeHeight(node->left) - GetNodeHeight(node->right) < -1)
        {
            if (data < node->right->data) // RL
            {
                node = RotateRightLeft(node);
            }
            else
            {
                node = RotateLeft(node); // RR
            }
        }
    }
    return node;
}

void PrevPrint(struct TreeNode *node)
{
    if (node != NULL)
    {
        printf("%d ", node->data);
        PrevPrint(node->left);
        PrevPrint(node->right);
    }
}

void MidPrint(struct TreeNode *node)
{
    if (node != NULL)
    {
        MidPrint(node->left);
        printf("%d ", node->data);
        // func(node->data);
        MidPrint(node->right);
    }
}

void PostPrint(struct TreeNode * node)
{
    if (node != NULL)
    {
        PostPrint(node->left);
        PostPrint(node->right);
        printf("%d ", node->data);
    }
}

int main(int argc, char *argv[])
{
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    struct TreeNode *root = NULL;
    for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
    {
        root = InsertData(root, a[i]);
    }

    printf("Prev:");
    PrevPrint(root);
    printf("\n");

    printf("Mid:");
    MidPrint(root);
    printf("\n");

    printf("Post:");
    PostPrint(root);
    printf("\n");

    return 0;
}
