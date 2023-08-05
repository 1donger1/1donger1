#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Phone
{
public:
    Phone(string name)
    {
        cout << "Phone的构造函数" << endl;
        pho_name = name;
    }
    ~Phone()
    {
        cout << "Phone的析构函数" << endl;
        }
    string pho_name;
};

class Game
{
public:
    Game(string name)
    {
        cout << "Game的构造函数" << endl;
        game_name = name;
    }
    ~Game()
    {
        cout << "Game的析构函数" << endl;
    }
    string game_name;
};

class Person
{
public:
#if 0
/*这样写会报错，因为
string per_name;Phone phone;Game game;代表要先定义这三个对象，
而Phone phone;Game game;这两个要调用无参构造，但是之前已经写了有参构造，
没有无参构造，所以实例化不了对象
*/
    Person(string per_name1, string pho_name, string g_name)
    {
        per_name = per_name1;
        phone.pho_name = pho_name;
        game.game_name = g_name;
    }
    string per_name;
    Phone phone;
    Game game;
#endif
    // 通过初始化列表解决此方法
    Person(string per_name1, string pho_name, string g_name) : per_name(per_name1),phone(pho_name),game(g_name)
    {
        cout << "person的构造函数" << endl;
    }
    ~Person()
    {
        cout << "person的析构函数" << endl;
    }

    void show()
    {
        cout << per_name<<"拿着"<< phone.pho_name << "玩着" << game.game_name << endl;
    }

    // 写了初识化列表，下面就成了声明
    // 构造的顺序和声明的顺序一致，Person最后构造
    string per_name;
    Phone phone;
    Game game;
    
};

void test01()
{
    Person p1("Donger", "iphone", "GTAV");
    p1.show();
}

int main(int argc, char **argv)
{
    test01();
    return 0;
}