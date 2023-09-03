#include "student_management_system.h"

int main()
{
    StudentManagementSystem system;

    Student *student1 = new Student("Alice", 20, "S12345");
    student1->inputInfo();
    system.addStudent(student1);

    Student *student2 = new Student("Bob", 21, "S67890");
    student2->inputInfo();
    system.addStudent(student2);

    system.displayAllStudents();

    // Don't forget to delete allocated memory
    delete student1;
    delete student2;

    return 0;
}
