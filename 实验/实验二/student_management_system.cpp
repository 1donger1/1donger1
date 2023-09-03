#include "student_management_system.h"
#include <iostream>


using namespace std;
void StudentManagementSystem::addStudent(Student *student)
{
    students.push_back(student);
}

void StudentManagementSystem::displayAllStudents() const
{
    for (const auto &student : students)
    {
        student->displayInfo();
        std::cout << "-------------------------\n";
    }
}

StudentManagementSystem::~StudentManagementSystem()
{
    for (auto student : students)
    {
        delete student;
    }
    students.clear();
}
