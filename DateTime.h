/*!
 * \file DateTime.h
 *
 * FEUP_AEDA1415_2MIEIC03_D
 * \author Carlos Soares
 * \author Diogo Marques
 * \author Fabio Carneiro
 *
 * \date Dezembro 2014
 *
 */

#ifndef __DATETIME_H_
#define __DATETIME_H_

#include "Common.h"

struct tm tm_localtime() {
	struct tm * timeinfo = new struct tm;
	time_t rawtime;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	return *timeinfo;
}

void tm_write(struct tm* timeinfo, ofstream &fout) {
	time_t rawtime = mktime(timeinfo);
	fout.write((char*)&rawtime, sizeof(time_t));
}

struct tm tm_read(time_t rawtime, ifstream &fout) {
	struct tm *timeinfo = new struct tm;
	fout.read((char*)&rawtime, sizeof(time_t));
	timeinfo = localtime(&rawtime);
	return *timeinfo;
}

bool operator<(struct tm t1, struct tm t2) {
	if (t1.tm_year == t2.tm_year) {
		if (t1.tm_mon == t2.tm_mon) {
			return (t1.tm_mday < t2.tm_mday);
		}
		return (t1.tm_mon < t2.tm_mon);
	}
	return (t1.tm_year < t2.tm_year);
}

bool operator==(struct tm t1, struct tm t2) {
	return (t1.tm_year == t2.tm_year && t1.tm_mon == t2.tm_mon && t1.tm_mday == t2.tm_mday);
}

string tm_converttime(struct tm t1) {
	ostringstream os;
	os << setw(2) << setfill('0') << t1.tm_hour;
	os << ":";
	os << setw(2) << setfill('0') << t1.tm_min;
	return os.str();
}

string tm_convertdate(struct tm t1) {
	ostringstream os;
	os << setw(2) << setfill('0') << t1.tm_mday;
	os << "/";
	os << setw(2) << setfill('0') << t1.tm_mon;
	os << "/";
	os << setw(4) << left << setfill(' ') << t1.tm_year + 1900;
	return os.str();
}

ostream &operator<<(ostream& os, struct tm t1) {
	os << tm_convertdate(t1);
	return os;
}

#endif /* __DATETIME_H_ */
