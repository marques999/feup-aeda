/*!
 * \file AppStore.h
 *
 * FEUP_AEDA1415_2MIEIC03_D
 * \author Carlos Soares
 * \author Diogo Marques
 * \author Fabio Carneiro
 *
 * \date Dezembro 2014
 *
 */

#ifndef __APPSTORE_H_
#define __APPSTORE_H_

#include <queue>

#include "BST.h"
#include "Sale.h"
#include "Developer.h"

typedef enum  {
	APP_NAME, APP_DATE, APP_PRICE, APP_RATING, APP_SALES
} AppSort;

typedef enum {
	CLIENTE_NAME, CLIENTE_APPS, CLIENTE_SALDO
} ClienteSort;

typedef enum {
	DEV_NAME, DEV_APPS, DEV_SALES
} DeveloperSort;

typedef enum {
	SALES_CLIENTE, SALES_PRICE, SALES_APPS
} SaleSort;

struct sortQueue
{
	bool operator()(App* &lhs, App* &rhs) const
	{
		if (lhs->getDate() == rhs->getDate())
		{
			if (lhs->getPrice() == rhs->getPrice())
			{
				return !(lhs->getName() < rhs->getName());
			}
			return !(lhs->getPrice() < rhs->getPrice());
		}
		return (lhs->getDate() < rhs->getDate());
	}
};

typedef priority_queue<App*,vector<App*>,sortQueue> queuePending;

class AppStore
{
public:

	AppStore();
	AppStore(string n);

	virtual ~AppStore();

	////////////////////////////////////////////////////////
	// CUTE tests related								  //
	unsigned int getNumAppsTotal() const;				  //
	unsigned int getNumClientes() const;				  //
	unsigned int getNumDevelopers() const;				  //
	unsigned int getNumAppsDev(Developer* dev) const;	  //
	vector<App*> getAppsFromDev(Developer* dev) const;    //
	string getName() const;								  //
	vector<App*> getApps() const;						  //
	////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////
	//					   APP C/R/U/D					  //
	////////////////////////////////////////////////////////
	bool createApp(int devIndex);
	bool deleteApp(int devIndex);
	bool deletePendingApp(int devIndex);
	void publishRemovedApp(int devIndex);
	bool updateApp(int devIndex);
	bool updatePendingApp(int devIndex);
	bool updateRemovedApp(int devIndex);
	void updateApp(App* app);

	////////////////////////////////////////////////////////
	//					 CLIENTE C/R/U/D				  //
	////////////////////////////////////////////////////////
	bool createCliente();
	bool deleteCliente();
	bool updateCliente();

	////////////////////////////////////////////////////////
	//			    	DEVELOPER C/R/U/D				  //
	////////////////////////////////////////////////////////
	bool createDeveloper();
	bool deleteDeveloper();
	bool updateDeveloper();

	int indexCliente(string cliName);
	int indexDeveloper(string devName) const;

	////////////////////////////////////////////////////////
	//			       		GUI: TABLES			 		  //
	////////////////////////////////////////////////////////
	void GUIAppsTable(const vector<App> &v) const;
	void GUIAppsTable(const vector<App*> &v) const;
	void GUIAppsTable2(const vector<App*> &v) const;
	void GUIClienteTable(const vector<Cliente*> &v) const;
	void GUIDeveloperAppsTable(const vector<App*> &v) const;
	void GUIDeveloperTable(const vector<Developer*> &v) const;
	void GUIDeveloperTable2(const vector<Developer*> &v) const;
	void GUISalesTable(const vector<Sale> &s) const;

	////////////////////////////////////////////////////////
	//			       GUI: INFORMATION BARS			  //
	////////////////////////////////////////////////////////
	void GUIAdminBar() const;
	void GUIDeveloperBar(int devIndex) const;
	void GUIClienteBar(int cliIndex) const;

	////////////////////////////////////////////////////////
	//			       GUI: CRUD OPERATIONS				  //
	////////////////////////////////////////////////////////
	void GUIAppCRUD();
	void GUIClienteCRUD();
	void GUIDeveloperCRUD();

	////////////////////////////////////////////////////////
	//			       GUI: OTHER METHODS				  //
	////////////////////////////////////////////////////////
	void GUIAddFunds(int cliIndex);
	void GUIAddToCart(int appIndex, int cliIndex);
	void GUIActivateVoucher(int cliIndex);
	void GUIBrowseApps(int cliIndex);
	void GUICheckoutCart(int cliIndex);
	void GUIFreeVoucher();
	void GUIPendingApps(int devIndex);
	void GUIRateApp(int appIndex);
	void GUIRemovedApps(int devIndex);
	void GUISearchCategory() const;
	void GUISearchDeveloper() const;
	void GUISearchPrice() const;
	void GUISearchRating() const;
	bool GUIRemoveFromCart();

	// APP

	int appIndex(string appName) const;

	void GUIListApps() const;
	void GUIListPending() const;
	void GUIListPublished(int devIndex) const;
	void GUIPendingMenu();
	void GUIDeveloperPending(int devIndex);

	void App_comment(int appIndex, int cliIndex);

	void App_print(int appIndex, int cliIndex);
	void App_checkout(int cliIndex, bool voucher);

	// Binary search tree

