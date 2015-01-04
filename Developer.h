/*!
 * \file Developer.h
 *
 * FEUP_AEDA1415_2MIEIC03_D
 * \author Carlos Soares
 * \author Diogo Marques
 * \author Fabio Carneiro
 *
 * \date Janeiro 2015
 *
 */

#ifndef __DEVELOPER_H_
#define __DEVELOPER_H_

#include <tr1/unordered_set>

#include "App.h"

#define APP_NOT_FOUND App("", 0, "", "")

typedef enum {
	DEVELOPER_INDIVIDUAL, DEVELOPER_EMPRESA
} DevType;

struct developerH
{
	int operator()(const App& lhs) const
	{
		int appHash = 0;
		string appName = lhs.getName();

		for ( size_t i = 0; i < appName.size() ; i++ )
		{
			appHash = 37*appHash + appName[i];
		}

		return appHash;
	}

	bool operator()(const App &lhs, const App &rhs) const
	{
		return lhs.getName() == rhs.getName();
	}
};

typedef tr1::unordered_set<App, developerH, developerH> hashDeveloper;

class Developer
{

public:

	/**
	 * @brief default constructor for 'Developer' abstract class
	 */
	Developer()
	{
		this->balance = 0.0;
		this->numApps = 0;
		this->numRemovedApps = 0;
	}

	/**
	 * @brief constructor with parameters for 'Developer' abstract class
	 * @param n customer's name / company official name
	 * @param a customer's address / company address
	 */
	Developer(string n, string a)
	{
		this->name = n;
		this->address = a;
		this->balance = 0.0;
		this->numApps = 0;
		this->numRemovedApps = 0;
	}

	/**
	 * @brief default destructor for 'Developer' class
	 */
	virtual ~Developer()
	{
	}

	/**
	 * @brief returns the developer's name
	 */
	string getName() const
	{
		return this->name;
	}

	/**
	 * @brief sets the developer with a new name
	 * @param n new company/developer name
	 */
	void setName(string n)
	{
		this->name = n;
	}

	/**
	 * @brief returns the developer's address
	 */
	string getAddress() const
	{
		return this->address;
	}

	/**
	 * @brief sets the developer with a new address
	 * @param new company/developer address
	 */
	void setAddress(string a)
	{
		this->address = a;
	}

	/**
	 * @brief returns the developer's current balance
	 */
	double getBalance() const
	{
		return this->balance;
	}

	/**
	 * @brief sets the developer with a new balance
	 * @param n new developer balance
	 */
	void setBalance(double n)
	{
		this->balance = n;
	}

	/**
	 * @brief returns the number of apps published by the developer
	 */
	unsigned getNumberApps() const
	{
		return numApps;
	}

	/**
	 * @brief sets the developer with a new number of apps
	 * @param n new number of apps developed
	 */
	void setNumberApps(unsigned n)
	{
		this->numApps = n;
	}

	/**
	 * @brief returns the removed apps table from the developer
	 */
	hashDeveloper getRemovedApps() const
	{
		return removedApps;
	}

	/**
	 * @brief returns the size of the removed apps table
	 */
	unsigned getNumberRemovedApps() const
	{
		return numRemovedApps;
	}

	/**
	 * @brief sets the developer with a new number of removed apps
	 * @param n new number of apps removed from the App Store
	 * @warning should be equal to the hash table size!
	 */
	void setNumberRemovedApps(unsigned n)
	{
		this->numRemovedApps = n;
	}

	/**
	 * @brief increments the number of apps associated with this developer by one
	 * @return returns a constant reference to 'this' object
	 */
	const Developer& operator++()
	{
		numApps++;
		return *this;
	}

	/**
	 * @brief decrements the number of apps associated with this developer by one
	 * @return returns a const reference to 'this' object
	 */
	const Developer& operator--()
	{
		numApps--;
		return *this;
	}

	/**
	 * @brief returns the developer type (individual/company)
	 */
	virtual DevType getType() const = 0;

	/**
	 * @brief inserts a new app into the removed apps table
	 * @param app const reference to the new app
	 */
	bool push(const App &app)
	{
		pair<hashDeveloper::iterator, bool> r = removedApps.insert(app);

		return r.second;
	}

	/**
	 * @brief removes an existing app from the removed apps table
	 * @param app const reference to the app to be removed
	 */
	bool pop(const App& app)
	{
		hashDeveloper::iterator it = removedApps.find(app);

		if (it != removedApps.end())
		{
			removedApps.erase(it);
			return true;
		}

		return false;
	}

	/**
	 * @brief finds an app removed by the developer given its name
	 * @param name application name
	 * @return returns an App object if application was found; otherwise returns an empty object
	 */
	App find(string name)
	{
		hashDeveloper::const_iterator it = removedApps.begin();

		for (; it != removedApps.end(); it++)
		{
			if (it->getName() == name)
			{
				return *it;
			}
		}

		return APP_NOT_FOUND;
	}

	/**
	 * @brief prints the developer information in a user-friendly way
	 */
	virtual void print() const = 0;

	/**
	 * @brief accumulates sales
	 * @param amount transaction amount
	 */
	void sale(double amount)
	{
		balance += amount * 0.8;
	}

	/**
	 * @brief writes developer information to a given file
	 * @param fout the output file stream
	 */
	virtual void write(ofstream &fout) const = 0;

protected:

	string address;
	string name;
	double balance;

	int numApps;
	int numRemovedApps;

	hashDeveloper removedApps;
};

class Developer_Individual: public Developer
{

public:

	/**
	 * @brief default constructor for 'Developer_Individual' class
	 */
	Developer_Individual()
	{
	}

	/**
	 * @brief constructor with parameters for 'Developer_Individual' class (same as 'Developer')
	 * @param n customer's name
	 * @param a customer's address
	 */
	Developer_Individual(string n, string a) : Developer(n, a)
	{
	}

	/**
	 * @brief default destructor for 'Developer_Individual' class
	 */
	~Developer_Individual()
	{
	}

	/**
	 * @brief returns the developer type (DEVELOPER_INDIVIDUAL)
	 */
	DevType getType() const
	{
		return DEVELOPER_INDIVIDUAL;
	}

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

class Developer_Empresa: public Developer
{

public:

	/**
	 * @brief default constructor for 'Developer_Empresa' class
	 */
	Developer_Empresa() : NIF(0)
	{
	}

	/**
	 * @brief constructor with parameters for 'Developer_Empresa' class
	 * @param n company name
	 * @param a company address
	 * @param id company tax ID number
	 */
	Developer_Empresa(string n, string a, unsigned id) : Developer(n, a)
	{
		ostringstream os;
		os << id;
		if (os.str().length() != 9)
		{
			throw InvalidParameter("NIF");
		}
		this->NIF = id;
	}

	/**
	 * @brief default destructor for 'Developer_Empresa' class
	 */
	~Developer_Empresa()
	{
	}

	/**
	 * @brief returns the company tax ID number (9 digits)
	 */
	unsigned getNIF() const
	{
		return this->NIF;
	}

	/**
	 * @brief changes the company tax number
	 * @param id new company tax ID
	 */
	void setNIF(unsigned id)
	{
		this->NIF = id;
	}

	/**
	 * @brief returns the developer type (DEVELOPER_EMPRESA)
	 */
	DevType getType() const
	{
		return DEVELOPER_EMPRESA;
	}

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
