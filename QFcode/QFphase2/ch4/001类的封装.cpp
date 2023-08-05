#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

class Person
{
public:
    void person_init(int age, char *name)
    {
        if (age >= 0 && age <= 100)
        {
            m_age = age;
            strcpy(m_name, name);
        }
    }

    void show_person()
    {
        cout << m_name << " " << m_age << endl;
    }

    int get_age()
    {
        return m_age;
    }

    void set_age(int age)
    {
        if(age >= 0 && age <= 100)
        {
            m_age = age;
        }
    }

    char *get_name()
    {
        return m_name;
    }

    void set_name(char *name)
    {
        strcpy(m_name, name);
    }

private:
    int m_age;
    char m_name[128];
};

void test01()
{
    Person p1;
    p1.person_init(20, "donger");
    p1.show_person();

    p1.set_age(24);
    p1.set_name("Donger");
    p1.show_person();
}

int main(int argc, char **argv)
{
    test01();
    return 0;
}