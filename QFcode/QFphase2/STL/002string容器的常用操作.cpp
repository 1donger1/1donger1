#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 1_string的构造函数
void test01()
{
    string str; // 定义个空串
    string str1("hello");
    string str2(str1);
    string str3(5, 'k');

    cout << str1 << endl;
    cout << str2 << endl;
    cout << str3 << endl;
}

// 2_string的基本操作
/*
 string& operator=(const char* s);//char*类型字符串 赋值给当前的字符串
 string& operator=(const string &s);//把字符串s赋给当前的字符串
 string& operator=(char c);//字符赋值给当前的字符串
 string& assign(const char *s);//把字符串s赋给当前的字符串
 string& assign(const char *s, int n);//把字符串s的前n个字符赋给当前的字符串
 string& assign(const string &s);//把字符串s赋给当前字符串
 string& assign(int n, char c);//用n个字符c赋给当前字符串
 string& assign(const string &s, int start, int n);//将s从start开始n个字符赋值给字符串
*/
void test02()
{
    string str("helloworld");
    string str1("heihei");
    str = str1;
    str = "hh";
    str = 'c';
    str.assign(str1);
    str.assign("hhhhhh");
    str.assign("chen", 2);  // 输出为ch
    str.assign(5, 'c');     // 输出5个c
    str.assign(str1, 1, 2); // 输出为ei
    cout << str << endl;
}

// 3_string存取字符串操作
/*
char& operator[](int n);//通过[]方式取字符--重载
char& at(int n);//通过at方法获取字符
*/
void test03()
{
    string str("helloworld");
    cout << str[4] << endl;
    str[4] = 'c';
    cout << str.at(4) << endl;
}

// 4_string的拼接操作
/*
 string& operator+=(const string& str);//重载+=操作符
 string& operator+=(const char* str);//重载+=操作符
 string& operator+=(const char c);//重载+=操作符

 string& append(const char *s);//把字符串s连接到当前字符串结尾
 string& append(const char *s, int n);//把字符串s的前n个字符连接到当前字符串结尾
 string& append(const string &s);//同operator+=()
 string& append(const string &s, int pos, int n);//把字符串s中从pos开始的n个字符连接到当
*/
void test04()
{
    string str1("hello");
    string str2("donger");

    // str1 += str2;
    // str1.append(str2);

    // str1.append("chen", 2);//输出helloch
    str1.append(str2, 2, 3); // 输出hellonge

    cout << str1 << endl;
}

// 5_string的查找和替换
/*
int find(const string& str, int pos = 0) const; //查找str第一次出现位置,从pos开始查找
int find(const char* s, int pos = 0) const; //查找s第一次出现位置,从pos开始查找
int find(const char* s, int pos, int n) const; //从pos位置查找s的前n个字符第一次位置
int find(const char c, int pos = 0) const; //查找字符c第一次出现位置

int rfind(const string& str, int pos = npos) const;//查找str最后一次位置,从pos开始查找
int rfind(const char* s, int pos = npos) const;//查找s最后一次出现位置,从pos开始查找
int rfind(const char* s, int pos, int n) const;//从pos查找s的前n个字符最后一次位置
int rfind(const char c, int pos = 0) const; //查找字符c最后一次出现位置

string& replace(int pos, int n, const string& str); //替换从pos开始n个字符为字符串str
string& replace(int pos, int n, const char* s); //替换从pos开始的n个字符为字符串s
*/
void test05()
{
    string str("helloworld");
    string str1("wor");
    // cout << str.find(str1) << endl;//5
    // cout << str.find("wor") << endl;//5
    // cout << str.find("world", 0, 2) << endl;//5
    // cout <<str.find('o') << endl;//4

    // cout << str.rfind("or") << endl; // 6
    // cout << str.rfind("l") << endl; // 8

    str.replace(5, 2, "c"); // hellocrld
    cout << str << endl;
}

// 6_string比较操作
/*
compare函数在>时返回 1，<时返回 ‐1，==时返回 0。
比较区分大小写，比较时参考字典顺序，排越前面的越小。
大写的A比小写的a小。
int compare(const string &s) const;//与字符串s比较
int compare(const char *s) const;//与字符串s比较
*/
void test06()
{
    // string的比较操作
    string str1("hello");
    string str2("world");
    // int ret = str1.compare(str2);
    int ret = str1.compare("hello");
    if (ret > 0)
    {
        cout << "str大" << endl;
    }
    else if (ret < 0)
    {
        cout << "str小" << endl;
    }
    else
    {
        cout << "相等" << endl;
    }
}

// 7_获取string子串
/*
string substr(int pos = 0, int n = npos) const;//返回由pos开始的n个字符组成的字符串
*/
void test07()
{
    string str("hello world");
    string str1 = str.substr(6, 5);
    cout << str1 << endl; // world
}

// 8_string插入和删除
/*
 string& insert(int pos, const char* s); //插入字符串
 string& insert(int pos, const string& str); //插入字符串
 string& insert(int pos, int n, char c);//在指定位置插入n个字符c
 string& erase(int pos, int n = npos);//删除从Pos开始的n个字符
 */
void test08()
{
    string str("hello");
    str.insert(1, "wor");
    cout << str << endl;
    str.erase(1, 3);
    cout << str << endl;
}

// 9_string对象和char*相互转换
void test09()
{
    string str("hello");

    char *s = NULL;
    s = const_cast<char *>(str.c_str());
    cout << s << endl;
}

int main(int argc, char **argv)
{
    test09();

    return 0;
}
