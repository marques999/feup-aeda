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

/**
 * @brief returns the local time on the computer
 * @return tm a time structure containing the current date and time
 */
struct tm tm_localtime();

/**
 * @brief writes date and time information to a given file
 * @param timeinfo a time data structure containing the information
 * @param fout the output filestream
 */
void tm_write(struct tm timeinfo, ofstream &fout);

/**
 * @brief reads date and time information from a given file
 * @param timeinfo a pointer to the time data structure where information is going to be placed
 * @param fin the input filestream
 */
void tm_read(struct tm *timeinfo, ifstream &fin);

/**
 * @brief compares two dates
 * @param t1 a time structure for comparison (left operand)
 * @param t2 another time structure for comparison (right operand)
 * @return if date t1 is before date t2 (happens earlier)
 */
bool operator<(struct tm t1, struct tm t2);

/**
 * @brief compares two dates for equality
 * @param t1 a time structure (left operand)
 * @param t2 another time data structure (right operand)
 * @return if date t1 is equal to date t2
 */
bool operator==(struct tm t1, struct tm t2);

/**
 * @brief displays time information in a more user-friendly way
 * @param t1 a time structure to display information from
 * @returns a formatted string (HH:MM)
 */
string tm_converttime(struct tm t1);

/**
 * @brief displays date information in a more user-friendly way
 * @param t1 a time structure to display information from
 * @returns a formatted string (DD/MM/YY)
 */
string tm_convertdate(struct tm t1);

/**
 * @brief displays date information in a more user-friendly way
 * @param os output stream
 * @param t1 a time structure to display information from
 * @returns reference to an output stream
 */
ostream &operator<<(ostream& os, struct tm t1);

#endif /* __DATETIME_H_ */
