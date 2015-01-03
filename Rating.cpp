/*!
* \file Rating.cpp
*
* FEUP_AEDA1415_2MIEIC03_D
* \author Carlos Soares
* \author Diogo Marques
* \author Fabio Carneiro
*
* \date Janeiro 2015
*
*/

#include "Rating.h"

double Rating::get() const
{
	double result = 0.0;

	if (r.size() == 0)
	{
		return 3.0;
	}

	for (auto &x : r)
	{
		result += x;
	}

	return (result / r.size());
}

string Rating::to_string() const
{
	switch (floor())
	{
	case 1:
		return "*";
	case 2:
		return "**";
	case 3:
		return "***";
	case 4:
		return "****";
	case 5:
		return "*****";
	default:
		return "";
	}
}

unsigned Rating::floor() const
{
	double x = get();

	if (x >= 0)
	{
		return (unsigned)(x + 0.5);
	}

	return (unsigned)(x - 0.5);
}

bool Rating::operator<(const Rating &r) const
{
	return get() < r.get();
}

void Rating::read(ifstream &fin)
{
	unsigned int sizeTemp;
	fin.read((char*)&sizeTemp, sizeof(unsigned));
	vector<uint8_t> vectorTemp(sizeTemp);
	for (unsigned int i = 0; i < sizeTemp; i++)
	{
		uint8_t ratingTemp;
		fin.read((char*)&ratingTemp, sizeof(uint8_t));
		vectorTemp[i] = ratingTemp;
	}
	r = vectorTemp;
}

void Rating::write(ofstream &fout) const
{
	unsigned int vecSize = r.size();
	fout.write((char*)&vecSize, sizeof(unsigned));
	for (auto &x : r)
	{
		fout.write((char*)&x, sizeof(uint8_t));
	}
}
