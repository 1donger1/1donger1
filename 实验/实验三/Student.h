#include <iostream>
#include <string>

class Student
{
private:
    std::string name;
    int age;
    double grade;

public:
    Student(const std::string &n, int a, double g) : name(n), age(a), grade(g) {}

    void displayInfo() const
    {
        std::cout << "Name: " << name << "\nAge: " << age << "\nGrade: " << grade << std::endl;
    }
};
