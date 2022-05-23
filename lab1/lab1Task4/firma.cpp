#include "firma.h"

Firma::Firma()
{

}

void Firma::Init(string f, string i, string o, string projname, string task, string datestart, string dateend)
{
    F=f;
    this->I=i;
    this->O=o;
    this->projName=projname;
    this->Task=task;
    this->dateStart=datestart;
    this->dateEnd=dateend;
    this->day = int(dateend[0] - '0') * 10 + int(dateend[1] - '0');
    this->month = int(dateend[3] - '0') * 10 + int(dateend[4] - '0');
    this->year = int(dateend[6] - '0') * 1000 + int(dateend[7] - '0') * 100 + int(dateend[8] - '0') * 10 + int(dateend[9] - '0');

}

string Firma::toSort()
{
    string s="0123.56.89"; //01.34.6789
    s[0]=this->dateEnd[6];
    s[1]=this->dateEnd[7];
    s[2]=this->dateEnd[8];
    s[3]=this->dateEnd[9];
    s[5]=this->dateEnd[3];
    s[6]=this->dateEnd[4];
    s[8]=this->dateEnd[0];
    s[9]=this->dateEnd[1];
    return s;
}

string Firma::toStrFormat()
{
    string res;
    res+="ФИО: ";
    res+=F+' '+I+' '+O;
    res+="\n";
    res+="Название проекта: ";
    res+=projName;
    res+="\n";
    res+="Задание: ";
    res+=Task;
    res+="\n";
    res+="Дата начала: "+dateStart+"\nДата завершения: "+dateEnd;
    return res;

}

string Firma::toStrFile()
{
    return (F+' '+I+' '+O+' '+projName+' '+Task+' '+dateStart+' '+dateEnd);

}
