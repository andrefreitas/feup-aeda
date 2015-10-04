#ifndef TYPES_H_
#define TYPES_H_
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
using namespace std;
//! Class Date
/*! This class defines an object that have a day, a month and an year
*/
class date {
public:
	//! Day
	int day;
	//! Month
	int mon;
	//! Year
	int year;
	//! Empty Constructor
	date() {
	}
	//! Constructor that receives a date string
	/*!
	 \param dateSt a date string in the format DD/MM/(YY)YY
	 */
	date(string dateSt) {
		// (1) Fetch the substrings
		// -> Day
		int posDay = dateSt.find("/");
		string stDay = dateSt.substr(0, posDay);
		dateSt[posDay] = '*';
		// -> Month
		int posMon = dateSt.find("/");
		string stMon = dateSt.substr(posDay + 1, posMon - (posDay + 1));
		dateSt[posMon] = '*';
		// -> Year
		string stYear = dateSt.substr(posMon + 1, dateSt.size() - (posMon + 1));
		// (2) Converting the substrings to integers
		day = atoi(stDay.c_str());
		mon = atoi(stMon.c_str());
		year = atoi(stYear.c_str());
	}

	//! Print the date in the format DD/MM/YYYY
	/*!
	 \returns a date string
	 */
	string print() {
		stringstream os;
		os << day << "/" << mon << "/" << year;
		return os.str();
	}
};

typedef double money;

#endif
