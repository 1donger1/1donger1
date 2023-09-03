#include <iostream>
#include <vector>
#include <algorithm>
#include "student.h"

int main()
{
    std::vector<Student> students;

    int numStudents;
    std::cout << "Enter the number of students: ";
    std::cin >> numStudents;

    for (int i = 0; i < numStudents; ++i)
    {
        std::string name;
        int id;
        double score;

        std::cout << "Enter student name: ";
        std::cin >> name;
        std::cout << "Enter student ID: ";
        std::cin >> id;
        std::cout << "Enter student score: ";
        std::cin >> score;

        students.push_back(Student(name, id, score));
    }

    std::cout << "\nStudent List:\n";
    for (const auto &student : students)
    {
        std::cout << student << "\n";
    }

    auto highestScoreStudent = std::max_element(students.begin(), students.end(),
                                                [](const Student &a, const Student &b)
                                                {
                                                    return a.getScore() < b.getScore();
                                                });

    std::cout << "\nStudent with the highest score:\n"
              << *highestScoreStudent << "\n";

    // 使用 sort 算法对学生对象按照成绩进行排序
    std::sort(students.begin(), students.end(),
              [](const Student &a, const Student &b)
              {
                  return a.getScore() > b.getScore();
              });

    std::cout << "\nStudent List (sorted by score):\n";
    for (const auto &student : students)
    {
        std::cout << student << "\n";
    }

    return 0;
}
