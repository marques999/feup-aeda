/*!
 * \file AppStore.cpp
 *
 * FEUP_AEDA1415_2MIEIC03_D
 * \author Carlos Soares
 * \author Diogo Marques
 * \author Fabio Carneiro
 *
 * \date Novembro 2014
 *
 */

#include "AppStore.h"
#include "DateTime.h"

#include <algorithm>
#include <climits>
#include <fstream>

AppStore::AppStore() {
	resetCart();
}

AppStore::~AppStore() {
}

AppStore::AppStore(string n) :
nome(n) {
	resetCart();
}

void AppStore::resetCart() {
	cart = Sale();
	cart.setPrice(0.0);
	cart.setOwner(NULL);
}

unsigned int AppStore::getNumAppsDev(Developer* dev) const {
	return getAppsFromDev(dev).size();
}

unsigned int AppStore::getNumAppsTotal() const {
	return apps.size();
}

unsigned int AppStore::getNumClientes() const {
	return clientes.size();
}

unsigned int AppStore::getNumDevelopers() const {
	return developers.size();
}

vector<App> AppStore::getAppsFromDev(Developer *dev) const
{
	vector<App> devApps;
	for (vector<App>::const_iterator it = apps.begin(); it != apps.end();
		it++) {
		if ((*it).getDeveloper()->getName() == dev->getName()) {
			devApps.push_back((*it));
		}
	}
	return devApps;
}

string AppStore::getName() const {
	return nome;
}

bool AppStore::read() {
	ifstream fin;
	fin.open("Developers.bin");
	if (!fin.is_open()) {
		fin.close();
		ofstream fout;
		fout.open("Apps.bin");
		fout.close();
		fout.open("Clientes.bin");
		fout.close();
		fout.open("Developers.bin");
		fout.close();
		fout.open("Vendas.bin");
		fout.close();
	}
	fin.close();
	Developer_read();
	App_read();
	Cliente_read();
	Sales_read();
	return true;
}

bool AppStore::write()
{
	Sales_write();
	Cliente_write();
	App_write();
	Developer_write();
	return true;
}

void AppStore::Developer_menu()
{
	int userChoice;
	string tempStr;
	while (true) {
		try {
			system("cls");
			UI::DisplayFrame("DEVELOPER C/R/U/D");
			UI::DisplayMenuTop();
			UI::DisplayMenuItem(1, "Create developer");
			UI::DisplayMenuItem(2, "Update developer");
			UI::DisplayMenuItem(3, "Delete developer");
			UI::DisplayMenuTop();
			UI::DisplayMenuItem(4, "List developers by name");
			UI::DisplayMenuItem(5, "List developers by sales");
			UI::DisplayMenuItem(6, "List developers by apps");
			UI::DisplayMenuBottom();
			cout << "Please select an option: ";
			getline(cin, tempStr);
			userChoice = atoi(tempStr.c_str());
			if (userChoice < 0 || userChoice > 6) {
				throw InvalidParameter("choice");
			}
			switch (userChoice) {
			case 1:
				Developer_create();
				system("pause");
				Developer_write();
				break;
			case 2:
				Developer_update();
				system("pause");
				Developer_write();
				break;
			case 3:
				Developer_delete();
				system("pause");
				Developer_write();
				break;
			case 4:
				system("cls");
				UI::DisplayFrame("DEVELOPERS BY NAME");
				listDevelopersByName();
				system("pause");
				break;
			case 5:
				system("cls");
				UI::DisplayFrame("DEVELOPERS BY SALES");
				listDevelopersBySales();
				system("pause");
				break;
			case 6:
				system("cls");
				UI::DisplayFrame("DEVELOPERS BY NUMBER OF APPS");
				listDevelopersByApps();
				system("pause");
				break;
			case 0:
				return;
			}
		}
		catch (JaExiste &e) {
			cout << "\nERROR: developer " << e.getName()
				<< " already exists.\n";
			system("pause");
		}
		catch (InvalidParameter &ip) {
			cout << "\nERROR: invalid parameter " << ip.what() << "\n";
			system("pause");
		}
		catch (DeveloperInexistente &e) {
			cout << "\nERROR: developer " << e.getName() << " not found.\n";
			system("pause");
		}
	}
}

vector<App> AppStore::sortApps(vector<App> v, Criteria s) const {
	vector<App> sortedVector = v;
	for (size_t i = 1; i < v.size(); i++) {
		App tempApp = sortedVector[i];
		size_t j = 0;
		if (s == APP_NAME) {
			for (j = i; j > 0 && tempApp.getName() < sortedVector[j - 1].getName(); j--) {
				sortedVector[j] = sortedVector[j - 1];
			}
		}
		else if (s == APP_PRICE)
		{
			for (j = i; j > 0 && tempApp.getPrice() < sortedVector[j - 1].getPrice(); j--) {
				sortedVector[j] = sortedVector[j - 1];
			}
		}
		else if (s == APP_RATING)
		{
			for (j = i; j > 0 && tempApp.getRating().get() > sortedVector[j - 1].getRating().get(); j--) {
				sortedVector[j] = sortedVector[j - 1];
			}
		}
		else if (s == APP_DATE)
		{
			for (j = i; j > 0 && tempApp.getDate() < sortedVector[j - 1].getDate(); j--) {
				sortedVector[j] = sortedVector[j - 1];
			}
		}
		sortedVector[j] = tempApp;
	}
	return sortedVector;
}

vector<Cliente*> AppStore::sortClients(vector<Cliente*> v, Criteria s) const {
	vector<Cliente*> sortedVector = v;
	for (size_t i = 1; i < v.size(); i++) {
		Cliente* tempCliente = sortedVector[i];
		size_t j = 0;
		if (s == CLIENTE_NAME) {
			for (j = i;
				j > 0
				&& tempCliente->getName()
				< sortedVector[j - 1]->getName(); j--) {
				sortedVector[j] = sortedVector[j - 1];
			}
		}
		else if (s == CLIENTE_APPS) {
			for (j = i;
				j > 0
				&& tempCliente->getNumApps()
			> sortedVector[j - 1]->getNumApps(); j--)
			{
				sortedVector[j] = sortedVector[j - 1];
			}
		}
		else if (s == CLIENTE_SALDO) {
			for (j = i;
				j > 0
				&& tempCliente->getSaldo()
									> sortedVector[j - 1]->getSaldo(); j--)
			{
				sortedVector[j] = sortedVector[j - 1];
			}
		}
		sortedVector[j] = tempCliente;
	}
	return sortedVector;
}

vector<Sale> AppStore::sortSales(vector<Sale> v, Criteria s) const {
	vector<Sale> sortedVector = v;
	for (size_t i = 1; i < v.size(); i++) {
		Sale tempSale = sortedVector[i];
		size_t j = 0;
		if (s == SALES_CLIENTE) {
			for (j = i;
				j > 0
				&& tempSale.getOwner()->getName()
				< sortedVector[j - 1].getOwner()->getName();
			j--) {
				sortedVector[j] = sortedVector[j - 1];
			}
		}
		else if (s == SALES_PRICE) {
			for (j = i;
				j > 0
				&& tempSale.getPrice()
									> sortedVector[j - 1].getPrice(); j--) {
				sortedVector[j] = sortedVector[j - 1];
			}
		}
		else if (s == SALES_APPS) {
			for (j = i;
				j > 0
				&& tempSale.getApps().size()
									> sortedVector[j - 1].getApps().size();
			j--) {
				sortedVector[j] = sortedVector[j - 1];
			}
		}
		sortedVector[j] = tempSale;
	}
	return sortedVector;
}

