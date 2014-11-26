/*!
* \file Rating.h
*
* FEUP_AEDA1415_2MIEIC03_D
* \author Carlos Soares
* \author Diogo Marques
* \author Fabio Carneiro
* \author Joao Santos
*
* \date Novembro 2014
*
*/

#ifndef RATING_H_
#define RATING_H_

#include "Common.h"

class Rating {
public:

	/**
	* @brief reads ratings data from a file in binary format
	* @param fin the input stream (should contain the input file)
	*/
	void read(ifstream &fin);

	/**
	* @brief writes ratings data to a file in binary format
	* @param fout the output stream (should contain the output file)
	*/
	void write(ofstream &fout) const;

	/**
	* @brief computes the arithmetic average of the ratings given by customers
	* @return a floating-point number containing the value
	*/
	double get() const;

	/**
	* @brief converts the ratings to a more user-friendly representation
	* @return a string containing the graphical representation
	*/
	string to_string() const;

	/**
	* @brief rounds the value computed by the method get() to the nearest integer
	* @return an integer containing the rounded value
	*/
	unsigned floor() const;

	/**
	 * @brief a vector containing the ratings given by customers
	 */
	vector<uint8_t> r;
};

#endif
