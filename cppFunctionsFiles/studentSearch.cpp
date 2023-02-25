/*  studentSearch.cpp

    Program to determine student with the most points and print.

    - Create a struct (Student) to store name and points of student.
    - Create array of students
    - Use std::max_element to find student with most points
    - Print student name with most points
*/

#include <iostream>
#include <array>
#include <algorithm>
#include <string_view>

struct Student
{
    std::string_view name{};
    int points{};
};

int main()
{
    const std::array<Student, 8> arr{
        {{ "Albert", 3 },
         { "Ben", 5 },
         { "Christine", 2 },
         { "Dan", 8 },
         { "Enchilada", 4 },
         { "Francis", 1 },
         { "Greg", 3 },
         { "Hagrid", 5 }}
    };

    const auto topScore{ 
        std::max_element(arr.begin(), arr.end(),
            [](const auto& a, const auto& b) {
                return ( a.points < b.points );
            })
    };

    std::cout << topScore->name << " is the best student\n";

    return 0;
}
