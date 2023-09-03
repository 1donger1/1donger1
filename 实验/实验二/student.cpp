#include "student.h"
#include <iostream>

Person::Person(const std::string &name, int age)
    : name(name), age(age)
{
    // Constructor implementation
}

void Person::displayInfo() const
{
    std::cout << "Name: " << name << std::endl;
    std::cout << "Age: " << age << std::endl;
}

Entity::Entity(const std::string &id)
    : id(id)
{
    // Constructor implementation
}

const std::string &Entity::getID() const
{
    return id;
}

Course::Course(const std::string &id, const std::string &name)
    : Entity(id), name(name)
{
    // Constructor implementation
}

void Course::showDetails() const
{
    std::cout << "Course ID: " << getID() << std::endl;
    std::cout << "Course Name: " << name << std::endl;
}

Student::Student(const std::string &name, int age, const std::string &studentID)
    : Person(name, age), studentID(studentID), enrolledCourse(nullptr)
{
    // Constructor implementation
}

void Student::inputInfo()
{
    std::cout << "Enter enrolled course ID: ";
    std::string courseID;
    std::cin >> courseID;
    enrolledCourse = new Course(courseID, "Course Name"); // Course name is just an example
}

void Student::displayInfo() const
{
    Person::displayInfo();
    std::cout << "Student ID: " << studentID << std::endl;
    if (enrolledCourse)
    {
        std::cout << "Enrolled Course Details:\n";
        enrolledCourse->showDetails();
    }
}

