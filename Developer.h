/*!
 * \file Developer.h
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

#ifndef DEVELOPER_H_
#define DEVELOPER_H

#include "App.h"

typedef enum {
	DEVELOPER_INDIVIDUAL, DEVELOPER_EMPRESA
} DevType;

class Developer {
public:

	/**
	 * @brief default constructor for 'Developer' abstract class
	 */
	Developer() {
		this->numApps = 0;
	}

	/**
	 * @brief constructor with parameters for 'Developer' abstract class
	 * @param n customer's name / company official name
	 * @param a the customer's / company address
	 */
	Developer(string n, string a) {
		this->balance = 0.0;
		this->numApps = 0;
		this->name = n;
		this->address = a;
	}

	/**
	 * @brief default destructor for 'Developer' class
	 */
	virtual ~Developer() {
	}

	/**
	 * @brief returns the developer's address
	 */
	string getAddress() const {
		return this->address;
	}

	/**
	 * @brief returns the developer's current balance
	 */
	double getBalance() const {
		return this->balance;
	}

	/**
	 * @brief returns the developer's name
	 */
	string getName() const {
		return this->name;
	}

	/**
	 * @brief returns the number of apps published by the developer
	 */
	int getNumApps() const {
		return numApps;
	}

	/**
	 * @brief increments the number of apps associated with the developer by one
	 * @return const reference to 'this' object
	 */
	const Developer& operator++() {
		numApps++;
		return *this;
	}

	/**
	 * @brief decrements the number of apps associated with the developer by one
	 * @return const reference to 'this' object
	 */
	const Developer& operator--() {
		numApps--;
		return *this;
	}

	/**
	 * @brief returns the developer type (individual/company)
	 */
	virtual DevType getType() const = 0;

	/**
	 * @brief accumulates sales
	 * @param amount transaction amount
	 */
	void sale(double amount) {
		balance += amount * 0.8;
	}

	/**
	 * @brief sets the number of apps associated with the developer
	 * @param n the new number of apps
	 */
	void setNumApps(unsigned n) {
		this->numApps = n;
	}

	/**
	 * @brief sets the developer with a new address
	 * @param a the new address for the company/developer
	 */
	void setAddress(string a) {
		this->address = a;
	}

	/**
	 * @brief sets the developer with a new name
	 * @param n the new name for the company/developer
	 */
	void setName(string n) {
		this->name = n;
	}

	/**
	 * @brief reads developer information from a given file
	 * @param fin the input filestream
	 */
	virtual bool read(ifstream &fin) = 0;

	/**
	 * @brief writes developer information to a given file
	 * @param fout the output filestream
	 */
	virtual void write(ofstream &fout) const = 0;

	/**
	 * @brief prints the developer information in a user-friendly way
	 */
	virtual void print() const = 0;

protected:

	int numApps;
	string address;
	string name;
	double balance;
};

class Developer_Individual: public Developer {
public:

	/**
	 * @brief default constructor for 'Developer_Individual' class
	 */
	Developer_Individual() {
	}

	/**
	 * @brief constructor with parameters for 'Developer_Individual' class (same as 'Developer')
	 * @param n customer's name
	 * @param a customer's address
	 */
	Developer_Individual(string n, string a) :
			Developer(n, a) {
	}

	/**
	 * @brief default destructor for 'Developer_Individual' class
	 */
	~Developer_Individual() {
	}

	/**
	 * @brief returns the developer type (DEVELOPER_INDIVIDUAL)
	 */
	DevType getType() const {
		return DEVELOPER_INDIVIDUAL;
	}

	/**
	 * @brief reads developer information from a given file
	 * @param fin the input filestream
	 */
	bool read(ifstream &fin);

	/**
	 * @brief writes developer information to a given file
	 * @param fout the output filestream
	 */
	void write(ofstream &fout) const;

	/**
	 * @brief prints the developer information in a user-friendly way
	 */
	void print() const;
};

class Developer_Empresa: public Developer {
public:

	/**
	 * @brief default constructor for 'Developer_Empresa' class
	 */
	Developer_Empresa() {
	}

	/**
	 * @brief constructor with parameters for 'Developer_Empresa' class
	 * @param n company name
	 * @param a company address
	 * @param id company tax ID number
	 */
	Developer_Empresa(string n, string a, unsigned id) :
			Developer(n, a) {
		ostringstream os;
		os << id;
		if (os.str().length() != 9) {
			throw InvalidParameter("NIF");
		}
		this->NIF = id;
	}

	/**
	 * @brief default destructor for 'Developer_Empresa' class
	 */
	~Developer_Empresa() {
	}

	/**
	 * @brief returns the company tax ID number (9 digits)
	 */
	unsigned getNIF() const {
		return this->NIF;
	}

	/**
	 * @brief changes the company tax number
	 * @param id new company tax ID
	 */
	void setNIF(unsigned id) {
		this->NIF = id;
	}

	/**
	 * @brief returns the developer type (DEVELOPER_EMPRESA)
	 */
	DevType getType() const {
		return DEVELOPER_EMPRESA;
	}

	/**
	 * @brief reads developer information from a given file
	 * @param fin the input filestream
	 */
	bool read(ifstream &fin);

	/**
	 * @brief writes developer information to a given file
	 * @param fout the output filestream
	 */
	void write(ofstream &fout) const;

	/**
	 * @brief prints the developer info in a user-friendly way
	 */
	void print() const;

private:

	unsigned NIF;
};

#endif
