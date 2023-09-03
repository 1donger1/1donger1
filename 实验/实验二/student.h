#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Person
{
public:
    Person(const std::string &name, int age);
    void displayInfo() const;

private:
    std::string name;
    int age;
};

class Entity
{
public:
    Entity(const std::string &id);
    virtual void showDetails() const = 0;

protected:
    const std::string &getID() const; // Protected getter for id
private:
    std::string id;
};

class Course : public Entity
{
public:
    Course(const std::string &id, const std::string &name);
    void showDetails() const override;

private:
    std::string name;
};

class Student : public Person
{
public:
    Student(const std::string &name, int age, const std::string &studentID);
    void inputInfo();
    void displayInfo() const;

private:
    std::string studentID;
    Course *enrolledCourse;
};

#endif // STUDENT_H
