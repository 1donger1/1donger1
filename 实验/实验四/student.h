#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>

class Student
{
public:
    Student(const std::string &name, int id, double score);

    // Getter 方法
    std::string getName() const;
    int getId() const;
    double getScore() const;

    // 重载输出操作符，用于打印学生信息
    friend std::ostream &operator<<(std::ostream &os, const Student &student);

    // 析构函数
    ~Student() = default;

private:
    std::string name;
    int id;
    double score;
};

#endif
