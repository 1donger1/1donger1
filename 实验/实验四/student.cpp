#include "student.h"

Student::Student(const std::string &name, int id, double score)
    : name(name), id(id), score(score) {}

std::string Student::getName() const
{
    return name;
}

int Student::getId() const
{
    return id;
}

double Student::getScore() const
{
    return score;
}

std::ostream &operator<<(std::ostream &os, const Student &student)
{
    os << "Name: " << student.name << "\tID: " << student.id << "\tScore: " << student.score;
    return os;
}