vector<Developer*> AppStore::sortDevelopers(const vector<Developer*> &v,
	Criteria s) const {
	vector<Developer*> sortedVector = v;
	for (size_t i = 1; i < v.size(); i++) {
		Developer* tempDev = sortedVector[i];
		size_t j = 0;
		if (s == DEV_NAME) {
			for (j = i;
				j > 0 && tempDev->getName() < sortedVector[j - 1]->getName();
				j--) {
				sortedVector[j] = sortedVector[j - 1];
			}
		}
		else if (s == DEV_APPS) {
			for (j = i;
				j > 0
				&& tempDev->getNumApps()
									> sortedVector[j - 1]->getNumApps(); j--) {
				sortedVector[j] = sortedVector[j - 1];
			}
		}
		else if (s == DEV_SALES) {
			for (j = i;
				j > 0
				&& tempDev->getBalance()
									> sortedVector[j - 1]->getBalance(); j--) {
				sortedVector[j] = sortedVector[j - 1];
			}
		}
		sortedVector[j] = tempDev;
	}
	return sortedVector;
}

/////////////////////////
// LIST&SORT CLIENTES
/////////////////////////

void AppStore::Cliente_table(const vector<Cliente*> &c) const
{
	const int rowCount = 4;
	vector<string> tableLabel = { " Customer name", " No. Apps ", " Balance", " Voucher" };
	int tableLength[rowCount] = { 32, 10, 10, 9 };
	UI::DisplayTable(rowCount, tableLabel, tableLength);
	for (unsigned int i = 0; i < c.size(); i++)
	{
		vector<string> tableRow(rowCount);
		tableRow[0] = c[i]->getName();
		tableRow[1] = UI::Format(c[i]->getNumApps(), 5);
		tableRow[2] = UI::FormatPrice(c[i]->getSaldo());
		tableRow[3] = c[i]->getVoucher() ? "  Yes" : "  No";
		UI::DisplayTableRow(rowCount, tableRow, tableLength);
	}
}

void AppStore::listClientesByName() const
{
	vector<Cliente*> sortedVector = sortClients(clientes, CLIENTE_NAME);
	Cliente_table(sortedVector);
}

void AppStore::listClientesBySaldo() const
{
	vector<Cliente*> sortedVector = sortClients(clientes, CLIENTE_SALDO);
	Cliente_table(sortedVector);
}

void AppStore::listClientesByApps() const
{
	vector<Cliente*> sortedVector = sortClients(clientes, CLIENTE_APPS);
	Cliente_table(sortedVector);
}

///////////////////////////////
// LIST&SORT DEVELOPERS
//////////////////////////////

void AppStore::Developer_table(const vector<Developer*> &v) const {
	const int rowCount = 4;
	vector<string> tableLabel = { " Developer name", " Address", " Type ", " NIF" };
	int tableLength[rowCount] = { 24, 24, 12, 11 };
	UI::DisplayTable(rowCount, tableLabel, tableLength);
	for (vector<Developer*>::const_iterator it = v.begin(); it != v.end(); it++)
	{
		(*it)->print();
	}
}

void AppStore::Developer_altTable(const vector<Developer*> &v) const
{
	const int rowCount = 4;
	vector<string> tableLabel = { " Developer name", " Address", " No. Apps ", " Balance" };
	int tableLength[rowCount] = { 24, 24, 12, 12 };
	UI::DisplayTable(rowCount, tableLabel, tableLength);
	for (vector<Developer*>::const_iterator it = v.begin(); it != v.end(); it++)
	{
		vector<string> tableRow(rowCount);
		tableRow[0] = (*it)->getName();
		tableRow[1] = (*it)->getAddress();
		tableRow[2] = UI::Format((*it)->getNumApps(), 10);
		tableRow[3] = UI::FormatPrice((*it)->getBalance());
		UI::DisplayTableRow(rowCount, tableRow, tableLength);
	}
}

void AppStore::listDevelopersByName() const
{
	vector<Developer*> sortedVector = sortDevelopers(developers, DEV_NAME);
	Developer_table(sortedVector);
}

void AppStore::listDevelopersByApps() const
{
	vector<Developer*> sortedVector = sortDevelopers(developers, DEV_APPS);
	Developer_altTable(sortedVector);
}

void AppStore::listDevelopersBySales() const
{
	vector<Developer*> sortedVector = sortDevelopers(developers, DEV_SALES);
	Developer_altTable(sortedVector);
}

///////////////////////////////
// LIST&SORT QUEUE
//////////////////////////////

void AppStore::listPendingByDeveloper(Developer* dev) const
{
	vector<App> tempVector = queueToVector(appsPendentes);
	vector<App> sortedVector;
	for (size_t i = 0; i < tempVector.size(); i++)
	{
		if (tempVector[i].getDeveloper() == dev)
		{
			sortedVector.push_back(apps[i]);
		}
	}
	App_table(sortedVector);
}

void AppStore::listPendingByPriority() const
{
	vector<App> sortedVector = queueToVector(appsPendentes);
	App_table(sortedVector);
}

///////////////////////////////
// LIST&SORT SALES
//////////////////////////////

void AppStore::Sales_table(const vector<Sale> &s) const {
	const int rowCount = 3;
	vector<string> tableLabel = { " Customer name", " No. Apps ", " Price" };
	int tableLength[rowCount] = { 32, 10, 10 };
	UI::DisplayTable(rowCount, tableLabel, tableLength);
	for (unsigned int i = 0; i < s.size(); i++) {
		vector<string> tableRow(rowCount);
		tableRow[0] = s[i].getOwner()->getName();
		tableRow[1] = UI::Format(s[i].getApps().size(), 5);
		tableRow[2] = UI::FormatPrice(s[i].getPrice());
		UI::DisplayTableRow(rowCount, tableRow, tableLength);
	}
}

void AppStore::listSalesByCliente() const
{
	vector<Sale> sortedVector = sortSales(vendas, SALES_CLIENTE);
	Sales_table(sortedVector);
}

void AppStore::listSalesByCliente(int cliIndex) const
{
	vector<Sale> sortedVector;
	for (size_t i = 0; i < vendas.size(); i++)
	{
		if (vendas[i].getOwner() == clientes[cliIndex])
		{
			sortedVector.push_back(vendas[i]);
		}
	}
	Sales_table(sortedVector);
}

void AppStore::listSalesByApps() const {
	vector<Sale> sortedVector = sortSales(vendas, SALES_APPS);
	Sales_table(sortedVector);
}

void AppStore::listSalesByPrice() const {
	vector<Sale> sortedVector = sortSales(vendas, SALES_PRICE);
	Sales_table(sortedVector);
}

///////////////////////////////
// LIST&SORT APPS
//////////////////////////////

void AppStore::App_table(const vector<App>& v) const {
	const int rowCount = 5;
	vector<string> tableLabel = { " Name", " Developer", " Category", " Price",
		" Rating" };
	int tableLength[rowCount] = { 24, 16, 12, 8, 10 };
	UI::DisplayTable(rowCount, tableLabel, tableLength);
	for (unsigned int i = 0; i < v.size(); i++) {
		vector<string> tableRow(rowCount);
		tableRow[0] = v[i].getName();
		if (v[i].getDeveloper() == NULL) {
			tableRow[1] = "Anonymous";
		}
		else {
			tableRow[1] = v[i].getDeveloper()->getName();
		}
		tableRow[2] = v[i].getCategory();
		if (v[i].getPrice() == 0.0) {
			tableRow[3] = "FREE";
		}
		else {
			tableRow[3] = UI::FormatPrice(v[i].getPrice());
		}
		if (v[i].getRating().get() == 0.0) {
			tableRow[4] = "N/A";
		}
		else {
			tableRow[4] = UI::FormatRating(v[i].getRating().get());
		}
		UI::DisplayTableRow(rowCount, tableRow, tableLength);
	}
}

