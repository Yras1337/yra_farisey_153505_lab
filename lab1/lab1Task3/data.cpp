#include "data.h"

Data::Data()
{

}
void Data::add(string nrDate, int nrNum, string nrLoc, string nrTime, int nrKPlace, int nrPPlace, int nrKFreePlase, int nrPFreePlace){
    this->date = nrDate;
    this->nReis = nrNum;
    this->location = nrLoc;
    this->rTime = nrTime;
    this->kPlace = nrKPlace;
    this->pPlace = nrPPlace;
    this->kFreePlase = nrKFreePlase;
    this->pFreePlase = nrPFreePlace;
    this->day = int(nrDate[0] - '0') * 10 + int(nrDate[1] - '0');
    this->month = int(nrDate[3] - '0') * 10 + int(nrDate[4] - '0');
    this->year = int(nrDate[6] - '0') * 1000 + int(nrDate[7] - '0') * 100 + int(nrDate[8] - '0') * 10 + int(nrDate[9] - '0');
}
string Data::to_str_format(){
    string res;
    res += "дата:";
    res += this->date;
    res += "\n";
    res += "номер рейса:";
    res += to_string(this->nReis);
    res += "\n";
    res += "конечный пункт:";
    res += this->location;
    res += "\n";
    res += "время отправления:";
    res += this ->rTime;
    res += "\n";
    res += "количество мест в купе:";
    res += to_string(this->kPlace);
    res += "\n";
    res += "количество мест в плацкарте:";
    res += to_string(this->pPlace);
    res += "\n";
    res += "количество свободных мест в купе:";
    res += to_string(this->kFreePlase);
    res += "\n";
    res += "количество свободных мест в плацкарте:";
    res += to_string(this->pFreePlase);
    return res;
}
string Data::to_str(){
    string res;
    res += this->date;
    res += " ";
    res += to_string(this->nReis);
    res += " ";
    res += this->location;
    res += " ";
    res += this ->rTime;
    res += " ";
    res += to_string(this->kPlace);
    res += " ";
    res += to_string(this->pPlace);
    res += " ";
    res += to_string(this->kFreePlase);
    res += " ";
    res += to_string(this->pFreePlase);
    return res;
}
int Data::get_day_of_week(){
    time_t raw_t;
    std::tm *time_in;
    time(&raw_t);
    time_in = localtime(&raw_t);
    time_in->tm_year = this->year - 1900;
    time_in->tm_mon= this->month - 1;
    time_in->tm_mday = this->day;
    mktime(time_in);
    return (int)time_in->tm_wday;
}
string Data::get_date(){
    return this->date;
}
string Data::get_location(){
    return this->location;
}
string Data::get_rTime(){
    return this->rTime;
}
int Data::get_nReis(){
    return this->nReis;
}
int Data::get_kPlace(){
    return this->kPlace;
}
int Data::get_kFreePlase(){
    return this->kFreePlase;
}
int Data::get_pFreePlase(){
    return this->pFreePlase;
}
int Data::get_pPlace(){
    return this->pPlace;
}
