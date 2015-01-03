/*!
 * \file Sale.h
 *
 * FEUP_AEDA1415_2MIEIC03_D
 * \author Carlos Soares
 * \author Diogo Marques
 * \author Fabio Carneiro
 *
 * \date Janeiro 2015
 *
 */

#ifndef SALE_H_
#define SALE_H

#include "App.h"

class Cliente;
class App;

class Sale
{

public:

	/**
	 * @brief default constructor for 'Sale' class
	 */
	Sale() : client(NULL), price(0.0)
	{
	}

	/**
	 * @brief constructor with parameters for 'Sale' class
	 * @param Buyer pointer to the customer who made the purchase
	 * @param AppsSold vector containing the apps bought by the customer in a purchase
	 * @param value amount paid by the customer
	 */
	Sale(Cliente* Buyer, vector<App*> AppsSold, double value)
		: client(Buyer), appsBought(AppsSold), price(value)
	{
	}

	/**
	 * @brief default destructor for 'Sale' class
	 */
	~Sale()
	{
	}

	/**
	 * @brief returns a pointer to the customer who made the purchase
	 */
	Cliente* getOwner() const
	{
		return this->client;
	}

	/**
	 * @brief associates the sale with a new customer
	 * @param newClient pointer to a customer
	 */
	void setOwner(Cliente* newClient)
	{
		this->client = newClient;
	}

	/**
	 * @brief returns the amount to be paid by the customer
	 */
	double getPrice() const
	{
		return this->price;
	}

	/**
	 * @brief sets the cart with a new total price (for voucher savings)
	 * @param newPrice new price
	 */
	void setPrice(double newPrice)
	{
		this->price = newPrice;
	}

	/**
	 * @brief returns the apps bought by the customer
	 */
	vector<App*> getApps() const
	{
		return this->appsBought;
	}

	/**
	 * @brief adds a new app to the sale (for "add to cart")
	 * @param a new application to be added
	 */
	bool push(App* a);

	/**
	 * @brief removes an app from the sale (for "remove from cart")
	 * @param a application to be removed
	 */
	bool pull(App* a);

	void write(ofstream &fout) const;

private:

	Cliente* client;
	vector<App*> appsBought;
	double price;
};

#endif
