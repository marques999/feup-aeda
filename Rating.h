/*!
 * \file Rating.h
 *
 * FEUP_AEDA1415_2MIEIC03_D
 * \author Carlos Soares
 * \author Diogo Marques
 * \author Fabio Carneiro
 *
 * \date Janeiro 2015
 *
 */

#ifndef __RATING_H_
#define __RATING_H_

#include "Common.h"

class Rating
{

public:

	/**
	* @brief reads ratings data from a file in binary format
	* @param fin the input file stream
	*/
	void read(ifstream &fin);

	/**
	* @brief writes ratings data to a file in binary format
	* @param fout the output file stream
	*/
	void write(ofstream &fout) const;

	/**
	* @brief computes the arithmetic average of the ratings given by customers
	* @return returns a floating-point number containing the value
	*/
	double get() const;

	/**
	* @brief converts the ratings to a more user-friendly representation
	* @return returns a string containing the graphical representation
	*/
	string to_string() const;

	/**
	* @brief rounds the value computed by the method get() to the nearest integer
	* @return returns an integer containing the rounded value
	*/
	unsigned floor() const;

	/**
	 * @brief compares two ratings
	 * @return returns true if left operand rating is lower; false otherwise
	 */
	bool operator<(const Rating &r) const;

	/**
	 * @biref vector containing the ratings given by customers
	 */
	vector<uint8_t> r;
};

#endif /* __RATING_H_ */
