#include <iostream>

struct DateTime
{
    int year;
    int month;
    int day;
    int hour;
};

bool isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int daysInMonth(int year, int month)
{
    int daysPerMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year))
    {
        return 29;
    }
    return daysPerMonth[month - 1];
}

DateTime calculateDateTime(int totalHours)
{
    int year = 2017;
    int remainingHours = totalHours;

    // Step 1: Calculate the year
    while (true)
    {
        int daysInCurrentYear = isLeapYear(year) ? 366 : 365;
        if (remainingHours >= daysInCurrentYear * 24)
        {
            remainingHours -= daysInCurrentYear * 24;
            year++;
        }
        else
        {
            break;
        }
    }

    // Step 2: Calculate the month
    int month = 1;
    while (true)
    {
        int daysInCurrentMonth = daysInMonth(year, month);
        if (remainingHours >= daysInCurrentMonth * 24)
        {
            remainingHours -= daysInCurrentMonth * 24;
            month++;
        }
        else
        {
            break;
        }
    }

    // Step 3: Calculate the day
    int day = remainingHours / 24 + 1; // Day starts from 1
    remainingHours %= 24;

    // Step 4: Calculate the hour
    int hour = remainingHours;

    return {year, month, day, hour};
}

int main()
{
    int totalHours;
    std::cout << "Enter the total number of hours: ";
    std::cin >> totalHours;

    DateTime result = calculateDateTime(totalHours);

    std::cout << "Year: " << result.year
              << ", Month: " << result.month
              << ", Day: " << result.day
              << ", Hour: " << result.hour << std::endl;

    return 0;
}
