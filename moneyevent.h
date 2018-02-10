#ifndef MONEYEVENT_H
#define MONEYEVENT_H
#include <time.h>
#include <string>

class moneyevent
{
public:
    moneyevent(int year,int month, int day, std::string desp, double val = 0, bool sign = 1);

private:
    int year;
    int month;
    int day;
    std::string desp;
    double val;
    bool sign;
};

#endif // MONEYEVENT_H
