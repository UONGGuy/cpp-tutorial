/*  studentGrades.cpp

    Program to take student names and grades before printing out in 
    order of descending grades.

    - Create a struct to hold student first name and grade (0 - 100)
    - Prompt how many students to be entered
    - Create a std::vector to hold all students
    - Prompt for name and grade
    - Sort list by grade (highest first)
    - Print names and grades in sorted order
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

struct Student
{
    std::string name;
    int grade;
};

int getClassSize()
{
    int classSize;
    std::cout << "Input number of students: ";
    std::cin >> classSize;

    return classSize;
}

std::vector<Student> getStudentInfo()
{
    using Database = std::vector<Student>;

    int classSize{ getClassSize() };
    Database students(static_cast<std::size_t>(classSize));

    int student_no{ 1 };

    for (auto& student : students)
    {
        std::cout << "Student #" << student_no << '\n';
        std::cout << "Enter name: ";
        std::getline(std::cin >> std::ws, student.name);
        std::cout << "Enter grade: ";
        std::cin >> student.grade;
        ++student_no;
    }

    std::cout << std::endl;

    return students;
}

bool GradeHighLow(const Student& a, const Student& b)
{
    return (a.grade > b.grade);
}

int main()
{
    std::vector<Student> database{ getStudentInfo() };
    
    std::sort(database.begin(), database.end(), GradeHighLow);

    for (auto& student : database)
    {
        std::cout << student.name << " got a grade of " << student.grade << '\n';
    }

    return 0;
}