void AppStore::listAppsByCategory(string cat) const
{
	vector<App> sortedVector;
	for (size_t i = 0; i < apps.size(); i++)
	{
		if (apps[i].getCategory() == cat)
		{
			sortedVector.push_back(apps[i]);
		}
	}
	sortedVector = sortApps(sortedVector, APP_NAME);
	App_table(sortedVector);
}

void AppStore::listAppsByDeveloper(Developer* dev) const
{
	vector<App> sortedVector;
	for (size_t i = 0; i < apps.size(); i++)
	{
		if (apps[i].getDeveloper() == dev)
		{
			sortedVector.push_back(apps[i]);
		}
	}
	sortedVector = sortApps(sortedVector, APP_NAME);
	App_table(sortedVector);
}

void AppStore::listAppsByDate(bool ord) const
{
	vector<App> sortedVector = sortApps(apps, APP_DATE);
	if (ord)
	{
		reverse(sortedVector.begin(), sortedVector.end());
	}
	App_table(sortedVector);
}

void AppStore::listAppsByName() const
{
	vector<App> sortedVector = sortApps(apps, APP_NAME);
	App_table(sortedVector);
}

void AppStore::listAppsByPrice() const
{
	vector<App> sortedVector = sortApps(apps, APP_PRICE);
	App_table(sortedVector);
}

void AppStore::listAppsByPrice(double min, double max) const
{
	vector<App> sortedVector;
	for (size_t i = 0; i < apps.size(); i++)
	{
		if (apps[i].getPrice() >= min && apps[i].getPrice() <= max)
		{
			sortedVector.push_back(apps[i]);
		}
	}
	sortedVector = sortApps(sortedVector, APP_NAME);
	App_table(sortedVector);
}

void AppStore::listAppsByRating() const
{
	vector<App> sortedVector = sortApps(apps, APP_RATING);
	App_table(sortedVector);
}

void AppStore::listAppsByRating(unsigned value) const
{
	vector<App> sortedVector;
	for (size_t i = 0; i < apps.size(); i++)
	{
		if (apps[i].getRating().floor() == value)
		{
			sortedVector.push_back(apps[i]);
		}
	}
	sortedVector = sortApps(sortedVector, APP_NAME);
	App_table(sortedVector);
}

void AppStore::freeVoucher() {
	unsigned int i = (unsigned int)round(clientes.size() * 0.1);
	cout << "\n";
	if (i == 0)
	{
		cout << "\nINFORMATION: not enough customers on the database\n";
	}
	while (i)
	{
		unsigned int j = rand() % clientes.size();
		if (clientes[j]->getVoucher() == false) {
			clientes[j]->setVoucher(true);
			i--;
			cout << "\nINFORMATION: " << clientes[j]->getName()
				<< " has recieved a voucher!\n";
		}
	}
}

bool AppStore::insertApp(const App &app)
{
	if (!sequentialSearch<App>(apps, app))
	{
		apps.push_back(app);
		return true;
	}
	return false;
}

bool AppStore::insertDeveloper(Developer* dev)
{
	if (!sequentialSearch<Developer*>(developers, dev))
	{
		developers.push_back(dev);
		return true;
	}
	return false;
}

bool AppStore::Cliente_add(Cliente* c1)
{
	if (!sequentialSearch<Cliente*>(clientes, c1))
	{
		clientes.push_back(c1);
		return true;
	}
	return false;
}

bool AppStore::Cliente_create()
{
	string tempName;
	string tempStr;
	double tempSaldo = 0.0;

	system("cls");
	UI::DisplayFrame("CREATE CUSTOMER");

	cout << "Please enter the customer's name:";
	getline(cin, tempName);

	if (tempName == "") {
		throw InvalidParameter("name");
	}

	int i = Cliente_index(tempName);
	if (i != -1) {
		throw JaExiste(tempName);
	}

	cout << "Customer's account balance:";
	cin >> tempSaldo;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		throw InvalidParameter("balance");
	}
	if (tempSaldo < 0) {
		cin.ignore(INT_MAX, '\n');
		throw InvalidParameter("balance");
	}

	cin.ignore(INT_MAX, '\n');
	Cliente* tempCliente = new Cliente(tempName, tempSaldo);
	clientes.push_back(tempCliente);
	Cliente_write();

	cout << endl << "INFORMATION: customer created successfully." << endl;
	return true;
}

bool AppStore::Cliente_update() {
	string tempName;
	string tempStr;
	double tempSaldo;
	int i;

	system("cls");
	UI::DisplayFrame("UPDATE CUSTOMER");

	cout << "Please enter the customer's name, <enter> to cancel:" << endl;
	getline(cin, tempName);

	if (tempName == "") {
		return true;
	}

	i = Cliente_index(tempName);
	if (i == -1) {
		throw ClienteInexistente(tempName);
	}

	cout << "New name, <enter> to skip: ";
	getline(cin, tempStr);

	int j = Cliente_index(tempStr);
	if (tempStr != "") {
		if (j != -1) {
			throw JaExiste(tempStr);
		}
		clientes[i]->setName(tempStr);
	}

	cout << "New account balance, (-1) to skip: ";
	cin >> tempSaldo;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		throw InvalidParameter("balance");
	}
	if (tempSaldo >= 0) {
		clientes[i]->setSaldo(tempSaldo);
	}

	cin.ignore(INT_MAX, '\n');
	Cliente_write();
	cout << endl << "INFORMATION: customer information updated." << endl;
	return true;
}

bool AppStore::Cliente_delete() {
	string tempName;

	system("cls");
	UI::DisplayFrame("DELETE CUSTOMER");

	cout << "Please enter the customer's name:" << endl;
	getline(cin, tempName);

	if (tempName == "") {
		throw InvalidParameter("name");
	}

	int i = Cliente_index(tempName);
	if (i == -1) {
		throw ClienteInexistente(tempName);
	}

	clientes.erase(clientes.begin() + i);
	Cliente_write();

	cout << "\nINFORMATION: customer deleted successfully.\n";
	return true;
}

void AppStore::Cliente_menu() {
	int userChoice;
	string tempStr;
	while (true) {
		try {
			system("cls");
			UI::DisplayFrame("CUSTOMER C/R/U/D");
			UI::DisplayMenuTop();
			UI::DisplayMenuItem(1, "Create Customer");
			UI::DisplayMenuItem(2, "Update Customer");
			UI::DisplayMenuItem(3, "Delete Customer");
			UI::DisplayMenuTop();
			UI::DisplayMenuItem(4, "List customers by name");
			UI::DisplayMenuItem(5, "List customers by balance");
			UI::DisplayMenuItem(6, "List customers by no. apps");
			UI::DisplayMenuBottom();
			cout << "Please select an option: ";
			getline(cin, tempStr);
			userChoice = atoi(tempStr.c_str());
			if (userChoice < 0 || userChoice > 6) {
				throw InvalidParameter("choice");
			}
			switch (userChoice) {
			case 1:
				Cliente_create();
				system("pause");
				Cliente_write();
				break;
			case 2:
				Cliente_update();
				system("pause");
				Cliente_write();
				break;
			case 3:
				Cliente_delete();
				system("pause");
				Cliente_write();
				break;
			case 4:
				system("cls");
				UI::DisplayFrame("CUSTOMERS BY NAME");
				listClientesByName();
				system("pause");
				break;
			case 5:
				system("cls");
				UI::DisplayFrame("CUSTOMERS BY BALANCE");
				listClientesBySaldo();
				system("pause");
				break;
			case 6:
				system("cls");
				UI::DisplayFrame("CUSTOMERS BY NUMBER OF APPS");
				listClientesByApps();
				system("pause");
				break;
			case 0:
				return;
			}
		}
		catch (InvalidParameter &ip) {
			cout << "\nERROR: invalid parameter " << ip.what() << "\n";
			system("pause");
		}
		catch (JaExiste &e) {
			cout << "\nERROR: customer " << e.getName() << " already exists.\n";
			system("pause");
		}
		catch (ClienteInexistente &e) {
			cout << "\nERROR: customer " << e.getName() << " not found.\n";
			system("pause");
		}
	}
}

