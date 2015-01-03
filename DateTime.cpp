/*!
* \file DateTime.cpp
*
* FEUP_AEDA1415_2MIEIC03_D
* \author Carlos Soares
* \author Diogo Marques
* \author Fabio Carneiro
*
* \date Janeiro 2015
*
*/

#include "DateTime.h"

Date::Date()
{
	struct tm * timeinfo = new struct tm;

	time_t rawtime;
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	this->day = timeinfo->tm_mday;
	this->month = timeinfo->tm_mon + 1;
	this->year = timeinfo->tm_year + 1900;
}

Date::~Date()
{
}

void Date::read(ifstream &fin)
{
	fin.read((char*)&day, sizeof(uint8_t));
	fin.read((char*)&month, sizeof(uint8_t));
	fin.read((char*)&year, sizeof(uint16_t));
}

void Date::write(ofstream &fout) const
{
	fout.write((char*)&day, sizeof(uint8_t));
	fout.write((char*)&month, sizeof(uint8_t));
	fout.write((char*)&year,sizeof(uint16_t));
}

bool Date::operator<(const Date &d) const
{
	if (year == d.year)
	{
		if (month == d.month)
		{
			return (day < d.day);
		}
		return (month < d.month);
	}
	return (year < d.year);
}

bool Date::operator>(const Date &d) const
{
	return (!operator<(d) && !operator==(d));
}

bool Date::operator==(const Date &d) const
{
	return (year == d.year && month == d.month && day == d.day);
}

ostream &operator<<(ostream& os, const Date &d)
{
	os << d.str();
	return os;
}

string Date::str() const
{
	ostringstream os;
	os << setw(2) << setfill('0') << int(day);
	os << "/";
	os << setw(2) << setfill('0') << int(month);
	os << "/";
	os << setw(4) << left << setfill(' ') << year;
	return os.str();
}
