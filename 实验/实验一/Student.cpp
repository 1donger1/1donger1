#include "Student.h"
#include <iostream>

// 构造函数
Student::Student()
{
    id = 0;
}

// 析构函数
Student::~Student()
{
    // 析构函数的实现，如果需要的话
}

void Student::setName(const std::string &newName)
{
    name = newName;
}

void Student::setID(int newID)
{
    id = newID;
}

void Student::setCourseScores(const std::vector<double> &scores)
{
    courseScores = scores;
}

void Student::inputStudent()
{
    std::cout << "Enter student name: ";
    std::cin >> name;
    std::cout << "Enter student ID: ";
    std::cin >> id;

    int numCourses;
    std::cout << "Enter the number of courses: ";
    std::cin >> numCourses;

    courseScores.resize(numCourses);
    for (int i = 0; i < numCourses; ++i)
    {
        std::cout << "Enter score for course " << i + 1 << ": ";
        std::cin >> courseScores[i];
    }
}

// 假设最大学生数为100
const int MAX_STUDENTS = 100;
Student studentArray[MAX_STUDENTS]; // 全局数组用于存储学生对象
int numStudents = 0;                // 当前存储的学生数量
void Student::storeStudent()
{
    if (numStudents < MAX_STUDENTS)
    {
        studentArray[numStudents] = *this; // 将当前学生对象存入数组
        numStudents++;
        std::cout << "Student stored!\n";
    }
    else
    {
        std::cout << "Maximum number of students reached.\n";
    }
}

void Student::outputStudent()
{
    std::cout << "Name: " << name << "\n";
    std::cout << "ID: " << id << "\n";
    std::cout << "Course Scores:\n";
    for (int i = 0; i < courseScores.size(); ++i)
    {
        std::cout << "Course " << i + 1 << ": " << courseScores[i] << "\n";
    }
}
