#include <iostream>
#include "fun.hpp"
using namespace std;


int main(int argc, char **argv)
{
    LNode *L = List();

    Del_x(L, 10);

    while(L!=NULL)
    {
        cout << L->data << " ";
        L = L->next;
    }

    return 0;
}