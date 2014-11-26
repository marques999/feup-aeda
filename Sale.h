/*!
 * \file Sale.h
 *
 * FEUP_AEDA1415_2MIEIC03_D
 * \author Carlos Soares
 * \author Diogo Marques
 * \author Fabio Carneiro
 *
 * \date Novembro 2014
 *
 */

#ifndef SALE_H_
#define SALE_H

#include "App.h"

class Cliente;
class App;

class Sale {
private:

	Cliente* client;
	vector<App> appsBought;
	double price;

public:

	/**
	 * @brief default constructor for 'Sale' class
	 */
	Sale() {
	}

	/**
	 * @brief constructor with parameters for 'Sale' class
	 * @param Buyer a pointer to the customer who made the purchase
	 * @param AppSold a vector containing the apps bought by the customer in a purchase
	 * @param value the amount paid by the customer
	 */
	Sale(Cliente* Buyer, vector<App> AppSold, double value) :
			client(Buyer), appsBought(AppSold), price(value) {
	}

	/**
	 * @brief default destructor for 'Sale' class
	 */
	~Sale() {
	}

	/**
	 * @brief returns a pointer to the customer who made the purchase
	 */
	Cliente* getOwner() const {
		return this->client;
	}

	/**
	 * @brief associates the sale with a new customer
	 * @param newClient a pointer to the new customer
	 */
	void setOwner(Cliente* newClient) {
		this->client = newClient;
	}

	/**
	 * @brief returns the amount to be paid by the customer
	 */
	double getPrice() const {
		return this->price;
	}

	/**
	 * @brief sets the sale with a new amount (for voucher savings)
	 * @param newPrice the new amount
	 */
	void setPrice(double newPrice) {
		this->price = newPrice;
	}

	/**
	 * @brief returns the apps bought by the customer
	 */
	vector<App> getApps() const {
		return this->appsBought;
	}

	/**
	 * @brief adds a new app to the sale (for "add to cart")
	 * @param a the application to be added
	 */
	void pushApp(const App &a);

	/**
	 * @brief removes an app from the sale (for "remove from cart")
	 * @param a the application to be removed
	 */
	void pullApp(const App &a);
};

#endif
