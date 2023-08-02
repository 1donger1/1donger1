#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef struct node
{
    int data;
    struct node *next;

}LNode,*LinkList;


LinkList List()
{
    LNode *L = new LNode;
    LNode *p = L;

    int data;
    cin >> data;
    L->data = data;
    while (data != -1)
    {
        LNode *q = new LNode;
        q->data = data;
        q->next = NULL;
        p->next = q;
        p = p->next;
        cin >> data;
    }
    return L;
}

void Del_x(LNode *&L, int x)
{
    LNode *p;
    if(L == NULL)
    {
        return;
    }
    if(L->data == x)
    {
        p = L;
        L = L->next;
        free(p);
        Del_x(L, x);
    }
    else{
        Del_x(L->next, x);
    }
}