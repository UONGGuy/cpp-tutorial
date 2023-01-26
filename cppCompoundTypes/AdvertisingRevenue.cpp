/*  AdvertisingRevenue.cpp

    Program to:
    - Keep track of how many ads are shown to readers
    - What % of ads were clicked
    - Average earning per ad clicked

    Reads in values from user then passes to function to:
    - Print each value
    - Calculate how much was made that day (product of 3 fields)
*/

#include <iostream>

struct AdStats
{
    int ad_qty{};
    double click_percent{};
    double avg_earn_per_click{};
};

AdStats getAdStats()
{
    AdStats temp{};
    std::cout << "How many ads were shown today?\n";
    std::cin >> temp.ad_qty;
    std::cout << "What percentage of ads were clicked by users?\n";
    std::cin >> temp.click_percent;
    std::cout << "What is the average earning per ad clicked?\n";
    std::cin >> temp.avg_earn_per_click;

    return temp;
}

void printAdStats(const AdStats& day_stats)
{
    std::cout << "Advertising statistics (daily)\n";
    std::cout << "Number of ads shown: " << day_stats.ad_qty << "\n";
    std::cout << "Percentage of ads clicked by users: " << day_stats.click_percent << "\n";
    std::cout << "Average earning per ad clicked: " << day_stats.avg_earn_per_click << "\n";
    std::cout << "Total earning: " << day_stats.ad_qty * day_stats.click_percent / 100 * day_stats.avg_earn_per_click << "\n";
}

int main()
{
    AdStats daily_stats{ getAdStats() };

    printAdStats(daily_stats);

    return 0;
}
