/*!
 * \file UI.h
 *
 * FEUP_AEDA1415_2MIEIC03_D
 * \author Carlos Soares
 * \author Diogo Marques
 * \author Fabio Carneiro
 *
 * \date Janeiro 2015
 *
 */

#ifndef __UI_H_
#define __UI_H_

#include "Common.h"

namespace UI
{
	/**
	* @brief displays a frame (or header)
	* @param s string to be displayed
	*/
	void DisplayFrame(const string &s);

	/**
	* @brief displays a frame (or header), doesn't clear console screen
	* @param s string to be displayed
	*/
	void DisplayFrameNoCls(const string &s);

	/**
	* @brief displays text centered on screen
	* @param s string to be displayed
	*/
	void Display(const string &s);

	/**
	* @brief displays a brief error or informative message
	* @param s string to be displayed
	*/
	void DisplayMessage(const string &s);

	/**
	* @brief displays table header
	* @param c number of columns
	* @param labels array containing the labels
	* @param length array containing the width of each column (should be the same size as c)
	*/
	void DisplayTable(int c, const vector<string> &labels, const int length[]);

	/**
	* @brief displays a table row
	* @param c number of columns (same as DisplayTable())
	* @param labels array containing the row values
	* @param length array containing the width of each cell (should be the same size as c)
	*/
	void DisplayTableRow(int c, const vector<string> &labels, const int length[]);

	/**
	* @brief displays menu item
	* @param i row index
	* @param label array containing the row values
	*/
	void DisplayMenuItem(int i, const string &label);

	/**
	 * @brief displays top menu separator
	 */
	void DisplayMenuTop();

	/**
	 * @brief displays bottom menu separator
	 */
	void DisplayMenuBottom();

	/**
	* @brief formats the price in a user-friendly way (fixed point)
	* @param p number to be formatted
	* @return returns a string containing the formatted value
	*/
	string FormatPrice(double p);

	/**
	* @brief formats ratings in a user-friendly way (fixed point)
	* @param r number
	* @return returns a string containing the formatted value
	*/
	string FormatRating(double r);

	/**
	* @brief formats a fixed digit number (eg. the tax number)
	* @param n number
	* @param w number of digits (field width)
	* @return returns a string containing the formatted value
	*/
	string Format(unsigned n, unsigned w);
}

#endif
