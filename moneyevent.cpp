#include "moneyevent.h"

moneyevent::moneyevent(int year,int month, int day, std::string desp, double val, bool sign)
{
    this->year = year;
    this->month = month;
    this->day = day;
    this->desp = desp;
    this->val = val;
    this->sign = sign;
}
