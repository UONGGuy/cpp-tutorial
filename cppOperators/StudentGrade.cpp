/*  StudentGrade.cpp
 *
 *  Program to assign grades to student by name in key-value pairs.
 *
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <map>

struct StudentGrade
{
    std::string name{};
    char grade{};
};

class GradeMap
{
private:
    std::vector<StudentGrade> m_map{};

public:
    char& operator[](std::string_view name);
};

char& GradeMap::operator[](std::string_view name)
{
    auto found{ std::find_if(m_map.begin(), m_map.end(),
        [&](const auto& student) { 
            return student.name == name; 
        })
    };

    if (found != m_map.end())
    {
        return found->grade;
    }
    else
    {
        m_map.push_back({ std::string{ name } });
        return m_map.back().grade;
    }
}

int main()
{
//    GradeMap grades{};
//
//    grades["Joe"] = 'A';
//    grades["Frank"] = 'B';

    std::map<std::string, char> grades{
        { "Joe", 'A' },
        { "Frank", 'B'}
    };
    grades["Susan"] = 'C';
    grades["Tom"] = 'D';

    std::cout << "Joe has a grade of " << grades["Joe"] << '\n';
    std::cout << "Frank has a grade of " << grades["Frank"] << '\n';

    return 0;
}
