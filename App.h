/*!
 * \file App.h
 *
 * FEUP_AEDA1415_2MIEIC03_D
 * \author Carlos Soares
 * \author Diogo Marques
 * \author Fabio Carneiro
 *
 * \date Janeiro 2015
 *
 */

#ifndef __APP_H_
#define __APP_H_

#include "Cliente.h"
#include "DateTime.h"
#include "Rating.h"

class Developer;

typedef struct {
	string clientName;
	string comment;
} Comentario;

class App
{

public:

	/**
	* @brief default constructor for 'App' class
	*/
	App()
	{
		this->dev = NULL;
		this->price = 0.0;
		this->sales = 0;
	}

	/**
	 * @brief constructor with parameters for 'App' class
	 * @param n app name
	 * @param p app price
	 * @param c app category (games, office, audio, video, internet, etc...)
	 * @param d app description
	 */
	App(string n, double p, string c, string d) : name(n), price(p), category(c), description(d)
	{
		this->dev = NULL;
		this->sales = 0;
	}

	/**
	 * @brief default destructor for 'App' class
	 */
	virtual ~App()
	{
	}

	/**
	 * @brief returns the app name
	 */
	string getName() const
	{
		return this->name;
	}

	/**
	 * @brief sets the application with a new name
	 * @param newName string containing the new application name
	 */
	void setName(const string &newName)
	{
		this->name = newName;
	}

	/**
	 * @brief returns the application price
	 */
	double getPrice() const
	{
		return this->price;
	}

	/**
	 * @brief sets the application with a new price
	 * @param newPrice new application price
	 */
	void setPrice(double newPrice)
	{
		this->price = newPrice;
	}

	/**
	 * @brief returns the application category
	 */
	string getCategory() const
	{
		return this->category;
	}

	/**
	 * @brief sets the application with a new category
	 * @param newCategory string containing the new category for the application
	 */
	void setCategory(const string &newCategory)
	{
		this->category = newCategory;
	}

	/**
	 * @brief returns a Date object containing the publish date
	 */
	Date getDate() const
	{
		return date;
	}

	/**
	 * @brief sets the application with a new publish date
	 * @param d Date object containing the new publish date
	 */
	void setDate(const Date &d)
	{
		this->date = d;
	}

	/**
	* @brief returns the application description
	*/
	string getDescription() const
	{
		return this->description;
	}

	/**
	* @brief sets the application with a new description
	* @param newDescription string containing the new description
	*/
	void setDescription(string newDescription)
	{
		this->description = newDescription;
	}

	/**
	 * @brief returns the developer who published this application
	 */
	Developer* getDeveloper() const
	{
		return this->dev;
	}

	/**
	 * @brief associates the application with a new developer
	 * @param newDev pointer to the new application developer
	 */
	void setDeveloper(Developer* newDev)
	{
		this->dev = newDev;
	}

	/**
	 * @brief returns the number of customers who have purchased this application
	 */
	int getSales() const
	{
		return this->sales;
	}

	/**
	 * @brief sets a new value for the application sales
	 * @param s new sales value
	 */
	void setSales(int s)
	{
		this->sales = s;
	}

	/**
	 * @brief returns a vector containing comments written by customers
	 */
	vector<Comentario> getComments() const
	{
		return this->comments;
	}

	/**
	 * @brief returns an object containing the ratings given by customers
	 */
	Rating getRating() const
	{
		return this->rating;
	}

	/**
	 * @brief compares two applications by name for equality
	 * @param ap right operand
	 * @return returns true if two applications have the same name; false otherwise
	 */
	bool operator==(const App &ap) const
	{
		return name == ap.name;
	}

	/**
	 * @brief compares two applications
	 * @param ap right operand
	 * @return returns true if left operand should appear before right operand; false otherwise
	 */
	bool operator<(const App &ap)
	{
		if (rating == ap.rating)
		{
			if (price == ap.price)
			{
				return (name < ap.name);
			}
			return (price < ap.price);
		}
		return (rating > ap.rating);
	}

	/**
	 * @brief updates application ratings
	 * @param r new rating given by a customer
	 */
	void classificar(unsigned r)
	{
		rating.r.push_back(r);
	}

	/**
	 * @brief writes a new comment
	 * @param cli customer's name
	 * @param c comment written by the customer
	 * @return returns true if comment was added successfully; false otherwise
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
	void sale()
	{
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
	unsigned sales;
	string category;
	Date date;
	string description;
	Developer* dev;
	Rating rating;
	vector<Comentario> comments;
};

#endif
