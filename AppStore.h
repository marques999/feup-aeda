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
	APP_NAME, APP_DATE, APP_PRICE, APP_RATING,
} AppSort;

typedef enum {
	CLIENTE_NAME, CLIENTE_APPS, CLIENTE_SALDO,
} ClienteSort;

typedef enum {
	DEV_NAME, DEV_APPS, DEV_SALES,

} DeveloperSort;

typedef enum {
	SALES_CLIENTE, SALES_PRICE, SALES_APPS
} SaleSort;

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
	//					 CLIENTE C/R/U/D				  //
	////////////////////////////////////////////////////////
	bool createCliente();
	bool deleteCliente();
	bool insertCliente(Cliente* c1);
	int indexCliente(string cliName);
	bool updateCliente();

	////////////////////////////////////////////////////////
	//			    	DEVELOPER C/R/U/D				  //
	////////////////////////////////////////////////////////
	bool Developer_create();
	bool Developer_delete();
	int indexDeveloper(string devName) const;
	bool insertDeveloper(Developer* dev);
	bool Developer_update();


	void Cliente_menu();
	void Developer_menu();
	void Cliente_browse(int cliIndex);

	void GUIAppsTable(const vector<App> &v) const;
	void GUIAppsTable(const vector<App*> &v) const;
	void GUIAppsTable2(const vector<App*> &v) const;
	void GUIClienteTable(const vector<Cliente*> &v) const;
	void GUIDeveloperTable(const vector<Developer*> &v) const;
	void GUIDeveloperTable2(const vector<Developer*> &v) const;
	void GUISalesTable(const vector<Sale> &s) const;

	void GUIAdminBar() const;
	void GUIDeveloperBar(int devIndex) const;
	void GUIClienteBar(int cliIndex) const;

	void GUIAddFunds(int cliIndex);
	void GUIAddToCart(int appIndex, int cliIndex);
	void GUIActivateVoucher(int cliIndex);
	void GUICheckoutCart(int cliIndex);
	void GUIFreeVoucher();
	void GUIRateApp(int appIndex);
	void GUISearchCategory() const;
	void GUISearchDeveloper() const;
	void GUISearchPrice() const;
	void GUISearchRating() const;
	bool GUIRemoveFromCart();

	// APP

	bool createApp(int devIndex);
	bool deleteApp(int devIndex);
	bool insertApp(App* app);
	bool updateApp(int devIndex);
	void updateApp(App* app);

	int appIndex(string appName) const;

	void App_list() const;
	void App_menu();
	void App_comment(int appIndex, int cliIndex);
	void publishApp();
	void GUIRemovedApps(int devIndex);
	void publishRemovedApp(int devIndex);
	void App_print(int appIndex, int cliIndex);
	void App_checkout(int cliIndex, bool voucher);

	// Binary search tree

	BST<App*> BSTGetApps() const;
	bool BSTInsertApp(App* a);
	bool BSTRemoveApp(App* a);
	bool BSTRemoveApp(string appName);

	bool updatePendingApp(int devIndex);
	bool deletePendingApp(int devIndex);
	// IO

	void IOReadApps();
	bool IOReadApp(ifstream &fin);
	void IOReadRemovedApps();
	bool IOReadRemovedApp(ifstream &fin);
	void IOWriteApp(App* app, ofstream &fout) const;
	void IOWriteApp(const App &app, ofstream &fout) const;
	void IOWriteApps() const;
	void IOWriteRemovedApps() const;

	void IOReadClientes();
	void IOWriteCliente(Cliente* cli, ofstream &fout) const;
	void IOWriteClientes() const;
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

	void resetCart();

	
	// LIST


	////////////////////////////////////////////////////////
	//			    	  LIST CLIENTES					  //
	////////////////////////////////////////////////////////
	void listClientesByName() const;
	void listClientesBySaldo() const;
	void listClientesByApps() const;

	////////////////////////////////////////////////////////
	//			         LIST DEVELOPERS				  //
	////////////////////////////////////////////////////////
	void listDevelopersByName() const;
	void listDevelopersByApps() const;
	void listDevelopersBySales() const;

	void listComments(int appIndex) const;

	vector<App*> listDeveloperPending(const Developer* dev) const;
	vector<App> listDeveloperRemoved(int devIndex) const;

	void listDevPendingByName(const Developer* dev) const;
	void listDevPendingByPriority(const Developer* dev) const;

	void listPendingByName() const;
	void listPendingByPriority() const;

	void listRemovedByName(int devIndex) const;
	void listRemovedByPrice(int devIndex) const;

	void listSalesByApps() const;
	void listSalesByCliente() const;
	void listSalesByCliente(int cliIndex) const;
	void listSalesByID() const;
	void listSalesByPrice() const;

	void listAppsByName() const;
	void listAppsByCategory(string cat) const;
	void listAppsByCliente(int cliIndex) const;
	void listAppsByDateAscending() const;
	void listAppsByDateDescending() const;
	void listAppsByDeveloper(const Developer* dev) const;
	void listAppsByPrice() const;
	void listAppsByPrice(double min, double max) const;
	void listAppsByRating() const;
	void listAppsByRating(unsigned value) const;
	void listAppsPending() const;
	void listAppsPendingByName() const;

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

//	bool tableInsertElement(const App &elem);
//	bool tableRemoveElement(const App& elem);
//	bool tableUpdateElement(const App& o, const App &n);

	string nome;
	Sale cart;

	vector<App*> apps;
	priority_queue<App*> appsPendentes;
	BST<App*> appsRanking;

	vector<Cliente*> clientes;
	vector<Developer*> developers;
	vector<Sale> vendas;

};


#endif /* APPSTORE_H_ */
