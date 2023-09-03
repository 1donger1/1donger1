#include <vector>

template <typename T>
class StudentGradeSystem
{
private:
    std::vector<T> students;

public:
    void addStudent(const T &student)
    {
        students.push_back(student);
    }

    void displayAllStudents() const
    {
        for (const auto &student : students)
        {
            student.displayInfo();
            std::cout << "-------------------\n";
        }
    }
};
