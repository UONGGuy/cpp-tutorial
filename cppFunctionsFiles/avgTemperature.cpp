/*  avgTemperature.cpp

    Program to sort code into seasons by ascending average temperature.

    Use std::sort and a lambda.
*/

#include <iostream>
#include <algorithm>
#include <array>
#include <string_view>

struct Season
{
    std::string_view name{};
    double avgTemp{};
};

int main()
{
    std::array<Season, 4> seasons{
       {{ "Spring", 285.0 },
        { "Summer", 296.0 },
        { "Fall", 288.0 },
        { "Winter", 263.0 }}
    };

   std::sort(seasons.begin(), seasons.end(), 
       [](const auto& a, const auto& b) {
           return (a.avgTemp < b.avgTemp);
           });

    for (const auto& season : seasons)
    {
        std::cout << season.name << '\n';
    }

    return 0;
}