void AppStore::App_list() const {
	int userChoice;
	string tempStr;
	while (true) {
		try {
			system("cls");
			UI::DisplayFrame("LIST APPS");
			UI::DisplayMenuTop();
			UI::DisplayMenuItem(1, "List apps by name");
			UI::DisplayMenuItem(2, "List apps by price");
			UI::DisplayMenuItem(3, "List apps by rating");
			UI::DisplayMenuItem(4, "List apps by date (oldest)");
			UI::DisplayMenuItem(5, "List apps by date (newest)");
			UI::DisplayMenuTop();
			UI::DisplayMenuItem(6, "Search apps by category");
			UI::DisplayMenuItem(7, "Search apps by developer");
			UI::DisplayMenuItem(8, "Search apps by price");
			UI::DisplayMenuItem(9, "Search apps by rating");
			UI::DisplayMenuBottom();
			cout << endl;
			cout << "Please select an option: ";
			getline(cin, tempStr);
			userChoice = atoi(tempStr.c_str());
			if (userChoice < 0 || userChoice > 7) {
				throw InvalidParameter("choice");
			}
			switch (userChoice) {
			case 1: {
				system("cls");
				UI::DisplayFrame("APPS BY NAME");
				listAppsByName();
				system("pause");
				break;
			}
			case 2: {
				system("cls");
				UI::DisplayFrame("APPS BY PRICE");
				listAppsByPrice();
				system("pause");
				break;
			}
			case 3: {
				system("cls");
				UI::DisplayFrame("APPS BY RATING");
				listAppsByRating();
				system("pause");
				break;
			}
			case 4: {
				system("cls");
				UI::DisplayFrame("APPS BY PUBLISH DATE (OLDEST)");
				listAppsByDate(0);
				system("pause");
				break;
			}
			case 5: {
				system("cls");
				UI::DisplayFrame("APPS BY PUBLISH DATE (NEWEST)");
				listAppsByDate(1);
				system("pause");
				break;
			}
			case 6: {
				cout << "\nPlease choose a category: ";
				getline(cin, tempStr);
				if (tempStr == "") {
					throw InvalidParameter("category");
				}

				system("cls");
				UI::DisplayFrame("APPS BY CATEGORY");
				listAppsByCategory(tempStr);
				system("pause");
				break;
			}
			case 7: {
				cout << "\nPlease enter the developer's name: ";
				getline(cin, tempStr);
				if (tempStr == "") {
					throw InvalidParameter("developer");
				}

				int i = Developer_index(tempStr);
				if (i == -1) {
					throw DeveloperInexistente(tempStr);
				}

				system("cls");
				UI::DisplayFrame("APPS BY DEVELOPER");
				listAppsByDeveloper(developers[Developer_index(tempStr)]);
				system("pause");
				break;
			}
			case 8: {
				double minTempPrice;
				cout << "\nPlease enter the lower limit: ";
				if (!(cin >> minTempPrice)) {
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					throw InvalidParameter("price");
				}

				double maxTempPrice;
				cout << "\nPlease enter the upper limit: ";
				if (!(cin >> maxTempPrice)) {
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					throw InvalidParameter("price");
				}

				system("cls");
				UI::DisplayFrame("APPS BY PRICE");
				listAppsByPrice(minTempPrice, maxTempPrice);
				cin.ignore(INT_MAX, '\n');
				system("pause");
				break;
			}
			case 9: {
				unsigned tempRating;
				cout << "\nPlease enter the rating: ";
				if (!(cin >> tempRating)) {
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					throw InvalidParameter("rating");
				}

				system("cls");
				UI::DisplayFrame("APPS BY RATING");
				cin.ignore(INT_MAX, '\n');
				listAppsByRating(tempRating);
				system("pause");
				break;
			}
			case 0:
				return;
			}
		}
		catch (InvalidParameter &ip) {
			cout << "\nERROR: invalid parameter " << ip.what() << "\n";
			system("pause");
		}
		catch (DeveloperInexistente &e) {
			cout << "\nERRROR: developer " << e.getName() << " not found.\n";
			system("pause");
		}
		catch (AppInexistente &e) {
			cout << "\nERROR: app " << e.getName() << " does not exist.\n";
			system("pause");
		}
	}
}

void AppStore::App_menu() {
	int userChoice;
	string tempStr;
	while (true) {
		try {
			system("cls");
			UI::DisplayFrame("APP C/R/U/D");
			UI::DisplayMenuTop();
			UI::DisplayMenuItem(1, "Create a new app");
			UI::DisplayMenuItem(2, "Update an existing app");
			UI::DisplayMenuItem(3, "Delete an existing app");
			UI::DisplayMenuTop();
			UI::DisplayMenuItem(4, "Free vouchers");
			UI::DisplayMenuBottom();
			cout << "Please select an option: ";
			getline(cin, tempStr);
			userChoice = atoi(tempStr.c_str());
			if (userChoice < 0 || userChoice > 4) {
				throw InvalidParameter("choice");
			}
			switch (userChoice) {
			case 1:
				App_create(-1);
				system("pause");
				App_write();
				break;
			case 2:
				App_update(-1);
				system("pause");
				App_write();
				break;
			case 3:
				App_delete(-1);
				system("pause");
				App_write();
				break;
			case 4:
				freeVoucher();
				Cliente_write();
				system("pause");
				break;
			case 0:
				return;
			}
		}
		catch (InvalidParameter &ip) {
			cout << "\nERROR: invalid parameter " << ip.what() << "\n";
			system("pause");
		}
		catch (DeveloperInexistente &e) {
			cout << "\nERRROR: developer " << e.getName() << " not found.\n";
			system("pause");
		}
		catch (JaExiste &e) {
			cout << "\nERROR: app " << e.getName() << " already exists.\n";
			system("pause");
		}
		catch (AppInexistente &e) {
			cout << "\nERROR: app " << e.getName() << " does not exist.\n";
			system("pause");
		}
	}
}

bool AppStore::App_create(int devIndex) {
	string tempName;
	string tempDeveloper;
	string tempCategory;
	string tempDescription;
	string tempStr;
	double tempPrice;

	system("cls");
	UI::DisplayFrame("CREATE APP");

	cout << "Please enter the app name:\n";
	getline(cin, tempName);
	int i = App_index(tempName);
	int j;
	if (tempName == "") {
		throw InvalidParameter("name");
	}
	if (i != -1) {
		throw JaExiste(tempName);
	}

	if (devIndex == -1) {
		cout << "\nPlease enter the developer name:\n";
		getline(cin, tempDeveloper);
		j = Developer_index(tempDeveloper);
		if (j == -1) {
			throw DeveloperInexistente(tempDeveloper);
		}
	}
	else {
		j = devIndex;
	}

	cout << "\nPlease enter the category:\n";
	getline(cin, tempCategory);

	cout << "\nPlease enter a description:\n";
	getline(cin, tempDescription);

	cout << "\nPlease enter the price:\n";
	cin >> tempPrice;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		throw InvalidParameter("price");
	}
	if (tempPrice < 0) {
		throw InvalidParameter("price");
	}

	App tempApp = App(tempName, tempPrice, tempCategory, tempDescription);
	tempApp.setDeveloper(developers[j]);
	++(*developers[j]);
	if (devIndex == -1)	{
		cin.ignore(INT_MAX, '\n');
		cout << "\nINFORMATION: app published successfully!\n";
		apps.push_back(tempApp);
	}
	else {
		cin.ignore(INT_MAX, '\n');
		cout << "\nINFORMATION: app added to queue successfully, waiting for validation.\n";
		appsPendentes.push(tempApp);
	}

	return true;
}

