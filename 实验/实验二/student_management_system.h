#ifndef STUDENT_MANAGEMENT_SYSTEM_H
#define STUDENT_MANAGEMENT_SYSTEM_H

#include <vector>
#include "student.h"

class StudentManagementSystem
{
public:
    void addStudent(Student *student);
    void displayAllStudents() const;
    ~StudentManagementSystem(); // Destructor to clean up memory
private:
    std::vector<Student *> students;
};

#endif // STUDENT_MANAGEMENT_SYSTEM_H
