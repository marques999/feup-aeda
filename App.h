/*!
 * \file App.h
 *
 * FEUP_AEDA1415_2MIEIC03_D
 * \author Carlos Soares
 * \author Diogo Marques
 * \author Fabio Carneiro
 *
 * \date Dezembro 2014
 *
 */

#ifndef __APP_H_
#define __APP_H_

#include "Cliente.h"
#include "Rating.h"

class Developer;

typedef struct {
	string clientName;
	string comment;
} Comentario;

class App {
public:

	/**
	* @brief default constructor for 'App' class
	*/
	App() {
		this->dev = NULL;
		this->price = 0.0;
		this->sales = 0;
	}

	/**
	 * @brief constructor with parameters for 'App' class
	 * @param n app name
	 * @param p app price
	 * @param c app category (games, produtividade, multimédia, web, etc...)
	 * @param d app description
	 */
	App(string n, double p, string c, string d) : name(n), price(p), category(c), description(d) {
		this->dev = NULL;
		this->sales = 0;
	}

	/**
	 * @brief default destructor for 'App' class
	 */
	~App() {
	}

	/**
	 * @brief returns the app name
	 */
	string getName() const {
		return this->name;
	}

	/**
	 * @brief sets the app with a new name
	 * @param newName a new app name
	 */
	void setName(string newName) {
		this->name = newName;
	}

	/**
	 * @brief returns the app price
	 */
	double getPrice() const {
		return this->price;
	}

	/**
	 * @brief sets the app with a new price
	 * @param newPrice a new price for the app
	 */
	void setPrice(double newPrice) {
		this->price = newPrice;
	}

	/**
	 * @brief returns the app category
	 */
	string getCategory() const {
		return this->category;
	}

	/**
	 * @brief sets the app with a new category
	 * @param newCategory a new category for the app
	 */
	void setCategory(string newCategory) {
		this->category = newCategory;
	}

	/**
	 * @brief returns a vector containing comments written by customers
	 */
	vector<Comentario> getComments() const {
		return this->comments;
	}

	/**
	 * @brief sets the app with a new publish date
	 * @param timeinfo a data structure containing the new date
	 */
	void setDate(struct tm timeinfo) {
		this->date = timeinfo;
	}

	/**
	 * @brief returns a data structure containing the publish date
	 */
	struct tm getDate() const {
		return date;
	}

	/**
	* @brief sets the app with a new description
	* @param newDescription a string containing the new description
	*/
	void setDescription(string newDescription) {
		this->description = newDescription;
	}

	/**
	* @brief returns the app description
	*/
	string getDescription() const {
		return this->description;
	}

	/**
	 * @brief returns the developer who published this app
	 */
	Developer* getDeveloper() const {
		return this->dev;
	}

	/**
	 * @brief associates the app with a new developer
	 * @param newDev a pointer to the new app developer
	 */
	void setDeveloper(Developer* newDev) {
		this->dev = newDev;
	}

	/**
	 * @brief returns an object containing the ratings given by customers
	 */
	Rating getRating() const {
		return this->rating;
	}

	/**
	 * @brief returns the number of customers who have purchased this app
	 */
	int getSales() const {
		return this->sales;
	}

	/**
	 * @brief sets a new value for the number of app sales
	 * @param s the updated value
	 */
	void setSales(int s) {
		this->sales = s;
	}

	/**
	 * @brief compares two apps by name
	 * @param ap the second comparable term
	 */
	bool operator==(const App &ap) const {
		return name == ap.name;
	}

	/**
	 * @brief updates the application rating
	 * @param r the rating given by the customer
	 */
	void classificar(unsigned r) {
		rating.r.push_back(r);
	}

	/**
	 * @brief writes a new comment
	 * @param cli the customer's name
	 * @param c the comment left by the customer
	 */
	bool comentar(string cli, string c);

	/**
	 * @brief reads comments and ratings from a given file
	 * @param fin the input filestream
	 */
	void read(ifstream &fin);

	/**
	 * @brief increments the amount of times this app has been purchased
	 */
	void sale() {
		this->sales++;
	}

	/**
	 * @brief writes comments and ratings to a given file
	 * @param fout the output filestream
	 */
	void write(ofstream &fout) const;

private:

	string name;
	double price;
	int sales;
	string category;
	struct tm date;
	string description;
	Developer* dev;
	Rating rating;
	vector<Comentario> comments;
};

#endif