bool AppStore::App_delete(int devIndex) {
	string tempName;

	system("cls");
	UI::DisplayFrame("DELETE APP");

	cout << "\nPlease enter the app name:\n";
	getline(cin, tempName);

	int i = App_index(tempName);
	if (i == -1) {
		throw AppInexistente(tempName);
	}

	if (devIndex == -1) {
		int j = Developer_index(apps[i].getDeveloper()->getName());
		if (j != -1) {
			--(*developers[j]);
		}
		apps.erase(apps.begin() + i);
		cout << "\nINFORMATION: app removed from the store successfully.\n";
		return true;
	}

	if (apps[i].getDeveloper() == developers[devIndex]) {
		apps.erase(apps.begin() + i);
		--(*developers[devIndex]);
		cout << "\nINFORMATION: app removed from the store successfully.\n";
		return true;
	}
	else {
		cout
			<< "\nERROR: permission denied - can't remove apps from other developers\n";
		return false;
	}
}

bool AppStore::App_update(int devIndex) {
	string tempName;
	string tempDescription;
	string tempCategory;
	string tempStr;
	double tempPrice;

	system("cls");
	UI::DisplayFrame("UPDATE APP");

	cout << "\nPlease enter the app name, <enter> to cancel:\n" << endl;
	getline(cin, tempName);

	if (tempName == "") {
		return true;
	}

	int i = App_index(tempName);
	if (i != -1) {
		cout << "\nERROR: app " << tempName << "not found.\n";
	}

	if (devIndex != -1) {
		if (apps[i].getDeveloper() != developers[devIndex]) {
			cout
				<< "\nERROR: permission denied - can't modify apps from other developers\n";
			return false;
		}
	}
	cout << "\nPlease enter a new name, <enter> to skip:\n";
	getline(cin, tempStr);

	if (tempStr != "") {
		int j = App_index(tempStr);
		if (j != -1) {
			throw JaExiste(tempStr);
		}
		apps[i].setName(tempStr);
	}

	cout << "\nPlease enter a new category, <enter> to skip:\n";
	getline(cin, tempCategory);

	if (tempCategory != "") {
		apps[i].setCategory(tempCategory);
	}

	cout << "\nPlease enter a new description, <enter> to skip:\n";
	getline(cin, tempDescription);

	if (tempDescription != "") {
		apps[i].setDescription(tempDescription);
	}

	cout << "\nPlease enter a new price, (-1) to skip:\n";
	cin >> tempPrice;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		throw InvalidParameter("price");
	}
	if (tempPrice >= 0) {
		apps[i].setPrice(tempPrice);
	}

	return true;
}

bool AppStore::Developer_create() {
	string tempName;
	string tempAddress;
	int tempNIF;
	string tempStr;
	int userChoice;

	system("cls");
	UI::DisplayFrame("CREATE DEVELOPER");

	cout << "Press 1 to create an individual developer.\n";
	cout << "Press 2 if we're talking about a company.\n";
	cout << "\nPlease select an option: ";
	getline(cin, tempStr);
	userChoice = atoi(tempStr.c_str());

	if (userChoice != 1 && userChoice != 2) {
		throw InvalidParameter("choice");
	}

	if (userChoice == 2) {
		cout << "\nPlease enter the company's oficial name:\n";
	}
	else {
		cout << "\nPlease enter the developer's name:\n";
	}

	getline(cin, tempName);

	if (tempName == "") {
		throw InvalidParameter("name");
	}

	int i = Developer_index(tempName);
	if (i != -1) {
		throw JaExiste(tempName);
	}

	if (userChoice == 2) {
		cout << "\nPlease enter the company's address:\n";
	}
	else {
		cout << "\nPlease enter the developer's adress:\n";
	}

	getline(cin, tempAddress);

	if (tempAddress == "") {
		throw InvalidParameter("address");
	}

	if (userChoice == 2) {
		cout << "\nPlease enter the company's tax ID number:\n";
		getline(cin, tempStr);
		if (tempStr.length() != 9) {
			throw InvalidParameter("NIF");
		}
		tempNIF = atoi(tempStr.c_str());
	}

	if (userChoice == 2) {
		Developer* temp = new Developer_Empresa(tempName, tempAddress, tempNIF);
		developers.push_back(temp);
	}
	else {
		Developer* temp = new Developer_Individual(tempName, tempAddress);
		developers.push_back(temp);
	}

	cout << "\nINFORMATION: developer created successfully.\n";
	return true;
}

bool AppStore::Developer_update() {
	string tempName;
	string tempStr;

	system("cls");
	UI::DisplayFrame("UPDATE DEVELOPER");

	cout << "\nPlease enter the developer/company name:\n";
	getline(cin, tempName);

	int i = Developer_index(tempName);
	if (i == -1) {
		throw DeveloperInexistente(tempName);
	}

	if (developers[i]->getType() == DEVELOPER_EMPRESA) {
		cout << "\nPlease enter a new company name, <enter> to skip:\n";
	}
	else {
		cout << "\nPlease enter a new name, <enter> to skip:\n";
	}

	getline(cin, tempStr);

	int j = Developer_index(tempStr);
	if (j != -1) {
		throw JaExiste(tempStr);
	}

	if (tempStr != "") {
		developers[i]->setName(tempStr);
	}

	cout << "\nPlease enter your new address, <enter> to skip:\n";
	getline(cin, tempStr);

	if (tempStr != "") {
		developers[i]->setAddress(tempStr);
	}

	if (developers[i]->getType() == DEVELOPER_EMPRESA) {
		cout << "\nPlease enter your new tax ID number, <enter> to skip:\n";
		getline(cin, tempStr);

		if (tempStr.length() != 9) {
			throw InvalidParameter("NIF");
		}

		int tempNIF = atoi(tempStr.c_str());
		dynamic_cast<Developer_Empresa*>(developers[i])->setNIF(tempNIF);
	}
	cout << "\nINFORMATION: developer information updated successfully.\n";
	return true;
}

bool AppStore::Developer_delete() {
	string tempName;

	system("cls");
	UI::DisplayFrame("DELETE DEVELOPER");

	cout << "Please enter the developer's name:" << endl;
	getline(cin, tempName);

	if (tempName == "") {
		throw InvalidParameter("name");
	}

	int i = Developer_index(tempName);
	if (i == -1) {
		throw DeveloperInexistente(tempName);
	}

	for (size_t j = 0; j < apps.size(); j++) {
		if (apps[j].getDeveloper() == developers[i]) {
			apps.erase(apps.begin() + j);
			j--;
		}
	}

	developers.erase(developers.begin() + i);
	cout << "\nINFORMATION: developer deleted sucessfully.\n";
	return true;
}

void AppStore::App_print(int appIndex, int cliIndex) {
	while (true) {
		system("cls");
		UI::DisplayFrame(to_upper(apps[appIndex].getName()));
		cout << left << "\t\t" << "Developer: "
			<< apps[appIndex].getDeveloper()->getName() << endl;
		cout << left << "\t\t" << "Category: " << setw(24)
			<< apps[appIndex].getCategory() << setw(5)
			<< apps[appIndex].getRating().to_string();
		cout << " (" << UI::FormatRating(apps[appIndex].getRating().get())
			<< ")" << endl;
		cout << left << "\t\t" << "Price: $" << fixed << setw(28)
			<< setprecision(2) << apps[appIndex].getPrice();
		cout << apps[appIndex].getRating().r.size() << " ratings";
		cout << "\n\n\t\tDescription: " << endl;
		cout << "\t\t" << apps[appIndex].getDescription() << endl << endl;

		UI::Display("<a> add to cart, <l> list comments");
		UI::Display("<c> comment, <r> rate");
		UI::Display("<b> go back");
		cout << "\nPlease choose an option: ";

		string tempStr;
		getline(cin, tempStr);

		if (tempStr.length() != 1) {
			throw InvalidParameter("choice");
		}

		switch (tempStr[0]) {
		case 'a': {
			vector<App> ownedApps = clientes[cliIndex]->getOwnedApps();
			for (size_t i = 0; i < ownedApps.size(); i++) {
				if (ownedApps[i] == apps[appIndex]) {
					throw JaExiste(apps[appIndex].getName());
				}
			}
			cart.pushApp(apps[appIndex]);
			cout << "\nINFORMATION: " << apps[appIndex].getName()
				<< " added to cart.\n";
			system("pause");
			return;
		}

		case 'r': {
			App_rate(appIndex);
			break;
		}

		case 'c': {
			App_comment(appIndex, cliIndex);
			break;
		}

		case 'l': {
			system("cls");
			vector<Comentario> appComments = apps[appIndex].getComments();
			ostringstream os;
			os << "COMMENTS (" << appComments.size() << ")";
			UI::DisplayFrame(os.str());
			cout << "\n";
			for (unsigned int i = 0; i < appComments.size(); i++) {
				cout << appComments[i].clientName << endl;
				cout << appComments[i].comment << endl << endl;
			}
			system("pause");
			break;
		}
		case 'b':
			return;
		default:
			throw InvalidParameter("choice");
		}
	}
}

