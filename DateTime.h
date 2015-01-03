/*!
 * \file DateTime.h
 *
 * FEUP_AEDA1415_2MIEIC03_D
 * \author Carlos Soares
 * \author Diogo Marques
 * \author Fabio Carneiro
 *
 * \date Janeiro 2015
 *
 */

#ifndef __DATETIME_H_
#define __DATETIME_H_

#include "Common.h"

class Date
{

public:

	/**
	 * @brief default construtor for 'Date' class
	 */
	Date();

	/**
	 * @brief default destructor for 'Date' class
	 */
	~Date();

	/**
	 * @brief compares two dates
	 * @param d right operand for comparison
	 * @return returns true if date is before date 'd' (happens earlier); false otherwise
	 */
	bool operator<(const Date &d) const;

	/**
	 * @brief compares two dates for equality
	 * @param d right operand for comparison
	 * @return returns true if dates are equal; false otherwise
	 */
	bool operator==(const Date &d) const;

	/**
	 * @brief displays date information in a more user-friendly way
	 * @param os output stream
	 * @param t1 a time structure to display information from
	 * @return returns a reference to the output stream
	 */
	friend ostream &operator<<(ostream& os, const Date &d);

	/**
	 * @brief displays date information in a more user-friendly way
	 * @return returns a formatted string (DD/MM/YY)
	 */
	string str() const;

	/**
	 * @brief reads date and time information from a given file
	 * @param fin the input filestream
	 */
	void read(ifstream &fin);

	/**
	 * @brief writes date and time information to a given file
	 * @param fout the output filestream
	 */
	void write(ofstream &fout) const;

private:

	uint8_t day;
	uint8_t month;
	uint16_t year;
};

#endif /* __DATETIME_H_ */
