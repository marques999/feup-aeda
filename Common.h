/*!
* \file Common.h
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

#ifndef COMMON_H_
#define COMMON_H_

#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <stdint.h>

using namespace std;

unsigned roundDouble(double x);

class DeveloperInexistente {
	string devName;
public:
	DeveloperInexistente(const string& n) {
		devName = n;
	}
	string getName() {
		return devName;
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
