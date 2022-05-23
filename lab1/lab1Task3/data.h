#ifndef DATA_H
#define DATA_H
#include <string>
#include <ctime>
using namespace std;

class Data
{
public:
    Data();
    void add(string nrDate, int nrNum, string nrLoc, string nrTime, int nrKPlace, int nrPPlace, int nrKFreePlase, int nrPFreePlace);
    string to_str_format();
    string to_str();
    int get_day_of_week();
    string get_date();
    string get_location();
    string get_rTime();
    int get_nReis();
    int get_kPlace();
    int get_pPlace();
    int get_kFreePlase();
    int get_pFreePlase();
private:
    string date, location, rTime;
    int nReis, kPlace, pPlace, kFreePlase, pFreePlase;
    int day, month, year;
};

#endif // DATA_H
