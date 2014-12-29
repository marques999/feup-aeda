/*!
 * \file Developer.h
 *
 * FEUP_AEDA1415_2MIEIC03_D
 * \author Carlos Soares
 * \author Diogo Marques
 * \author Fabio Carneiro
 *
 * \date Dezembro 2014
 *
 */

#ifndef __DEVELOPER_H_
#define __DEVELOPER_H_

#include <tr1/unordered_set>
#include "App.h"

typedef enum {
	DEVELOPER_INDIVIDUAL, DEVELOPER_EMPRESA
} DevType;

struct developerH {

	int operator()(const App& lhs) {

		int appHash = 0;
		string appName = lhs.getName();

		for ( size_t i = 0; i < appName.size() ; i++ ) {
			appHash = 37*appHash + appName[i];
		}

		return appHash;
	}

	bool operator()(const App &lhs, const App &rhs) {

		return lhs.getName() == rhs.getName();
	}
};

typedef tr1::unordered_set<App, developerH, developerH> hashDeveloper;

class Developer {
public:

	/**
	 * @brief default constructor for 'Developer' abstract class
	 */
	Developer() {
		this->balance = 0.0;
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
	 * @brief returns the removed apps from the developer
	 */
	hashDeveloper getRemovedApps() const {
		return removedApps;
	}

	/**
	 * @brief returns the apps published by this developer
	 */
	hashDeveloper getPublishedApps() const {
		return removedApps;
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
	 * @brief sets the developer with a new removed apps table
	 * @param ht the new hashtable containing removed apps (unordered_set)
	 */
	void setRemovedApps(const hashDeveloper &ht) {
		this->removedApps.clear();
		this->removedApps = ht;
	}

	/**
	 * @brief pushes a new app to the published apps vector
	 * @param ht a pointer to the new app
	 */
	void push(App* app) {
		publishedApps.push_back(app);
	}

	/**
	 * @brief removes an existing app from the published apps vector
	 */
	void pop(App* app) {

		vector<App*>::iterator it = find(publishedApps.begin(), publishedApps.end(), app);

		if (it != publishedApps.end()) {
			publishedApps.erase(it);
		}
	}

	/**
	 * @brief prints the developer information in a user-friendly way
	 */
	virtual void print() const = 0;

	/**
	 * @brief reads developer information from a given file
	 * @param fin the input filestream
	 */
	virtual bool read(ifstream &fin) = 0;

	/**
	 * @brief accumulates sales
	 * @param amount transaction amount
	 */
	void sale(double amount) {
		balance += amount * 0.8;
	}

	/**
	 * @brief writes developer information to a given file
	 * @param fout the output filestream
	 */
	virtual void write(ofstream &fout) const = 0;

protected:

	string address;
	string name;
	double balance;

	int numApps;
	vector<App*> publishedApps;
	hashDeveloper removedApps;
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

#endif /* __DEVELOPER_H_ */