bool operator<(const App &lhs, const App &rhs)
{
	if (lhs.getDate() == rhs.getDate())
	{
		if (lhs.getPrice() == rhs.getPrice())
		{
			return (lhs.getName() < rhs.getName());
		}
		return (lhs.getPrice() > rhs.getPrice());
	}
	return (lhs.getDate() < rhs.getDate());
}





void AppStore::App_publish() {
	priority_queue<App> tempQueue;

	while (!appsPendentes.empty()) {
		system("cls");
		UI::DisplayFrame(to_upper(appsPendentes.top().getName()));
		cout << left << "\t\t" << "Developer: "
			<< appsPendentes.top().getDeveloper()->getName() << "\n";
		cout << left << "\t\t" << "Category: " << setw(24)
			<< appsPendentes.top().getCategory();
		cout << left << "\t\t" << "Price: $" << fixed << setw(28)
			<< setprecision(2) << appsPendentes.top().getPrice();
		cout << "\n\n\t\tDescription: " << endl;
		cout << "\t\t" << appsPendentes.top().getDescription() << "\n\n";
		UI::Display("<q> decide later");
		cout << "\nDo you want to publish this app? (y/n): ";

		string tempStr;
		getline(cin, tempStr);

		if (tempStr.size() != 1) {
			throw InvalidParameter("choice");
		}

		if (tempStr[0] == 'q') {
			break;
		}

		switch (tempStr[0]) {
		case 'y':
			apps.push_back(appsPendentes.top());
			appsPendentes.pop();
			break;
		case 'n':
			tempQueue.push(appsPendentes.top());
			appsPendentes.pop();
			break;
		}
	}
	while (!tempQueue.empty()) {
		appsPendentes.push(tempQueue.top());
		tempQueue.pop();
	}
}

void AppStore::App_checkout(int cliIndex, bool voucher) {
	vector<App> boughtApps = cart.getApps();
	if (boughtApps.size() == 0) {
		cout << "\nCheckout failed. Your shopping cart is empty.\n";
		system("pause");
		return;
	}
	if (voucher) {
		cart.setPrice(cart.getPrice() * 0.95);
	}
	if (cart.getPrice() > clientes[cliIndex]->getSaldo()) {
		cout << "\nCheckout failed. You don't have enough funds.\n";
		system("pause");
		return;
	}
	clientes[cliIndex]->setSaldo(
		clientes[cliIndex]->getSaldo() - cart.getPrice());
	if (voucher) {
		clientes[cliIndex]->setVoucher(false);
	}
	for (size_t i = 0; i < boughtApps.size(); i++) {
		Developer* devTemp = boughtApps[i].getDeveloper();
		int j = Developer_index(devTemp->getName());
		if (j == -1) {
			throw DeveloperInexistente(devTemp->getName());
		}
		clientes[cliIndex]->own(boughtApps[i]);
		developers[j]->sale(boughtApps[i].getPrice());
	}
	cart.setOwner(clientes[cliIndex]);
	vendas.push_back(cart);
	Cliente_write();
	Developer_write();
	Sales_write();
	resetCart();
	cout << "\nPurchase successful. Enjoy your new apps!\n";
	system("pause");
}

void AppStore::Cliente_browse(int cliIndex) {
	string tempStr;
	while (true) {
		try {
			system("cls");
			UI::DisplayFrame("BROWSE APPSTORE");
			listAppsByName();
			cout << endl << "Please choose an app, <0> to go back: ";
			getline(cin, tempStr);
			if (tempStr == "0") {
				return;
			}
			int i = App_index(tempStr);
			if (i == -1) {
				throw AppInexistente(tempStr);
			}
			App_print(i, cliIndex);
		}
		catch (AppInexistente &e) {
			cout << "\nERORR: app " << e.getName() << " not found.\n";
			system("pause");
		}
		catch (JaExiste &e) {
			cout << "\nERROR: couldn't add " << e.getName()
				<< " to cart - already exists\n";
			system("pause");
		}
	}
}

