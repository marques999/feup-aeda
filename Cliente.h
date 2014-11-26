/*!
* \file Cliente.h
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

#ifndef CLIENTE_H
#define CLIENTE_H

#include "Common.h"
#include "UI.h"

class App;

class Cliente
{
public:

	/**
	* @brief default constructor for 'Cliente' class
	* @param n the customer's name
	* @param s initial account balance (may add some funds later)
	*/
	Cliente(string n, double s);

	/**
	* @brief default destructor for 'Cliente' class
	*/
	virtual ~Cliente() {
	}

	/**
	* @brief returns the customer's name
	*/
	string getName() const {
		return this->name;
	}

	/**
	* @brief sets the customer with a new name
	*/
	void setName(string n) {
		this->name = n;
	}

	/**
	* @brief reurns the customer's account balance
	*/
	double getSaldo() const {
		return this->saldo;
	}

	/**
	* @brief sets the customer's account balance to s
	*/
	void setSaldo(double s) {
		this->saldo = s;
	}

	/**
	* @brief returns true if customer owns a voucher, otherwise false
	*/
	bool getVoucher() const {
		return this->voucher;
	}

	/**
	* @brief sets new status for voucher
	* @param v new status (true/false)
	*/
	void setVoucher(bool v) {
		this->voucher = v;
	}

	/**
	* @brief returns number of apps bought by the customer
	*/
	unsigned int getNumApps() const {
		return owned.size();
	}

	/**
	* @brief returns a vector containing all the apps owned by the customer
	*/
	vector<App> getOwnedApps() const {
		return owned;
	}

	/**
	* @brief pushes an app purchased by the customer to its "collection"
	* @param a the recently bought app
	*/
	void own(const App &a) {
		owned.push_back(a);
	}

private:

	string name;
	double saldo;
	bool voucher;
	vector<App> owned;
};

#endif
