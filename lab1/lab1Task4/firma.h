#ifndef FIRMA_H
#define FIRMA_H
#include <string>
using namespace std;

class Firma
{
public:
    Firma();
    void Init(string f, string i, string o, string projname, string task, string datestart, string dateend);
    string F,I,O,projName,Task,dateStart,dateEnd;
    string toSort();
    string toStrFormat();
    string toStrFile();
    int day, month, year;

};

#endif // FIRMA_H