bool AppStore::Main_user(int cliIndex) {
	string tempStr;
	int userChoice;

	while (true) {
		try {
			system("cls");
			cout << "Customer: " << clientes[cliIndex]->getName();
			cout << " / Balance: "
				<< UI::FormatPrice(clientes[cliIndex]->getSaldo());
			cout << " / Apps: " << clientes[cliIndex]->getNumApps();
			cout << " / Voucher: "
				<< (clientes[cliIndex]->getVoucher() ? "Yes" : "No")
				<< endl;
			UI::DisplayFrame("CUSTOMER MENU");
			UI::DisplayMenuTop();
			UI::DisplayMenuItem(1, "Purchase app");
			UI::DisplayMenuItem(2, "List apps");
			UI::DisplayMenuItem(3, "Bought apps");
			UI::DisplayMenuItem(4, "Checkout cart");
			UI::DisplayMenuItem(5, "Transaction history");
			UI::DisplayMenuItem(6, "Add funds");
			UI::DisplayMenuItem(7, "Activate voucher");
			UI::DisplayMenuTop();
			UI::DisplayMenuItem(0, "Logout");
			UI::DisplayMenuTop();
			cout << "\nPlease select an option: ";
			getline(cin, tempStr);
			userChoice = atoi(tempStr.c_str());
			if (userChoice < 0 || userChoice > 7) {
				throw InvalidParameter("choice");
			}
			switch (userChoice) {
			case 0:
				resetCart();
				return true;
			case 1:
				Cliente_browse(cliIndex);
				break;
			case 2:
				App_list();
				break;
			case 3:
				system("cls");
				UI::DisplayFrame("APPS OWNED");
				App_table(clientes[cliIndex]->getOwnedApps());
				system("pause");
				break;
				//////////////////////////
				// Checkout            //
				/////////////////////////
			case 4: {
				system("cls");
				UI::DisplayFrame("CHECKOUT CART");
				App_table(cart.getApps());
				cout << endl;
				ostringstream os;
				os << "Total: " << UI::FormatPrice(cart.getPrice());
				if (clientes[cliIndex]->getVoucher()) {
					os << ", w/voucher: "
						<< UI::FormatPrice(cart.getPrice() * 0.95);
				}
				UI::Display(os.str());
				cout << endl;
				UI::Display("<c> checkout, <r> remove from cart");
				cout << endl << "Please select an option: ";
				getline(cin, tempStr);
				if (tempStr.length() != 1) {
					throw InvalidParameter("choice");
				}
				switch (tempStr[0]) {
				case 'c': {
					cout << endl << "Are you sure you want to checkout? (Y/n) ";
					getline(cin, tempStr);
					if (tempStr == "n") {
						break;
					}
					else {
						if (clientes[cliIndex]->getVoucher()) {
							cout
								<< "Do you want to use your voucher with this purchase? (Y/n)";
							getline(cin, tempStr);
							if (tempStr == "n") {
								App_checkout(cliIndex, false);
							}
							else {
								App_checkout(cliIndex, true);
							}
						}
						else {
							App_checkout(cliIndex, false);
						}
					}
					break;
				}

				case 'r': {
					cout << endl
						<< "Please enter the name of the app to be removed: ";
					getline(cin, tempStr);
					vector<App> cartApps = cart.getApps();
					size_t i;
					for (i = 0; i < cartApps.size(); i++) {
						if (cartApps[i].getName() == tempStr) {
							cart.pullApp(cartApps[i]);
							system("pause");
							break;
						}
					}
					break;
				}
				}
				break;
			}
			case 5: {
				system("cls");
				UI::DisplayFrame("YOUR TRANSACTION HISTORY");
				listSalesByCliente(cliIndex);
				system("pause");
				break;
			}
					//////////////////////////
					// Add Funds           //
					/////////////////////////
			case 6: {
				cout << endl << "(1) $5.00" << endl;
				cout << "(2) $10.00" << endl;
				cout << "(3) $20.00" << endl;
				cout << "(4) $50.00" << endl;
				cout << "Please choose the amount: ";
				getline(cin, tempStr);
				userChoice = atoi(tempStr.c_str());
				if (userChoice < 1 || userChoice > 4) {
					throw InvalidParameter("choice");
				}
				switch (userChoice) {
				case 1:
					clientes[cliIndex]->setSaldo(
						clientes[cliIndex]->getSaldo() + 5.00);
					break;
				case 2:
					clientes[cliIndex]->setSaldo(
						clientes[cliIndex]->getSaldo() + 10.00);
					break;
				case 3:
					clientes[cliIndex]->setSaldo(
						clientes[cliIndex]->getSaldo() + 20.00);
					break;
				case 4:
					clientes[cliIndex]->setSaldo(
						clientes[cliIndex]->getSaldo() + 50.00);
					break;
				}
				Cliente_write();
				cout << "Funds sucessfully added to your account!" << endl;
				break;
			}

					//////////////////////////
					// Activate Voucher    //
					/////////////////////////
			case 7: {
				string tempStr;
				string voucherCode = "I-LOVE-APPS";
				cout << endl << "Please enter the discount code: ";
				getline(cin, tempStr);
				if (tempStr == voucherCode) {
					if (clientes[cliIndex]->getVoucher()) {
						cout << "You already have a discount code." << endl;
					}
					else {
						clientes[cliIndex]->setVoucher(true);
						Cliente_write();
						cout << "Code activated successfully!" << endl;
					}
				}
				else {
					cout << "Invalid code, please try again..." << endl;
				}
				system("pause");
				break;
			}
			}
		}
		catch (InvalidParameter &ip) {
			cout << "\nERROR: invalid parameter " << ip.what() << "\n";
			system("pause");
		}
		catch (AppInexistente &e) {
			cout << "\nERROR: app " << e.getName() << " not found.\n";
			system("pause");
		}
	}
}

void AppStore::Main_developer(int devIndex) {
	string tempStr;
	int userChoice;

	while (true) {
		try {
			system("cls");
			cout << "Developer: " << developers[devIndex]->getName();
			if (developers[devIndex]->getType() == DEVELOPER_EMPRESA) {
				cout << " / Type: Company";
			}
			else {
				cout << " / Type: Individual";
			}
			cout << " / Balance: "
				<< UI::FormatPrice(developers[devIndex]->getBalance());
			cout << " / Apps: "
				<< UI::Format(developers[devIndex]->getNumApps(), 5);
			UI::DisplayFrame("DEVELOPER MENU");
			UI::DisplayMenuTop();
			UI::DisplayMenuItem(1, "Launch a new app");
			UI::DisplayMenuItem(2, "Update existing app");
			UI::DisplayMenuItem(3, "Remove existing app");
			UI::DisplayMenuTop();
			UI::DisplayMenuItem(4, "List apps published");
			UI::DisplayMenuBottom();
			cout << endl << "Please select an option: ";
			getline(cin, tempStr);
			userChoice = atoi(tempStr.c_str());
			if (userChoice < 0 || userChoice > 4) {
				throw InvalidParameter("choice");
			}
			switch (userChoice) {
			case 1:
				App_create(devIndex);
				system("pause");
				break;
			case 2:
				App_update(devIndex);
				system("pause");
				break;
			case 3:
				App_delete(devIndex);
				system("pause");
				break;
			case 4:
				system("cls");
				UI::DisplayFrame("YOUR APPS");
				listAppsByDeveloper(developers[devIndex]);
				system("pause");
				break;
			case 0:
				return;
			}
		}
		catch (InvalidParameter &ip) {
			cout << "\nERROR: invalid parameter " << ip.what() << "\n";
			system("pause");
		}
		catch (AppInexistente &e) {
			cout << "\nERROR: app " << e.getName() << " not found.\n";
			system("pause");
		}
		catch (DeveloperInexistente &e) {
			cout << "\nERROR: developer " << e.getName() << " not found.\n";
			system("pause");
		}
	}
}

void AppStore::Main_admin() {
	string tempStr;
	int userChoice;
	while (true) {
		try {
			system("cls");
			cout << this->nome;
			cout << " / Apps: " << apps.size();
			cout << " / Developers: " << developers.size();
			cout << " / Customers: " << clientes.size() << endl;
			UI::DisplayFrame("ADMINISTRATION MENU");
			UI::DisplayMenuTop();
			UI::DisplayMenuItem(1, "Manage apps");
			UI::DisplayMenuItem(2, "Manage developers");
			UI::DisplayMenuItem(3, "Manage customers");
			UI::DisplayMenuTop();
			UI::DisplayMenuItem(4, "List apps");
			UI::DisplayMenuItem(5, "List sales by ID");
			UI::DisplayMenuItem(6, "List sales by customer");
			UI::DisplayMenuItem(7, "List sales by apps");
			UI::DisplayMenuItem(8, "List sales by price");
			UI::DisplayMenuBottom();
			cout << "Please select an option: ";
			getline(cin, tempStr);
			userChoice = atoi(tempStr.c_str());
			if (userChoice < 0 || userChoice > 8) {
				throw InvalidParameter("choice");
			}
			switch (userChoice) {
			case 0: {
				return;
			}
			case 1: {
				App_menu();
				break;
			}
			case 2: {
				Developer_menu();
				break;
			}
			case 3: {
				Cliente_menu();
				break;
			}
			case 4: {
				App_list();
				break;
			}
			case 5: {
				system("cls");
				UI::DisplayFrame("SALES BY ID");
				Sales_table(vendas);
				system("pause");
				break;
			}
			case 6: {
				system("cls");
				UI::DisplayFrame("SALES BY CUSTOMER");
				listSalesByCliente();
				system("pause");
				break;
			}
			case 7: {
				system("cls");
				UI::DisplayFrame("SALES BY NO. APPS");
				listSalesByApps();
				system("pause");
				break;
			}
			case 8: {
				system("cls");
				UI::DisplayFrame("SALES BY PRICE");
				listSalesByPrice();
				system("pause");
				break;
			}
			}
		}
		catch (InvalidParameter &ip) {
			cout << "\nERROR: invalid parameter " << ip.what() << "\n";
			system("pause");
		}
	}
}

void AppStore::App_comment(int appIndex, int cliIndex) {
	string tempComment;
	cout << "Please enter your comment, <enter> to submit:\n";
	getline(cin, tempComment);
	if (apps[appIndex].comentar(clientes[cliIndex]->getName(), tempComment)
		== true) {
		cout << "\nINFORMATION: comment added successfully.\n";
		system("pause");
	}
	else {
		cout << "\nERROR: you have already published a comment for this app.\n";
		system("pause");
	}
}

