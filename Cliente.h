/*!
 * \file Cliente.h
 *
 * FEUP_AEDA1415_2MIEIC03_D
 * \author Carlos Soares
 * \author Diogo Marques
 * \author Fabio Carneiro
 *
 * \date Janeiro 2015
 *
 */

#ifndef __CLIENTE_H_
#define __CLIENTE_H_

#include "Common.h"
#include "UI.h"

class App;

class Cliente
{
public:

	/**
	* @brief default constructor for 'Cliente' class
	* @param n customer's name
	* @param s initial account balance (may add some funds later)
	*/
	Cliente(string n, double s)
	{
		this->name = n;
		this->saldo = s;
		this->voucher = false;
	}

	/**
	* @brief default destructor for 'Cliente' class
	*/
	virtual ~Cliente()
	{
	}

	/**
	* @brief returns the customer's name
	*/
	string getName() const
	{
		return this->name;
	}

	/**
	* @brief sets the customer with a new name
	* @param n string containing the new customer name
	*/
	void setName(string n)
	{
		this->name = n;
	}

	/**
	* @brief returns the customer's account balance
	*/
	double getSaldo() const
	{
		return this->saldo;
	}

	/**
	* @brief sets the customer with a new account balance
	* @param s new customer account balance
	*/
	void setSaldo(double s)
	{
		this->saldo = s;
	}

	/**
	* @brief gets customer's voucher status
	* @return returns true if customer owns a voucher; false otherwise
	*/
	bool getVoucher() const
	{
		return this->voucher;
	}

	/**
	* @brief sets new status for the customer voucher
	* @param v new status for the voucher (must be true OR false)
	*/
	void setVoucher(bool v)
	{
		this->voucher = v;
	}

	/**
	* @brief returns number of applications bought by the customer
	*/
	unsigned int getNumberApps() const
	{
		return owned.size();
	}

	/**
	* @brief returns a vector containing all the applications bought by the customer
	*/
	vector<App*> getOwnedApps() const
	{
		return owned;
	}

	/**
	* @brief pushes an application purchased by the customer to its "collection"
	* @param a recently purchased app
	*/
	void own(App *a)
	{
		owned.push_back(a);
	}

	/**
	 * @brief writes customer information to a given file
	 * @param fout the output file stream
	 */
	void write(ofstream &fout);

private:

	string name;
	double saldo;
	bool voucher;
	vector<App*> owned;
};

#endif /* __CLIENTE_H_ */
