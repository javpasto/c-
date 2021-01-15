#ifndef date_h
#define date_h

#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <string>


typedef time_t tDate;

tDate currDate();

std::string dateToStr(tDate date, bool time);


#endif //date_h