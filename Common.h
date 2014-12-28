/*!
* \file Common.h
*
* FEUP_AEDA1415_2MIEIC03_D
* \author Carlos Soares
* \author Diogo Marques
* \author Fabio Carneiro
*
* \date Novembro 2014
*
*/

#ifndef COMMON_H_
#define COMMON_H_

#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdint>

using namespace std;

class DeveloperInexistente {

	string devName;

public:


	DeveloperInexistente(const string& n) {
		devName = n;
	}

	string getName() {
		return devName;
	}

	friend ostream& operator<<(ostream &os, const DeveloperInexistente &e) {
		os << "\nERRROR: developer " << e.devName << " not found.\n";
		return os;
	}
};

class ClienteInexistente {

	string cliName;

public:

	ClienteInexistente(const string &n) {
		cliName = n;
	}

	string getName() {
		return cliName;
	}

	friend ostream& operator<<(ostream &os, const ClienteInexistente &e) {
		os << "\nERROR: customer " << e.cliName << " not found.\n";
		return os;
	}
};

class AppInexistente {

	string appName;

public:

	AppInexistente(const string &n) {
		appName = n;
	}

	string getName() {
		return appName;
	}

	friend ostream& operator<<(ostream &os, const AppInexistente &e) {
		os << "\nERROR: app " << e.appName << " not found.\n";
		return os;
	}
};

class JaExiste {

	string name;

public:

	JaExiste(const string &n) {
		name = n;
	}

	string getName() {
		return name;
	}

	friend ostream& operator<<(ostream &os, const JaExiste &e) {
		os << "\nERROR: customer " << e.name << " already exists.\n";
		return os;
	}
};

class InvalidParameter {

	string param;

public:

	InvalidParameter(const string &p) {
		param = p;
	}

	string what() {
		return param;
	}

	friend ostream& operator<<(ostream &os, const InvalidParameter &ip) {
		os << "\nERROR: invalid parameter " << ip.param << "\n";
		return os;
	}
};

class FileIOException  {
	string fileName;
public:
	FileIOException(const string &fn) {
		fileName = fn;
	}
	string what() {
		return fileName;
	}
};

template<class Comparable>
bool sequentialSearch(const vector<Comparable> &v, Comparable value) {
	for (size_t i = 0; i < v.size(); i++) {
		if (v[i] == value) {
			return true;
		}
	}
	return false;
}

string to_upper(const string &s);

#endif
