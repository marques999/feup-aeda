/*!
 * \file App.h
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

#ifndef APP_H_
#define APP_H_

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
	App() 
	{
	}

	/**
	 * @brief constructor with parameters for 'App' class
	 * @param n app name
	 * @param p app price
	 * @param c app category (games, produtividade, multimédia, web, etc...)
	 * @param d app description
	 */
	App(string n, double p, string c, string d) : 
		name(n), price(p), category(c), description(d) 
	{
		dev = NULL;
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
	 * @param newName the new app name
	 */
	void setName(string newName) {
		this->name = newName;
	}

	/**
	 * @brief returns the current app price
	 */
	double getPrice() const {
		return this->price;
	}

	/**
	 * @brief sets the app with a new price
	 * @param newPrice the new price for the app
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
	 * @param newCategory the new category for the app
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
	 * @param timeinfo a time struct containing the new date
	 */
	void setDate(struct tm timeinfo) {
		this->date = timeinfo;
	}

	/**
	 * @brief returns a time struct for the publish date
	 */
	struct tm getDate() const {
		return date;
	}

	/**
	* @brief sets the app with a new description
	* @param newDescription string containing the new description
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
	 * @brief returns the app developer
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
	 * @brief returns the ratings given by customers
	 */
	Rating getRating() const {
		return this->rating;
	}

	/**
	 * @brief compares two apps by name
	 * @param ap the second comparable term
	 */
	bool operator==(const App &ap) const;

	/**
	 * @brief rates the application
	 * @param r the rating given by the customer
	 */
	void classificar(unsigned r);

	/**
	 * @brief writes a new comment
	 * @param cli the customer name
	 * @param c the comment written by the customer
	 */
	bool comentar(string cli, string c);

	/**
	 * @brief reads comments and ratings from a given file
	 * @param fin the input filestream
	 */
	void read(ifstream &fin);

	/**
	 * @brief writes comments and ratings to a given file
	 * @param fout the output filestream
	 */
	void write(ofstream &fout) const;

private:

	string name;
	double price;
	string category;
	struct tm date;
	string description;
	Developer* dev;
	Rating rating;
	vector<Comentario> comments;
};

#endif
