#ifndef __MYSTRING_H_
#define __MYSTRING_H_
typedef struct string MyString;
#define Init_MyString(obj, str) \
    MyString obj;               \
    Initize(&obj, str);
struct string
{
    char *string;
    int size;

    void (*Print)(MyString obj);
    int (*IsEqual)(MyString *obj1, MyString *obj2);
    int (*IsContain)(MyString *obj1, const char *s);
    int (*Size)(MyString *obj);
    void (*RmStr)(MyString *obj, const char *s);
    void (*InsertStr)(MyString *obj, const char *s, int target);
};

void Initize(MyString *obj, const char *str);

void FreeMystring(MyString *obj);
/*
int size(MyString *obj);
void Initize(MyString *obj,const char *str);
void print(MyString obj);
int IsEqual(MyString *obj1,MyString *obj2);
int IsContain(MyString *obj1,const char *s);
void RmStr(MyString *obj,const char *s);
void InsertStr(MyString *obj,const char *s,int target);
*/
#endif