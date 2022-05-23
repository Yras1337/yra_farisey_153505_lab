#include "date.h"
int numberDays[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
Date::Date(){
}
Date::Date(string s){
    this->formatDate = s;
    this->curDay = int(s[0] - '0') * 10 + int(s[1] - '0');
    this->curMonth = int(s[3] - '0') * 10 + int(s[4] - '0');
    this->curYear = int(s[6] - '0') * 1000 + int(s[7] - '0') * 100 + int(s[8] - '0') * 10 + int(s[9] - '0');
}
int Date::to_days(){
    int countDays = this->curYear * 365 + this->curDay + this->curYear / 4 - this->curYear / 100 + this->curYear / 400;
    for (int i = 1; i < this->curMonth; i++){
        countDays += numberDays[i] + (this->WeekNumber() && i == 2);
    }
    return countDays;
}
string Date::to_string_format(int day, int month, int year){
    string result;
    result += char(day / 10 + '0');
    result += char(day % 10 + '0');
    result += '.';
    result += char(month / 10 + '0');
    result += char(month % 10 + '0');
    result += '.';
    result += char(year / 1000 + '0');
    result += char(year / 100 % 10 + '0');
    result += char(year / 10 % 10 + '0');
    result += char(year % 10 + '0');
    return result;
}
Date Date::nextDay(){
    Date result;
    result.curDay = this->curDay + 1;
    result.curMonth = this->curMonth;
    result.curYear = this->curYear;
    if (numberDays[result.curMonth] + (result.curMonth == 2 && result.WeekNumber()) < result.curDay){
        result.curDay = 1;
        result.curMonth += 1;
        if (result.curMonth > 12){
            result.curMonth = 1;
            result.curYear += 1;
        }
    }
    result.formatDate = to_string_format(result.curDay, result.curMonth, result.curYear);
    return result;
}
Date Date::PreviousDay(){
    Date result;
    result.curDay = this->curDay - 1;
    result.curMonth = this->curMonth;
    result.curYear = this->curYear;
    if (result.curDay < 1){
        result.curMonth -= 1;
        if (result.curMonth < 1){
            result.curMonth = 12;
            result.curYear -= 1;
        }
        result.curDay = numberDays[result.curMonth] + (result.curMonth == 2 && result.WeekNumber());
    }
    result.formatDate = to_string_format(result.curDay, result.curMonth, result.curYear);
    return result;
}
short Date::WeekNumber(){
    if (this->curYear % 400 == 0){
        return 1;
    }
    if (this->curYear % 100 == 0){
        return 0;
    }
    if (this->curYear % 4 == 0){
        return 1;
    }
    return 0;
}
int Date::DaysTillYourBithday(Date bithdaydate){
    int days_first = this->to_days();
    bithdaydate.curYear = this->curYear;
    int days_second = bithdaydate.to_days();
    if (days_first > days_second){
        return 365 - (days_first - days_second);
    }
    else{
        return days_second - days_first;
    }
}
int Date::Duration(Date date){
    return abs(this->to_days() - date.to_days());
}
bool Date::valid_check(){
    if (this->curDay > numberDays[this->curMonth] + (this->curMonth == 2 && this->WeekNumber()) || this->curMonth > 12 || this->curMonth == 0 || this->curDay == 0 || this->curYear < 0){
        return 0;
    }
    return 1;
}
