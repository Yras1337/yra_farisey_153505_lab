#ifndef DATE_H
#define DATE_H
#include <string>
using std::string;

class Date
{
    int curDay;
    int curMonth;
    int curYear;
    int to_days();
    string to_string_format(int day, int month, int year);
public:
    bool valid_check();
    string formatDate;
    Date();
    Date(string s);
    Date nextDay();
    Date PreviousDay();
    short WeekNumber();
    int DaysTillYourBithday(Date bithdaydate);
    int Duration(Date date);
};

#endif // DATE_H
