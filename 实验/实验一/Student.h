#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>

class Student
{
public:
    Student();  // 构造函数
    ~Student(); // 析构函数

    void setName(const std::string &newName);
    void setID(int newID);
    void setCourseScores(const std::vector<double> &scores);

    void inputStudent();  // 输入学生信息
    void storeStudent();  // 存储学生信息
    void outputStudent(); // 输出学生信息

private:
    std::string name;
    int id;
    std::vector<double> courseScores;
};

#endif // STUDENT_H
