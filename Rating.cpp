/*!
* \file Rating.cpp
*
* FEUP_AEDA1415_2MIEIC03_D
* \author Carlos Soares
* \author Diogo Marques
* \author Fabio Carneiro
*
* \date Dezembro 2014
*
*/

#include "Rating.h"

double Rating::get() const {

	double result = 0.0;

	if (r.size() == 0) {
		return 3.0;
	}

	for (unsigned int i = 0; i < r.size(); i++) {
		result += r[i];
	}

	return (result / r.size());
}

string Rating::to_string() const {

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

unsigned Rating::floor() const {

	double x = get();

	if (x >= 0) {
		return (unsigned)(x + 0.5);
	}

	return (unsigned)(x - 0.5);
}

void Rating::read(ifstream &fin) {
	unsigned int sizeTemp;
	fin.read((char*)&sizeTemp, sizeof(unsigned int));
	vector<uint8_t> vectorTemp(sizeTemp);
	for (unsigned int i = 0; i < sizeTemp; i++) {
		uint8_t ratingTemp;
		fin.read((char*)&ratingTemp, sizeof(uint8_t));
		vectorTemp[i] = ratingTemp;
	}
	r = vectorTemp;
}

void Rating::write(ofstream &fout) const {
	unsigned int vecSize = r.size();
	fout.write((char*)&vecSize, sizeof(unsigned int));
	for (unsigned int i = 0; i < vecSize; i++) {
		uint8_t vecRating = r[i];
		fout.write((char*)&vecRating, sizeof(uint8_t));
	}
}
