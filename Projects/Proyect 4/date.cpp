#include "date.h"
#include <sstream>

tDate currDate() {
	return time(0);
}


std::string dateToStr(tDate date, bool time) {
	std::ostringstream result;
	tm ltm;
	localtime_s(&ltm, &date);
	result << setfill('0') << setw(4) << 1900 + ltm.tm_year << '/'
		<< setw(2) << 1 + ltm.tm_mon << '/' << setw(2)
		<< ltm.tm_mday;
	if(time) {
		result << ' (' << setw(2) << ltm.tm_hour << ':'
			<< setw(2) << ltm.tm_min << ':' << setw(2)
			<< ltm.tm_sec << ')';
	}
	return result.str();
}