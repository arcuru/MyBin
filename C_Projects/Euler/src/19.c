#include "Euler.h"

int64_t Euler_19()
{
    int day = 1;
    int weekday = 3;
    int month = 1;
    int year = 1901;
    int count = 0;
    while ((day + month + year) < 2043) {
        if (weekday < 7) {
            weekday++;
        } else {
            weekday = 1;
        }

        if ((month == 4) || (month == 6) || (month == 9) || (month == 11)) {//April, June, September, November
            if (day == 30) {
                day = 1;
                month++;
            } else {
                day++;
            }
        } else if (month == 2) {//February
            if (((year % 4 != 0) && (day == 28)) || ((year % 4 == 0) && (day
                    == 29)) || ((year % 100 == 0) && (day == 28))) {
                day = 1;
                month++;
            } else {
                day++;
            }
        } else {
            if (day == 31) {
                day = 1;
                if (month == 12) {
                    month = 1;
                    year++;
                } else {
                    month++;
                }
            } else {
                day++;
            }
        }

        if ((day == 1) && (weekday == 1)) {
            count++;
        }
    }
    return (int64_t) count;
}