	BST<App*> BSTGetApps() const;
	bool BSTInsertApp(App* a);
	bool BSTRemoveApp(App* a);
	bool BSTRemoveApp(string appName);
	App* queueFindElement(string name) const;


	// IO

	void IOReadApps();
	bool IOReadApp(ifstream &fin);
	void IOReadRemovedApps();
	bool IOReadRemovedApp(ifstream &fin);
	void IOWriteApps() const;
	void IOWriteRemovedApps() const;

	void IOReadClientes();
	void IOWriteClientes() const;
	bool IOReadDeveloper(ifstream &fin);
	void IOReadDevelopers();
	void IOWriteDeveloper(Developer* dev, ofstream &fout) const;
	void IOWriteDevelopers() const;

	void IOReadSales();
	void IOWriteSale(const Sale &s, ofstream& fout) const;
	void IOWriteSales() const;
	bool IOReadStore();
	bool IOWriteStore() const;
	
	void IOReadSale(ifstream &fin);

	// MENU

	void GUIAdminMenu();
	void GUIDeveloperMenu(int devIndex);
	bool GUIClienteMenu(int cliIndex);


	void GUIListSales() const;
	

	////////////////////////////////////////////////////////
	//					     LIST APPS					  //
	////////////////////////////////////////////////////////
	void listAppsByName() const;
	void listAppsByCategory(string cat) const;
	void listAppsByCliente(int cliIndex) const;
	void listAppsByDate() const;
	void listAppsByPrice() const;
	void listAppsByPrice(double min, double max) const;
	void listAppsByRating() const;
	void listAppsByRating(unsigned value) const;
	void listAppsBySales() const;

	////////////////////////////////////////////////////////
	//				   LIST PENDING APPS				  //
	////////////////////////////////////////////////////////
	void listAppsPending() const;
	void listAppsPendingByName() const;


	////////////////////////////////////////////////////////
	//			    	  LIST CLIENTES					  //
	////////////////////////////////////////////////////////
	void listClientesByName() const;
	void listClientesBySaldo() const;
	void listClientesByApps() const;

	////////////////////////////////////////////////////////
	//			      LIST APPS BY DEVELOPER			  //
	////////////////////////////////////////////////////////
	vector<App*> listDeveloperApps(const Developer* dev) const;
	void listDeveloperAppsByDate(const Developer* dev) const;
	void listDeveloperAppsByName(const Developer* dev) const;
	void listDeveloperAppsByPrice(const Developer* dev) const;
	void listDeveloperAppsBySales(const Developer* dev) const;

	////////////////////////////////////////////////////////
	//			         LIST DEVELOPERS				  //
	////////////////////////////////////////////////////////
	void listDevelopersByName() const;
	void listDevelopersByApps() const;
	void listDevelopersBySales() const;

	////////////////////////////////////////////////////////
	//			      	   LIST COMMENTS				  //
	////////////////////////////////////////////////////////
	void listComments(int appIndex) const;

	////////////////////////////////////////////////////////
	//			     LIST PENDING APPS BY DEVELOPER		  //
	////////////////////////////////////////////////////////
	vector<App*> listDeveloperPending(const Developer* dev) const;
	void listDeveloperPendingByName(const Developer* dev) const;
	void listDeveloperPendingByPrice(const Developer* dev) const;
	void listDeveloperPendingByPriority(const Developer* dev) const;

	////////////////////////////////////////////////////////
	//			    	 LIST PENDING APPS	        	  //
	////////////////////////////////////////////////////////
	void listPendingByName() const;
	void listPendingByDate() const;
	void listPendingByPrice() const;
	void listPendingByPriority() const;

	////////////////////////////////////////////////////////
	//			     	 LIST REMOVED APPS     			  //
	////////////////////////////////////////////////////////
	vector<App> listDeveloperRemoved(int devIndex) const;
	void listRemovedByName(int devIndex) const;
	void listRemovedByPrice(int devIndex) const;
	void listRemovedBySales(int devIndex) const;

	////////////////////////////////////////////////////////
	//			 		     LIST SALES					  //
	////////////////////////////////////////////////////////
	void listSalesByApps() const;
	void listSalesByCliente() const;
	void listSalesByCliente(int cliIndex) const;
	void listSalesByID() const;
	void listSalesByPrice() const;


	void listTopNApps(int topN) const;
	void listTop10Apps() const;

	void freeVoucher();

private:

	vector<App> sortApps(const vector<App> &v, AppSort s) const;
	vector<App*> sortApps(const vector<App*> &v, AppSort s) const;
	vector<Cliente*> sortClientes(vector<Cliente*> v, ClienteSort s) const;
	vector<Developer*> sortDevelopers(const vector<Developer*> &v, DeveloperSort s) const;
	vector<Sale> sortSales(const vector<Sale> v, SaleSort s) const;

	vector<App*> queueToVector() const;
	App* queueFindElement(string name, int devIndex) const;
	bool queueRemoveElement(App* elem);
	void queueInsertElement(App* elem);
	bool queueRemoveElement(string name);
	void queueUpdateElement(App* o, App* n);

	void resetCart();

	string nome;
	Sale cart;

	vector<App*> apps;
	queuePending pending;
	BST<App*> appsRanking;

	vector<Cliente*> clientes;
	vector<Developer*> developers;
	vector<Sale> vendas;

};


#endif /* APPSTORE_H_ */
