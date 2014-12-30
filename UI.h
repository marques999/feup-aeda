/*!
 * \file UI.h
 *
 * FEUP_AEDA1415_2MIEIC03_D
 * \author Carlos Soares
 * \author Diogo Marques
 * \author Fabio Carneiro
 *
 * \date Dezembro 2014
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
	* @return void
	*/
	void DisplayFrame(string s);

	/**
	* @brief displays text centered on screen
	* @param s string to be displayed
	* @return void
	*/
	void Display(string s);

	/**
	* @brief displays a brief error or informative message
	* @param s string to be displayed
	* @return void
	*/
	void DisplayMessage(string s);

	/**
	* @brief displays the table header
	* @param c the number of columns
	* @param labels an array containing the labels
	* @param length an array containing the width of each column (should be the same size as c)
	* @return void
	*/
	void DisplayTable(int c, vector<string> labels, int length[]);

	/**
	* @brief displays a table row
	* @param c the number of columns (same as DisplayTable())
	* @param labels an array containing the row values
	* @param length an array containing the width of each cell (should be the same size as c)
	* @return void
	*/
	void DisplayTableRow(int c, vector<string> labels, int length[]);

	/**
	* @brief displays a new menu item
	* @param i index
	* @param label an array containing the row values
	* @return void
	*/
	void DisplayMenuItem(int i, string label);

	void DisplayMenuTop();

	void DisplayMenuBottom();

	/**
	* @brief formats the price in a user-friendly way (fixed point)
	* @param p number to be formatted
	* @return a string containing the formatted value
	*/
	string FormatPrice(double p);

	/**
	* @brief formats ratings in a user-friendly way (fixed point)
	* @param p number to be formatted
	* @return a string containing the formatted value
	*/
	string FormatRating(double r);

	/**
	* @brief formats a fixed digit number (eg. the tax number)
	* @param p number to be formatted
	* @param r number of digits
	* @return a string containing the formatted value
	*/
	string Format(unsigned n, unsigned w);
}

#endif
