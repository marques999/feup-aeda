/*!
* \file AppStore.h
*
* FEUP_AEDA1415_2MIEIC03_D
* \author Carlos Soares
* \author Diogo Marques
* \author Fabio Carneiro
*
* \date Novembro 2014
*
*/

#ifndef APPSTORE_H_
#define APPSTORE_H_

#include <queue>
#include "BST.h"

#include "Sale.h"
#include "Developer.h"

typedef enum  {
	APP_NAME, APP_DATE, APP_PRICE, APP_RATING,
	DEV_NAME, DEV_APPS, DEV_SALES,
	CLIENTE_NAME, CLIENTE_APPS, CLIENTE_SALDO,
	SALES_CLIENTE, SALES_PRICE, SALES_APPS
} Criteria;

class AppStore
{
public:

	AppStore();
	AppStore(string n);
	virtual ~AppStore();

	unsigned int getNumAppsDev(Developer* dev) const;

	////////////////////////////////////////////////////////
	// CUTE test related								  //
	bool insertDeveloper(Developer* dev);				  //
	bool insertApp(const App &app);						  //
	unsigned int getNumAppsTotal() const;				  //
	unsigned int getNumClientes() const;				  //
	unsigned int getNumDevelopers() const;				  //
	vector<App> getAppsFromDev(Developer* dev) const;     //
	string getName() const;								  //
	////////////////////////////////////////////////////////

	// DEVELOPER

	bool Developer_create();
	bool Developer_delete();
	int Developer_index(string name) const;
	void Developer_menu();
	void Developer_read();
	void Developer_altTable(const vector<Developer*> &v) const;
	void Developer_table(const vector<Developer*> &v) const;
	bool Developer_update();
	void Developer_write();

	// CLIENTE

	bool Cliente_add(Cliente* c1);
	void Cliente_browse(int cliIndex);
	bool Cliente_create();
	bool Cliente_delete();
	int Cliente_index(string name);
	void Cliente_menu();
	void Cliente_read();
	void Cliente_table(const vector<Cliente*> &c) const;
	bool Cliente_update();
	void Cliente_write() const;

	// APP

	bool App_create(int devIndex);
	void App_checkout(int cliIndex, bool voucher);
	bool App_delete(int devIndex);
	void App_comment(int appIndex, int cliIndex);
	int App_index(string name) const;
	void App_list() const;
	void App_menu();
	void App_publish();
	void App_print(int appIndex, int cliIndex);
	void App_read();
	void App_rate(int appIndex);
	void App_table(const vector<App> &a) const;
	bool App_update(int devIndex);
	void App_write() const;

	// IO

	bool read();
	bool write();
	
	void resetCart();

	// MENU

	void Main_admin();
	void Main_developer(int devIndex);
	bool Main_user(int cliIndex);


	// SALES
	void Sales_read();
	void Sales_table(const vector<Sale> &s) const;
	void Sales_write() const;
	
	// LIST

	void listDevelopersByName() const;
	void listDevelopersByApps() const;
	void listDevelopersBySales() const;

	void listClientesByName() const;
	void listClientesBySaldo() const;
	void listClientesByApps() const;

	void listPendingByDeveloper(Developer* dev) const;
	void listPendingByPriority() const;

	void listSalesByCliente() const;
	void listSalesByCliente(int cliIndex) const;
	void listSalesByApps() const;
	void listSalesByPrice() const;

	void listAppsByName() const;
	void listAppsByCategory(string cat) const;
	void listAppsByCliente(const Cliente &cli);
	void listAppsByDate(bool ord) const;
	void listAppsByDeveloper(Developer* dev) const;
	void listAppsByPrice() const;
	void listAppsByPrice(double min, double max) const;
	void listAppsByRating() const;
	void listAppsByRating(unsigned value) const;
	void listAppsPending() const;

	void freeVoucher();

private:

	vector<App> sortApps(const vector<App> v, Criteria s) const;
	vector<Cliente*> sortClients(vector<Cliente*> v, Criteria s) const;
	vector<Developer*> sortDevelopers(const vector<Developer*> &v, Criteria s) const;
	vector<Sale> sortSales(const vector<Sale> v, Criteria s) const;

	string nome;
	Sale cart;
	vector<App> apps;
	vector<Cliente*> clientes;
	vector<Developer*> developers;
	vector<Sale> vendas;
	priority_queue<App> appsPendentes;
};

template<class Comparable>
vector<Comparable> queueToVector(const priority_queue<Comparable> &q) {
	priority_queue<Comparable> tempQueue;
	vector<Comparable> tempVector(tempQueue.size());
	for (size_t i = 0; i < tempVector.size(); i++) {
		tempVector[i] = tempQueue.top();
		tempQueue.pop();
	}
	return tempVector;
}

template<class Comparable>
bool queueRemoveElement(priority_queue<Comparable>& q, const Comparable &elem) {
	priority_queue<Comparable> tempQueue;
	if (q.empty()) {
		return false;
	}
	while (!q.empty()) {
		if (q.top() == elem) {
			break;
		}
		tempQueue.push(q.top());
		q.pop();
	}
	while (!tempQueue.empty()) {
		q.push(tempQueue.top());
		tempQueue.pop();
	}
	return true;
}

template<class Comparable>
bool queueInsertElement(priority_queue<Comparable> &q, const Comparable &elem) {
	q.push(elem);
}

template<class Comparable>
bool queueUpdateElement(priority_queue<Comparable> &q, const Comparable &o, const Comparable &n) {
	queueRemoveElement(q, o);
	queueInsertElement(q, n);
}

#endif /* APPSTORE_H_ */