void AppStore::App_rate(int appIndex) {
	uint8_t tempRating;
	string tempStr;
	cout << "Rate this app: ";
	getline(cin, tempStr);
	tempRating = atoi(tempStr.c_str());
	if (tempRating == 0 || tempRating > 5) {
		throw InvalidParameter("rating");
	}
	apps[appIndex].classificar(tempRating);
	cout << "\nINFORMATION: thanks for rating our app!\n";
	system("pause");
}

void AppStore::App_read() {
	ifstream fin;
	fin.open("Apps.bin");
	if (!fin.is_open()) {
		throw FileIOException("Apps.bin");
	}
	while (!fin.eof()) {
		// ler informações básicas (necessárias para o construtor)
		string tempName;
		getline(fin, tempName);

		if (tempName == "") {
			break;
		}

		string tempDev;
		getline(fin, tempDev);
		string tempCategory;
		getline(fin, tempCategory);
		string tempDescription;
		getline(fin, tempDescription);
		double tempPrice;
		fin.read((char*)&tempPrice, sizeof(double));

		// chamar construtor com parametros
		App tempApp = App(tempName, tempPrice, tempCategory, tempDescription);

		// procurar developer
		int devIndex = Developer_index(tempDev);
		if (devIndex != -1) {
			tempApp.setDeveloper(developers[devIndex]);
		}
		else {
			tempApp.setDeveloper(NULL);
		}

		// ler comentários e classificações para os vectores respectivos
		tempApp.read(fin);

		// push para o vector
		apps.push_back(tempApp);
	}
}

void AppStore::App_write() const {
	ofstream fout;
	fout.open("Apps.bin");
	if (!fout.is_open()) {
		throw FileIOException("Apps.bin");
	}
	for (size_t i = 0; i < apps.size(); i++) {
		fout << apps[i].getName() << endl;
		fout << apps[i].getDeveloper()->getName() << endl;
		fout << apps[i].getCategory() << endl;
		fout << apps[i].getDescription() << endl;
		double tempPrice = apps[i].getPrice();
		fout.write((char*)&tempPrice, sizeof(double));
		apps[i].write(fout);
	}
}

void AppStore::Cliente_read() {
	ifstream fin;
	fin.open("Clientes.bin");
	if (!fin.is_open()) {
		throw FileIOException("Clientes.bin");
	}
	while (!fin.eof()) {
		string tempName;
		getline(fin, tempName);
		if (tempName == "") {
			break;
		}
		double tempSaldo;
		fin.read((char*)&tempSaldo, sizeof(double));
		Cliente* tempCliente = new Cliente(tempName, tempSaldo);
		bool tempVoucher;
		fin.read((char*)&tempVoucher, sizeof(uint8_t));
		tempCliente->setVoucher(tempVoucher);
		uint32_t tempNumTransacoes;
		fin.read((char*)&tempNumTransacoes, sizeof(uint32_t));
		for (size_t i = 0; i < tempNumTransacoes; i++) {
			string tempAppName;
			getline(fin, tempAppName);
			int j = App_index(tempAppName);
			if (j != -1) {
				tempCliente->own(apps[j]);
			}
		}
		clientes.push_back(tempCliente);
	}
}

void AppStore::Cliente_write() const {
	ofstream fout;
	fout.open("Clientes.bin");
	if (!fout.is_open()) {
		throw FileIOException("Clientes.bin");
	}
	for (size_t i = 0; i < clientes.size(); i++) {
		fout << clientes[i]->getName() << endl;
		double tempSaldo = clientes[i]->getSaldo();
		fout.write((char*)&tempSaldo, sizeof(double));
		bool tempVoucher = clientes[i]->getVoucher();
		fout.write((char*)&tempVoucher, sizeof(uint8_t));
		uint32_t tempNumTransacoes = clientes[i]->getNumApps();
		fout.write((char*)&tempNumTransacoes, sizeof(uint32_t));
		vector<App> ownedApps = clientes[i]->getOwnedApps();
		for (size_t j = 0; j < tempNumTransacoes; j++) {
			fout << ownedApps[j].getName() << endl;
		}
	}
}

void AppStore::Developer_read() {
	ifstream fin;
	fin.open("Developers.bin");
	if (!fin.is_open()) {
		throw FileIOException("Developers.bin");
	}
	while (!fin.eof()) {
		uint8_t tempType;
		fin.read((char*)&tempType, sizeof(uint8_t));
		switch (tempType) {
		case DEVELOPER_INDIVIDUAL: {
			Developer* tempDev = new Developer_Individual;
			if (tempDev->read(fin))
				developers.push_back(tempDev);
			break;
		}
		case DEVELOPER_EMPRESA: {
			Developer* tempDev = new Developer_Empresa;
			if (tempDev->read(fin))
				developers.push_back(tempDev);
			break;
		}
		}
	}
}

void AppStore::Developer_write() {
	ofstream fout;
	fout.open("Developers.bin");
	if (!fout.is_open()) {
		throw FileIOException("Developers.bin");
	}
	for (size_t i = 0; i < developers.size(); i++) {
		uint8_t tempType = developers[i]->getType();
		fout.write((char*)&tempType, sizeof(uint8_t));
		developers[i]->write(fout);
	}
}

void AppStore::Sales_read() {
	ifstream fin;
	fin.open("Vendas.bin", ios::binary);
	if (!fin.is_open()) {
		throw FileIOException("Vendas.bin");
	}
	while (!fin.eof()) {
		string tempName;
		getline(fin, tempName);
		if (tempName == "") {
			break;
		}
		int i = Cliente_index(tempName);
		if (i == -1) {
			throw ClienteInexistente(tempName);
		}

		Cliente* tempCliente = clientes[i];

		double tempSaldo;
		fin.read((char*)&tempSaldo, sizeof(double));

		vector<App> tempApps;
		uint32_t tempNumApps;
		fin.read((char*)&tempNumApps, sizeof(uint32_t));
		for (size_t i = 0; i < tempNumApps; i++) {
			string tempAppName;
			getline(fin, tempAppName);
			int j = App_index(tempAppName);
			if (j != -1) {
				tempApps.push_back(apps[j]);
			}
		}

		Sale tempSale = Sale(tempCliente, tempApps, tempSaldo);
		vendas.push_back(tempSale);
	}
}

void AppStore::Sales_write() const {
	ofstream fout;
	fout.open("Vendas.bin", ios::binary);
	if (!fout.is_open()) {
		throw FileIOException("Vendas.bin");
	}
	for (size_t i = 0; i < vendas.size(); i++) {
		fout << vendas[i].getOwner()->getName() << "\n";
		double tempSaldo = vendas[i].getPrice();
		fout.write((char*)&tempSaldo, sizeof(double));
		uint32_t tempNumApps = vendas[i].getApps().size();
		fout.write((char*)&tempNumApps, sizeof(uint32_t));
		vector<App> boughtApps = vendas[i].getApps();
		for (size_t j = 0; j < boughtApps.size(); j++) {
			fout << boughtApps[j].getName() << "\n";
		}
	}
}

int AppStore::App_index(string name) const 
{
	for (unsigned int i = 0; i < apps.size(); i++) 
	{
		if (apps[i].getName() == name)
		{
			return i;
		}
	}
	return -1;
}

int AppStore::Cliente_index(string name) 
{
	for (unsigned int i = 0; i < clientes.size(); i++) 
	{
		if (clientes[i]->getName() == name) 
		{
			return i;
		}
	}
	return -1;
}

int AppStore::Developer_index(string name) const 
{
	for (unsigned int i = 0; i < developers.size(); i++) 
	{
		if (developers[i]->getName() == name) 
		{
			return i;
		}
	}
	return -1;
}