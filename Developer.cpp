/*!
* \file Developer.cpp
*
* FEUP_AEDA1415_2MIEIC03_D
* \author Carlos Soares
* \author Diogo Marques
* \author Fabio Carneiro
*
* \date Novembro 2014
*
*/

#include "Developer.h"

void Developer_Individual::print() const
{
	const int rowCount = 4;
	int tableLength[rowCount] = { 24, 24, 12, 11 };
	vector<string> tableRow = { name, address, "Individual", "-",};
	UI::DisplayTableRow(rowCount, tableRow, tableLength);
}

void Developer_Empresa::print() const
{
	const int rowCount = 4;
	int tableLength[rowCount] = { 24, 24, 12, 11 };
	vector<string> tableRow = { name, address, "Empresa" , UI::Format(NIF, 9) };
	UI::DisplayTableRow(rowCount, tableRow, tableLength);
}

bool Developer_Individual::read(ifstream &fin) {
	getline(fin, name);
	if (name == "") {
		return false;
	}
	getline(fin, address);
	fin.read((char*)&numApps, sizeof(unsigned));
	fin.read((char*)&balance, sizeof(double));
	return true;
}

void Developer_Individual::write(ofstream &fout) const {
	fout << name << endl;
	fout << address << endl;
	fout.write((char*)&numApps, sizeof(unsigned));
	fout.write((char*)&balance, sizeof(double));
}

bool Developer_Empresa::read(ifstream &fin) {
	getline(fin, name);
	if (name == "") {
		return false;
	}
	getline(fin, address);
	fin.read((char*)&NIF, sizeof(unsigned));
	fin.read((char*)&numApps, sizeof(unsigned));
	fin.read((char*)&balance, sizeof(double));
	return true;
}

void Developer_Empresa::write(ofstream &fout) const {
	fout << name << endl;
	fout << address << endl;
	unsigned tempNIF = NIF;
	fout.write((char*)&tempNIF, sizeof(unsigned));
	fout.write((char*)&numApps, sizeof(unsigned));
	fout.write((char*)&balance, sizeof(double));
}