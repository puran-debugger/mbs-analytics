#ifndef UTILITIES_H
#define UTILITIES_H

#include <cmath>
#include <ctime>

namespace Utilities
{

const double EPSILON = 0.000001;

inline double changeCompoundingBasis(
    double rate, int origCompoundsPerYear, int newCompoundsPerYear)
{
    return 1.0 - pow(1.0 - rate, float(origCompoundsPerYear) / float(newCompoundsPerYear));
}

inline double calculatePayment(double balance, int amortTerm, double periodicRate)
{
    if (amortTerm == 0)
    {
        return periodicRate * balance;
    }
    else
    {
        return balance * periodicRate / (1 - pow(1 + periodicRate, -amortTerm));
    }
}

inline struct tm createTime(int year, int month, int day)
{
    struct tm date;
    date.tm_hour = 0;
    date.tm_min = 0;
    date.tm_sec = 0;
    date.tm_year = year - 1900;
    date.tm_mon = month - 1;
    date.tm_mday = day;
    return date;
}

} // namespace Utilities

#endif