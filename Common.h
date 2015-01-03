/*!
 * \file Common.h
 *
 * FEUP_AEDA1415_2MIEIC03_D
 * \author Carlos Soares
 * \author Diogo Marques
 * \author Fabio Carneiro
 *
 * \date Janeiro 2015
 *
 */

#ifndef __COMMON_H_
#define __COMMON_H_

#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

class DeveloperInexistente {

	string devName;

public:

	DeveloperInexistente(const string& n) {
		devName = n;
	}

	friend ostream& operator<<(ostream &os, const DeveloperInexistente &e) {
		os << "\nERRROR: developer " << e.devName << " not found.\n";
		return os;
	}
};

class DeveloperJaExiste {

	string devName;

public:

	DeveloperJaExiste(const string &n) {
		devName = n;
	}

	friend ostream& operator<<(ostream &os, const DeveloperJaExiste &e) {
		os << "\nERROR: developer " << e.devName << " already exists.\n";
		return os;
	}
};

class ClienteInexistente {

	string cliName;

public:

	ClienteInexistente(const string &n) {
		cliName = n;
	}

	friend ostream& operator<<(ostream &os, const ClienteInexistente &e) {
		os << "\nERROR: customer " << e.cliName << " not found.\n";
		return os;
	}
};

class ClienteJaExiste {

	string cliName;

public:

	ClienteJaExiste(const string &n) {
		cliName = n;
	}

	friend ostream& operator<<(ostream& os, const ClienteJaExiste &e) {
		os << "\nERROR: customer " << e.cliName << " already exists.\n";
		return os;
	}
};

class AppInexistente {

	string appName;

public:

	AppInexistente(const string &n) {
		appName = n;
	}

	friend ostream& operator<<(ostream &os, const AppInexistente &e) {
		os << "\nERROR: app " << e.appName << " not found.\n";
		return os;
	}
};

class AppExisteNoCarrinho {

	string appName;

public:

	AppExisteNoCarrinho(const string &n) {
		appName = n;
	}

	friend ostream& operator<<(ostream &os, const AppExisteNoCarrinho &e) {
		os << "\nERROR: couldn't add " << e.appName	<< " to cart - already exists\n";
		return os;
	}
};

class AppJaExiste {

	string appName;

public:

	AppJaExiste(const string &n) {
		appName = n;
	}

	friend ostream& operator<<(ostream &os, const AppJaExiste &e) {
		os << "\nERROR: app " << e.appName << " already exits.\n";
		return os;
	}
};

class PermissoesInsuficientes {

	string param;

public:

	PermissoesInsuficientes(const string &n) {
		param = n;
	}

	friend ostream& operator<<(ostream &os, const PermissoesInsuficientes &e) {
		os << "ERROR: permission denied - can't access " << e.param << " from other developers.\n";
		return os;
	}
};

class InvalidParameter {

	string param;

public:

	InvalidParameter(const string &p) {
		param = p;
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

	friend ostream& operator<<(ostream &os, const FileIOException &e) {
		os << "\nERROR: file I/O exception occured while trying to read/write " << e.fileName << "\n";
		return os;
	}
};

string to_upper(const string &s);

#endif /* __COMMON_H_ */
