#ifndef DATE_H
#define DATE_H
#include <string>

class Date
{
    int day,month,year;
    std::string stringDate(int day, int month, int year);
public:
    Date();
    Date(std::string s);
    Date NextDay();
    Date PreviousDay();
    bool IsLeap();
    std::string formatDate;
    short WeekNumber();
    int DaysTillYourBirthday(Date birthdaydate);
    int Duration(Date date);
    bool validCheck();


};

#endif // DATE_H
