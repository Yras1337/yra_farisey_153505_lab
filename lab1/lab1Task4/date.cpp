#include "date.h"
#include <string>
Date::Date()
{

}

std::string Date::stringDate(int day, int month, int year)
{
    std::string result;
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

Date Date::NextDay()
{
    Date x;
    x.day=this->day;
    x.month=this->month;
    x.year=this->year;
    if (this->day<28) {
        x.day++;
        x.formatDate=x.stringDate(x.day, x.month, x.year);
        return x;
    }
    else if(this->day==28){

        if(this->month==2) {

            if(IsLeap()){
                x.day++;
                x.formatDate=x.stringDate(x.day, x.month, x.year);
                return x;
            } else {
                x.day=1;
                x.month++;
                x.formatDate=x.stringDate(x.day, x.month, x.year);
                return x;
            }
        } else {
            x.day++;
            x.formatDate=x.stringDate(x.day, x.month, x.year);
            return x;
        }
    }
    else if(this->day==29) {
        if(this->month==2){
            x.day=1;
            x.month++;
            x.formatDate=x.stringDate(x.day, x.month, x.year);
            return x;
        }
        else {
            x.day++;
            x.formatDate=x.stringDate(x.day, x.month, x.year);
            return x;
        }
    }
    else if(this->day==30){
        if(this->month==4||this->month==6||this->month==9||this->month==11){
            x.day=1;
            x.month++;
            x.formatDate=x.stringDate(x.day, x.month, x.year);
            return x;
        }
        else {
            x.day++;
            x.formatDate=x.stringDate(x.day, x.month, x.year);
            return x;
        }
    }
    else {
        if(this->month==12){
            x.day=1;
            x.month=1;
            x.year++;
            x.formatDate=x.stringDate(x.day, x.month, x.year);
            return x;
        }
        else {
            x.day=1;
            x.month++;
            x.formatDate=x.stringDate(x.day, x.month, x.year);
            return x;
        }
    }

}

Date Date::PreviousDay()
{
    Date x;
    x.day=this->day;
    x.month=this->month;
    x.year=this->year;
    if(this->day==1 && this->month==1 && this->year==0){
        x.formatDate=x.stringDate(x.day, x.month, x.year);
        return x;
    }
    if(this->day==1) {
        if(this->month==1){
            x.year--;
            x.month=12;
            x.day=31;
            x.formatDate=x.stringDate(x.day, x.month, x.year);
            return x;
        }
        else if(this->month==2||this->month==4||this->month==6||this->month==8||this->month==9||this->month==11){
            x.month--;
            x.day=31;
            x.formatDate=x.stringDate(x.day, x.month, x.year);
            return x;
        } else {
            if(this->month==3){
                if(IsLeap()){
                    x.day=29;
                    x.month--;
                    x.formatDate=x.stringDate(x.day, x.month, x.year);
                    return x;
                } else {
                    x.day=28;
                    x.month--;
                    x.formatDate=x.stringDate(x.day, x.month, x.year);
                    return x;
                }
            } else {
                x.day=30;
                x.month--;
                x.formatDate=x.stringDate(x.day, x.month, x.year);
                return x;

            }
        }
    } else{
        x.day--;
        x.formatDate=x.stringDate(x.day, x.month, x.year);
        return x;
    }
}

bool Date::IsLeap()
{
    if((this->year % 400 == 0) || (this->year % 100 != 0 || this->year % 4 == 0)){
        return true;
    }
    else {
        return false;
    }
}

short Date::WeekNumber()
{
    Date x;
    short s=0;
    x.day=1;
    x.month=1;
    x.year=this->year;
    while(true){
        s++;
        if(x.day==this->day && x.month==this->month && x.year==this->year){
            return ((s-1)/7+1);
        }
        x=x.NextDay();

    }
}

int Date::DaysTillYourBirthday(Date birthdaydate)
{
    Date x;
    x.day=this->day;
    x.month=this->month;
    x.year=this->year;
    int s=0;
    while(true){

        if(x.day==birthdaydate.day && x.month==birthdaydate.month){
            return s;
        }
        x=x.NextDay();
        s++;

    }
}

int Date::Duration(Date date)
{
    Date x;
    x.day=this->day;
    x.month=this->month;
    x.year=this->year;
    int s=0;
    if(x.year<date.year||(x.year==date.year&&x.month<date.month)||(x.year==date.year&&x.month==date.month&&x.day<date.day)){
        while(true){
            if(x.day==date.day && x.month==date.month && x.year==date.year){
                return s;
            }
            x=x.NextDay();
            s++;
        }
    } else {
        while(true){
            if(x.day==date.day && x.month==date.month && x.year==date.year){
                return s;
            }
            date=date.NextDay();
            s++;
        }
    }

}

bool Date::validCheck()
{
    if(this->month>12||this->month<1){
        return false;
    }
    if(this->year<0) {
        return false;
    }
    if(this->month==1||this->month==3||this->month==4||this->month==5||this->month==6||this->month==8||this->month==10||this->month==12){
        if(this->day>31||this->day<1){
            return false;
        }
    } else if(this->month==2) {
        if(IsLeap()) {
            if(this->day>29||this->day<1){
                return false;
            }
        } else {
            if(this->day>28||this->day<1){
                return false;
            }
        }

    } else{
        if(this->day>30||this->day<1){
            return false;
        }
    }
    return true;

}

Date::Date(std::string s) {
    this->formatDate = s;
    this->day = int(s[0] - '0') * 10 + int(s[1] - '0');
    this->month = int(s[3] - '0') * 10 + int(s[4] - '0');
    this->year = int(s[6] - '0') * 1000 + int(s[7] - '0') * 100 + int(s[8] - '0') * 10 + int(s[9] - '0');
}
