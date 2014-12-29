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

AppStore::AppStore() :
		appsRanking(new App("", 0, "", "")) {
	resetCart();
}

AppStore::~AppStore() {
}

AppStore::AppStore(string n) :
		nome(n), appsRanking(new App("", 0, "", "")) {
	resetCart();
}

void AppStore::resetCart() {
	cart = Sale();
	cart.setPrice(0.0);
	cart.setOwner(NULL);

	appsRanking.insert(new App("aaaa", 2.99, "Internet", "qqqq"));
	appsRanking.insert(new App("bbbb", 1.99, "Category", "xxxx"));

	BSTItrIn<App*> it(appsRanking);
	while (!it.isAtEnd()) {
		it.advance();
	}
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

vector<App*> AppStore::getAppsFromDev(Developer *dev) const {

	vector<App*> devApps;
	vector<App*>::const_iterator it = apps.begin();

	for (; it != apps.end(); it++) {
		if ((*it)->getDeveloper()->getName() == dev->getName()) {
			devApps.push_back((*it));
		}
	}

	return devApps;
}

string AppStore::getName() const {
	return nome;
}

bool AppStore::IOReadStore() {
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
	IOReadDevelopers();
	IOReadApps();
	IOReadClientes();
	IOReadSales();
	return true;
}

bool AppStore::IOWriteStore() const {
	IOWriteSales();
	IOWriteClientes();
	IOWriteApps();
	IOWriteDevelopers();
	return true;
}

void AppStore::Developer_menu() {

	int userChoice;
	string tempStr;

	while (true) {

		try {

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
				IOWriteDevelopers();
				system("pause");

				break;

			case 2:

				Developer_update();
				IOWriteDevelopers();
				system("pause");

				break;

			case 3:

				Developer_delete();
				IOWriteDevelopers();
				system("pause");

				break;

			case 4:

				UI::DisplayFrame("DEVELOPERS BY NAME");
				listDevelopersByName();
				system("pause");

				break;

			case 5:

				UI::DisplayFrame("DEVELOPERS BY SALES");
				listDevelopersBySales();
				system("pause");

				break;

			case 6:

				UI::DisplayFrame("DEVELOPERS BY NUMBER OF APPS");
				listDevelopersByApps();
				system("pause");

				break;

			case 0:

				return;

			}
		} catch (InvalidParameter &ip) {
			cout << ip;
			system("pause");
		} catch (DeveloperJaExiste &e) {
			cout << e;
			system("pause");
		} catch (DeveloperInexistente &e) {
			cout << e;
			system("pause");
		}
	}
}

vector<App*> AppStore::sortApps(vector<App*> v, Criteria s) const {

	vector<App*> sortedVector = v;

	for (size_t i = 1; i < v.size(); i++) {

		App* tempApp = sortedVector[i];
		size_t j = 0;

		if (s == APP_NAME) {

			for (j = i; j > 0 && tempApp->getName() < sortedVector[j - 1]->getName(); j--) {
				sortedVector[j] = sortedVector[j - 1];
			}
		}

		else if (s == APP_PRICE) {

			for (j = i; j > 0 && tempApp->getPrice() < sortedVector[j - 1]->getPrice(); j--) {
				sortedVector[j] = sortedVector[j - 1];
			}
		}

		else if (s == APP_RATING) {

			for (j = i;
					j > 0
							&& tempApp->getRating().get()
									> sortedVector[j - 1]->getRating().get();
					j--) {
				sortedVector[j] = sortedVector[j - 1];
			}
		} else if (s == APP_DATE) {
			for (j = i;
					j > 0 && tempApp->getDate() < sortedVector[j - 1]->getDate();
					j--) {
				sortedVector[j] = sortedVector[j - 1];
			}
		}
		sortedVector[j] = tempApp;
	}
	return sortedVector;
}

vector<Cliente*> AppStore::sortClientes(vector<Cliente*> v, Criteria s) const {

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
		} else if (s == CLIENTE_APPS) {
			for (j = i;
					j > 0
							&& tempCliente->getNumApps()
									> sortedVector[j - 1]->getNumApps(); j--) {
				sortedVector[j] = sortedVector[j - 1];
			}
		} else if (s == CLIENTE_SALDO) {
			for (j = i;
					j > 0
							&& tempCliente->getSaldo()
									> sortedVector[j - 1]->getSaldo(); j--) {
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

vector<Developer*> AppStore::sortDevelopers(const vector<Developer*> &v, Criteria s) const {
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
		} else if (s == DEV_APPS) {
			for (j = i;
					j > 0
							&& tempDev->getNumApps()
									> sortedVector[j - 1]->getNumApps(); j--) {
				sortedVector[j] = sortedVector[j - 1];
			}
		} else if (s == DEV_SALES) {
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

void AppStore::GUIClienteTable(const vector<Cliente*> &v) const {

	const int rowCount = 4;
	int tableLength[rowCount] = { 32, 10, 10, 9 };

	vector<string> tableLabel = { " Customer name", " No. Apps ", " Balance", " Voucher" };
	vector<Cliente*>::const_iterator it = v.begin();

	UI::DisplayTable(rowCount, tableLabel, tableLength);

	for (; it != v.end(); it++) {
		vector<string> tableRow(rowCount);
		tableRow[0] = (*it)->getName();
		tableRow[1] = UI::Format((*it)->getNumApps(), 5);
		tableRow[2] = UI::FormatPrice((*it)->getSaldo());
		tableRow[3] = (*it)->getVoucher() ? "  Yes" : "  No";
		UI::DisplayTableRow(rowCount, tableRow, tableLength);
	}
}

void AppStore::listClientesByName() const {
	GUIClienteTable(sortClientes(clientes, CLIENTE_NAME));
}

void AppStore::listClientesBySaldo() const {
	GUIClienteTable(sortClientes(clientes, CLIENTE_SALDO));
}

void AppStore::listClientesByApps() const {
	GUIClienteTable(sortClientes(clientes, CLIENTE_APPS));
}

///////////////////////////////
// LIST&SORT DEVELOPERS
//////////////////////////////

void AppStore::GUIDeveloperTable(const vector<Developer*> &v) const {

	const int rowCount = 4;
	int tableLength[rowCount] = { 24, 24, 12, 11 };

	vector<string> tableLabel = { " Developer name", " Address", " Type ", " NIF" };
	vector<Developer*>::const_iterator it = v.begin();

	UI::DisplayTable(rowCount, tableLabel, tableLength);

	for (; it != v.end(); it++) {
		(*it)->print();
	}
}

void AppStore::GUIDeveloperTable2(const vector<Developer*> &v) const {

	const int rowCount = 4;
	int tableLength[rowCount] = { 24, 24, 12, 12 };

	vector<string> tableLabel = { " Developer name", " Address", " No. Apps ", " Balance" };
	vector<Developer*>::const_iterator it = v.begin();

	UI::DisplayTable(rowCount, tableLabel, tableLength);

	for (; it != v.end(); it++) {
		vector<string> tableRow(rowCount);
		tableRow[0] = (*it)->getName();
		tableRow[1] = (*it)->getAddress();
		tableRow[2] = UI::Format((*it)->getNumApps(), 10);
		tableRow[3] = UI::FormatPrice((*it)->getBalance());
		UI::DisplayTableRow(rowCount, tableRow, tableLength);
	}
}

void AppStore::listDevelopersByName() const {
	GUIDeveloperTable(sortDevelopers(developers, DEV_NAME));
}

void AppStore::listDevelopersByApps() const {
	GUIDeveloperTable2(sortDevelopers(developers, DEV_APPS));
}

void AppStore::listDevelopersBySales() const {
	GUIDeveloperTable2(sortDevelopers(developers, DEV_SALES));
}

///////////////////////////////
// LIST&SORT QUEUE
//////////////////////////////

vector<App*> AppStore::listDeveloperPending(const Developer* dev) const {

	vector<App*> tempVector = queueToVector();
	vector<App*> sortedVector;
	vector<App*>::const_iterator it = tempVector.begin();

	for (; it != tempVector.end(); it++) {
		if ((*it)->getDeveloper() == dev) {
			sortedVector.push_back(*it);
		}
	}

	return sortedVector;
}

void AppStore::listDevPendingByPriority(const Developer* dev) const {
	GUIAppsTable(listDeveloperPending(dev));
}

void AppStore::listDevPendingByName(const Developer* dev) const {
	GUIAppsTable(sortApps(listDeveloperPending(dev), APP_NAME));
}

void AppStore::listPendingByPriority() const {
	GUIAppsTable(queueToVector());
}

void AppStore::listPendingByName() const {
	GUIAppsTable(sortApps(queueToVector(), APP_NAME));
}

///////////////////////////////
// LIST&SORT HASH TABLE
//////////////////////////////

vector<App> AppStore::listDeveloperRemoved(int devIndex) const {

	vector<App> sortedVector;

	if (devIndex != -1) {
		hashDeveloper devTable = developers[devIndex]->getRemovedApps();
		hashDeveloper::const_iterator it = devTable.begin();
		for (; it != devTable.end(); it++) {
			sortedVector.push_back(*it);
		}
	}
	return sortedVector;
}

void AppStore::listRemovedByName(int devIndex) const {

	vector<App> sortedVector = listDeveloperRemoved(devIndex);
	GUIAppsTable(sortApps(sortedVector,APP_NAME));
}

void AppStore::listRemovedByPrice(int devIndex) const {

	vector<App> sortedVector = listDeveloperRemoved(devIndex);
	GUIAppsTable(sortApps(sortedVector, APP_PRICE));
}

///////////////////////////////
// LIST&SORT SALES
//////////////////////////////

void AppStore::GUISalesTable(const vector<Sale> &s) const {

	const int rowCount = 3;
	int tableLength[3] = { 32, 10, 10 };

	vector<string> tableLabel = { " Customer name", " No. Apps ", " Price" };
	vector<Sale>::const_iterator it = s.begin();

	UI::DisplayTable(rowCount, tableLabel, tableLength);

	for (; it != s.end(); it++) {
		vector<string> tableRow(rowCount);
		tableRow[0] =  it->getOwner()->getName();
		tableRow[1] = UI::Format(it->getApps().size(), 5);
		tableRow[2] = UI::FormatPrice(it->getPrice());
		UI::DisplayTableRow(rowCount, tableRow, tableLength);
	}
}

void AppStore::listSalesByCliente() const {
	GUISalesTable(sortSales(vendas, SALES_CLIENTE));
}

void AppStore::listSalesByCliente(int cliIndex) const {

	vector<Sale> sortedVector;
	vector<Sale>::const_iterator it = vendas.begin();

	for (; it != vendas.end(); it++) {
		if (it->getOwner() == clientes[cliIndex]) {
			sortedVector.push_back(*it);
		}
	}

	GUISalesTable(sortedVector);
}

void AppStore::listSalesByID() const {
	GUISalesTable(vendas);
}

void AppStore::listSalesByApps() const {
	GUISalesTable(sortSales(vendas, SALES_APPS));
}

void AppStore::listSalesByPrice() const {
	GUISalesTable(sortSales(vendas, SALES_PRICE));
}

///////////////////////////////
// LIST&SORT APPS
//////////////////////////////

void AppStore::GUIAppsTable(const vector<App*> &v) const {

	const int rowCount = 5;
	int tableLength[rowCount] = { 24, 16, 12, 8, 10 };

	vector<string> tableLabel = { " Name", " Developer", " Category", " Price", " Rating" };

	UI::DisplayTable(rowCount, tableLabel, tableLength);
	for (unsigned int i = 0; i < v.size(); i++) {
		vector<string> tableRow(rowCount);
		tableRow[0] = v[i]->getName();
		if (v[i]->getDeveloper() == NULL) {
			tableRow[1] = "Anonymous";
		} else {
			tableRow[1] = v[i]->getDeveloper()->getName();
		}
		tableRow[2] = v[i]->getCategory();
		if (v[i]->getPrice() == 0.0) {
			tableRow[3] = "FREE";
		} else {
			tableRow[3] = UI::FormatPrice(v[i]->getPrice());
		}
		if (v[i]->getRating().get() == 0.0) {
			tableRow[4] = "N/A";
		} else {
			tableRow[4] = UI::FormatRating(v[i]->getRating().get());
		}
		UI::DisplayTableRow(rowCount, tableRow, tableLength);
	}
}

void AppStore::GUIAppsTable(const vector<App> &v) const {

	const int rowCount = 5;
	int tableLength[rowCount] = { 24, 16, 12, 8, 10 };

	vector<string> tableLabel = { " Name", " Developer", " Category", " Price", " Rating" };
	vector<App>::const_iterator it = v.begin();

	UI::DisplayTable(rowCount, tableLabel, tableLength);

	for (; it != v.end(); it++) {

		vector<string> tableRow(rowCount);
		tableRow[0] = it->getName();
		if (it->getDeveloper() == NULL) {
			tableRow[1] = "Anonymous";
		} else {
			tableRow[1] = it->getDeveloper()->getName();
		}
		tableRow[2] = it->getCategory();
		if (it->getPrice() == 0.0) {
			tableRow[3] = "FREE";
		} else {
			tableRow[3] = UI::FormatPrice(it->getPrice());
		}
		if (it->getRating().get() == 0.0) {
			tableRow[4] = "N/A";
		} else {
			tableRow[4] = UI::FormatRating(it->getRating().get());
		}
		UI::DisplayTableRow(rowCount, tableRow, tableLength);
	}
}

void AppStore::listAppsByCategory(string cat) const {

	vector<App*> sortedVector;
	vector<App*>::const_iterator it = apps.begin();

	for (; it != apps.end(); it++) {
		if ((*it)->getCategory() == cat) {
			sortedVector.push_back(*it);
		}
	}

	GUIAppsTable(sortApps(sortedVector, APP_NAME));
}

void AppStore::listAppsByCliente(int cliIndex) const {
	GUIAppsTable(sortApps(clientes[cliIndex]->getOwnedApps(), APP_NAME));
}

void AppStore::listAppsByDeveloper(const Developer* dev) const {

	vector<App*> sortedVector;
	vector<App*>::const_iterator it = apps.begin();

	for (; it != apps.end(); it++) {
		if ((*it)->getDeveloper() == dev) {
			sortedVector.push_back(*it);
		}
	}

	GUIAppsTable(sortApps(sortedVector, APP_NAME));
}

void AppStore::listAppsByDateAscending() const {
	GUIAppsTable(sortApps(apps, APP_DATE));
}

void AppStore::listAppsByDateDescending() const {
	vector<App*> sortedVector = sortApps(apps, APP_DATE);
	reverse(sortedVector.begin(), sortedVector.end());
	GUIAppsTable(sortedVector);
}

void AppStore::listAppsByName() const {
	GUIAppsTable(sortApps(apps, APP_NAME));
}

void AppStore::listAppsByPrice() const {
	GUIAppsTable(sortApps(apps, APP_PRICE));
}

void AppStore::listAppsByPrice(double min, double max) const {

	vector<App*> sortedVector;
	vector<App*>::const_iterator it = apps.begin();

	for (; it != apps.end(); it++) {
		if ((*it)->getPrice() >= min && (*it)->getPrice() <= max) {
			sortedVector.push_back(*it);
		}
	}

	GUIAppsTable(sortApps(sortedVector, APP_NAME));
}

void AppStore::listAppsByRating() const {
	GUIAppsTable(sortApps(apps, APP_RATING));
}

void AppStore::listAppsByRating(unsigned value) const {

	vector<App*> sortedVector;
	vector<App*>::const_iterator it = apps.begin();

	for (; it != apps.end(); it++) {
		if ((*it)->getRating().floor() == value) {
			sortedVector.push_back(*it);
		}
	}

	GUIAppsTable(sortApps(sortedVector, APP_NAME));
}

void AppStore::freeVoucher() {
	unsigned int i = (unsigned int) round(clientes.size() * 0.1);
	cout << "\n";
	if (i == 0) {
		cout << "\nINFORMATION: not enough customers on the database\n";
	}
	while (i) {
		unsigned int j = rand() % clientes.size();
		if (clientes[j]->getVoucher() == false) {
			clientes[j]->setVoucher(true);
			i--;
			cout << "\nINFORMATION: " << clientes[j]->getName() << " has recieved a voucher!\n";
		}
	}
}

bool AppStore::insertApp(App* app) {

	vector<App*>::const_iterator it = find(apps.begin(), apps.end(), app);

	if (it == apps.end()) {
		apps.push_back(app);
		return true;
	}

	return false;
}

bool AppStore::insertDeveloper(Developer* dev) {

	vector<Developer*>::const_iterator it = find(developers.begin(), developers.end(), dev);

	if (it == developers.end()) {
		developers.push_back(dev);
		return true;
	}

	return false;
}

bool AppStore::insertCliente(Cliente* c1) {

	vector<Cliente*>::const_iterator it = find(clientes.begin(), clientes.end(), c1);

	if (it == clientes.end()) {
		clientes.push_back(c1);
		return true;
	}

	return false;
}

const string customerCreated = "INFORMATION: customer created successfully.";
const string customerUpdated =  "INFORMATION: customer information updated successfully.";
const string customerDeleted = "INFORMATION: customer deleted successfully.";

void displayMessage(string msg) {
	cout << endl << msg << endl;
}

bool AppStore::createCliente() {
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

	int i = indexCliente(tempName);
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
	displayMessage(customerCreated);

	return true;
}

bool AppStore::updateCliente() {
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

	i = indexCliente(tempName);
	if (i == -1) {
		throw ClienteInexistente(tempName);
	}

	cout << "New name, <enter> to skip: ";
	getline(cin, tempStr);

	int j = indexCliente(tempStr);
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
	displayMessage(customerUpdated);

	return true;
}

bool AppStore::deleteCliente() {

	string tempName;

	system("cls");
	UI::DisplayFrame("DELETE CUSTOMER");

	cout << "Please enter the customer's name:" << endl;
	getline(cin, tempName);

	if (tempName == "") {
		throw InvalidParameter("name");
	}

	int i = indexCliente(tempName);
	if (i == -1) {
		throw ClienteInexistente(tempName);
	}

	clientes.erase(clientes.begin() + i);
	displayMessage(customerDeleted);

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

				createCliente();
				IOWriteClientes();
				system("pause");

				break;

			case 2:

				updateCliente();
				IOWriteClientes();
				system("pause");

				break;

			case 3:

				deleteCliente();
				IOWriteClientes();
				system("pause");

				break;

			case 4:

				UI::DisplayFrame("CUSTOMERS BY NAME");
				listClientesByName();
				system("pause");

				break;

			case 5:

				UI::DisplayFrame("CUSTOMERS BY BALANCE");
				listClientesBySaldo();
				system("pause");

				break;

			case 6:

				UI::DisplayFrame("CUSTOMERS BY NUMBER OF APPS");
				listClientesByApps();
				system("pause");

				break;

			case 0:

				return;

			}
		} catch (InvalidParameter &ip) {
			cout << ip;
			system("pause");
		} catch (ClienteJaExiste &e) {
			cout << e;
			system("pause");
		} catch (ClienteInexistente &e) {
			cout << e;
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
			case 1:

				UI::DisplayFrame("APPS BY NAME");
				listAppsByName();
				system("pause");

				break;

			case 2:

				UI::DisplayFrame("APPS BY PRICE");
				listAppsByPrice();
				system("pause");

				break;

			case 3:

				UI::DisplayFrame("APPS BY RATING");
				listAppsByRating();
				system("pause");

				break;

			case 4:

				UI::DisplayFrame("APPS BY PUBLISH DATE (OLDEST)");
				listAppsByDateAscending();
				system("pause");

				break;

			case 5:

				UI::DisplayFrame("APPS BY PUBLISH DATE (NEWEST)");
				listAppsByDateDescending();
				system("pause");

				break;

			case 6: {
				cout << "\nPlease choose a category: ";
				getline(cin, tempStr);
				if (tempStr == "") {
					throw InvalidParameter("category");
				}

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

				int i = indexDeveloper(tempStr);
				if (i == -1) {
					throw DeveloperInexistente(tempStr);
				}

				UI::DisplayFrame("APPS BY DEVELOPER");
				listAppsByDeveloper(developers[indexDeveloper(tempStr)]);
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
		} catch (InvalidParameter &ip) {
			cout << ip;
			system("pause");
		} catch (DeveloperInexistente &e) {
			cout << e;
			system("pause");
		} catch (AppInexistente &e) {
			cout << e;
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

				createApp(-1);
				system("pause");
				IOWriteApps();

				break;

			case 2:

				updateApp(-1);
				system("pause");
				IOWriteApps();

				break;

			case 3:

				deleteApp(-1);
				system("pause");
				IOWriteApps();

				break;

			case 4:

				freeVoucher();
				IOWriteClientes();
				system("pause");

				break;

			case 0:

				return;

			default:

				throw InvalidParameter("choice");
			}
		} catch (InvalidParameter &ip) {
			cout << ip;
			system("pause");
		} catch (DeveloperInexistente &e) {
			cout << e;
			system("pause");
		} catch (AppJaExiste &e) {
			cout << e;
			system("pause");
		} catch (AppInexistente &e) {
			cout << e;
			system("pause");
		}
	}
}

const string appUpdated = "INFORMATON: app information updated successfully.";
const string appRemoved = "INFORMATION: app removed from the store successfully.";
const string appPublished = "INFORMATION: app published successfully!";
const string appWaitingValidation = "INFORMATION: added app to queue successfully, waiting for approval.";
const string appPermissionsRemove = "ERROR: permission denied - can't remove apps from other developers.";
const string appPermissionsUpdate = "ERROR: permission denied - can't modify apps from other developers.";

bool AppStore::createApp(int devIndex) {

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
	int i = appIndex(tempName);
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
		j = indexDeveloper(tempDeveloper);
		if (j == -1) {
			throw DeveloperInexistente(tempDeveloper);
		}
	} else {
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

	App* newApp = new App(tempName, tempPrice, tempCategory, tempDescription);

	newApp->setDeveloper(developers[j]);

	if (devIndex == -1) {
		cin.ignore(INT_MAX, '\n');
		displayMessage(appPublished);
		developers[j]->push(newApp);
		appsRanking.insert(newApp);
		apps.push_back(newApp);
	}

	else {
		cin.ignore(INT_MAX, '\n');
		displayMessage(appWaitingValidation);
		appsPendentes.push(newApp);
	}

	return true;
}

bool AppStore::deleteApp(int devIndex) {

	string tempName;

	UI::DisplayFrame("DELETE APP");

	cout << "\nPlease enter the app name:\n";
	getline(cin, tempName);

	int i = appIndex(tempName);
	if (i == -1) {
		throw AppInexistente(tempName);
	}

	if (devIndex == -1) {

		int j = indexDeveloper(apps[i]->getDeveloper()->getName());
		if (j != -1) {
			developers[j]->pop(apps[i]);
		}

		apps.erase(apps.begin() + i);
		displayMessage(appRemoved);
		return true;
	}

	if (apps[i]->getDeveloper() == developers[devIndex]) {
		developers[devIndex]->pop(apps[i]);
		apps.erase(apps.begin() + i);
		displayMessage(appRemoved);
		return true;
	}

	else {
		displayMessage(appPermissionsRemove);
		return false;
	}
}

bool AppStore::updateApp(int devIndex) {

	string tempName;
	string tempDescription;
	string tempCategory;
	string tempStr;
	double tempPrice;

	UI::DisplayFrame("UPDATE APP");

	cout << "\nPlease enter the app name, <enter> to cancel:\n" << endl;
	getline(cin, tempName);

	if (tempName == "") {
		return true;
	}

	int i = appIndex(tempName);
	if (i != -1) {
		throw AppInexistente(tempName);
	}

	if (devIndex != -1) {
		if (apps[i]->getDeveloper() != developers[devIndex]) {
			displayMessage(appPermissionsUpdate);
			return false;
		}
	}

	cout << "\nPlease enter a new name, <enter> to skip:\n";
	getline(cin, tempStr);

	if (tempStr != "") {
		int j = appIndex(tempStr);
		if (j != -1) {
			throw JaExiste(tempStr);
		}
		apps[i]->setName(tempStr);
	}

	cout << "\nPlease enter a new category, <enter> to skip:\n";
	getline(cin, tempCategory);

	if (tempCategory != "") {
		apps[i]->setCategory(tempCategory);
	}

	cout << "\nPlease enter a new description, <enter> to skip:\n";
	getline(cin, tempDescription);

	if (tempDescription != "") {
		apps[i]->setDescription(tempDescription);
	}

	cout << "\nPlease enter a new price, (-1) to skip:\n";
	cin >> tempPrice;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		throw InvalidParameter("price");
	}
	if (tempPrice >= 0) {
		apps[i]->setPrice(tempPrice);
	}

	displayMessage(appUpdated);

	return true;
}

void AppStore::updateApp(App* app) {

	string tempDescription;
	string tempCategory;
	double tempPrice;

	UI::DisplayFrame("UPDATE APP");

	cout << "\nPlease enter a new category, <enter> to skip:\n";
	getline(cin, tempCategory);

	if (tempCategory != "") {
		app->setCategory(tempCategory);
	}

	cout << "\nPlease enter a new description, <enter> to skip:\n";
	getline(cin, tempDescription);

	if (tempDescription != "") {
		app->setDescription(tempDescription);
	}

	cout << "\nPlease enter a new price, (-1) to skip:\n";
	cin >> tempPrice;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		throw InvalidParameter("price");
	}

	if (tempPrice >= 0) {
		app->setPrice(tempPrice);
	}

	displayMessage(appUpdated);
}

const string developerCreated = "INFORMATION: developer created successfully.";
const string developerUpdated = "INFORMATION: developer information updated successfully.";
const string developerRemoved = "INFORMATION: developer deleted sucessfully.";

bool AppStore::Developer_create() {

	string tempName;
	string tempAddress;
	int tempNIF;
	string tempStr;
	int userChoice;

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
	} else {
		cout << "\nPlease enter the developer's name:\n";
	}

	getline(cin, tempName);

	if (tempName == "") {
		throw InvalidParameter("name");
	}

	int i = indexDeveloper(tempName);
	if (i != -1) {
		throw JaExiste(tempName);
	}

	if (userChoice == 2) {
		cout << "\nPlease enter the company's address:\n";
	} else {
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
	} else {
		Developer* temp = new Developer_Individual(tempName, tempAddress);
		developers.push_back(temp);
	}

	displayMessage(developerCreated);

	return true;
}

bool AppStore::Developer_update() {

	string tempName;
	string tempStr;

	UI::DisplayFrame("UPDATE DEVELOPER");

	cout << "\nPlease enter the developer/company name:\n";
	getline(cin, tempName);

	int i = indexDeveloper(tempName);
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

	int j = indexDeveloper(tempStr);
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

		if (tempStr.size() != 9) {
			throw InvalidParameter("NIF");
		}

		int tempNIF = atoi(tempStr.c_str());
		dynamic_cast<Developer_Empresa*>(developers[i])->setNIF(tempNIF);
	}

	displayMessage(developerUpdated);

	return true;
}

bool AppStore::Developer_delete() {

	string tempName;

	UI::DisplayFrame("DELETE DEVELOPER");

	cout << "Please enter the developer's name:" << endl;
	getline(cin, tempName);

	if (tempName == "") {
		throw InvalidParameter("name");
	}

	int i = indexDeveloper(tempName);
	if (i == -1) {
		throw DeveloperInexistente(tempName);
	}

	for (size_t j = 0; j < apps.size(); j++) {
		if (apps[j]->getDeveloper() == developers[i]) {
			apps.erase(apps.begin() + j);
			j--;
		}
	}

	developers.erase(developers.begin() + i);
	displayMessage(developerRemoved);

	return true;
}

void AppStore::App_print(int appIndex, int cliIndex) {
	while (true) {

		UI::DisplayFrame(to_upper(apps[appIndex]->getName()));
		cout << left << "\t\t" << "Developer: "
				<< apps[appIndex]->getDeveloper()->getName() << endl;
		cout << left << "\t\t" << "Category: " << setw(24)
				<< apps[appIndex]->getCategory() << setw(5)
				<< apps[appIndex]->getRating().to_string();
		cout << " (" << UI::FormatRating(apps[appIndex]->getRating().get())
				<< ")" << endl;
		cout << left << "\t\t" << "Price: $" << fixed << setw(28)
				<< setprecision(2) << apps[appIndex]->getPrice();
		cout << apps[appIndex]->getRating().r.size() << " ratings";
		cout << "\n\n\t\tDescription: " << endl;
		cout << "\t\t" << apps[appIndex]->getDescription() << endl << endl;

		UI::Display("<a> add to cart, <l> list comments");
		UI::Display("<c> comment, <r> rate");
		UI::Display("<b> go back");
		cout << "\nPlease choose an option: ";

		string tempStr;
		getline(cin, tempStr);

		if (tempStr.length() != 1 || !isalpha(tempStr[0])) {
			throw InvalidParameter("choice");
		}

		switch (tempStr[0]) {

		case 'a':

			GUIAddToCart(appIndex, cliIndex);
			system("pause");

			return;

		case 'r':

			GUIRateApp(appIndex);
			system("pause");

			break;

		case 'c':

			App_comment(appIndex, cliIndex);
			system("pause");

			break;

		case 'l':

			listComments(appIndex);
			system("pause");

			break;

		case 'b':

			return;

		default:

			throw InvalidParameter("choice");
		}
	}
}

void AppStore::GUIAddToCart(int appIndex, int cliIndex) {

	vector<App*> ownedApps = clientes[cliIndex]->getOwnedApps();
	vector<App*>::iterator it = ownedApps.begin();

	for (; it != ownedApps.end(); it++) {
		if ((*it) == apps[appIndex]) {
			throw JaExiste(apps[appIndex]->getName());
		}
	}

	cart.pushApp(apps[appIndex]);
	cout << "\nINFORMATION: " << apps[appIndex]->getName() << " added to cart.\n";
}

void AppStore::listComments(int appIndex) const {

	vector<Comentario> appComments = apps[appIndex]->getComments();
	ostringstream os;

	os << "COMMENTS (" << appComments.size() << ")";
	UI::DisplayFrame(os.str());
	cout << "\n";

	for (unsigned int i = 0; i < appComments.size(); i++) {
		cout << appComments[i].clientName << endl;
		cout << appComments[i].comment << endl << endl;
	}
}

bool operator<(const App &lhs, const App &rhs) {
	if (lhs.getDate() == rhs.getDate()) {
		if (lhs.getPrice() == rhs.getPrice()) {
			return !(lhs.getName() < rhs.getName());
		}
		return (lhs.getPrice() < rhs.getPrice());
	}
	return !(lhs.getDate() < rhs.getDate());
}

const string pendingAppUpdated = "INFORMATION: pending app information updated successfully.";

void AppStore::App_publish() {

	priority_queue<App*> tempQueue;

	while (!appsPendentes.empty()) {
		system("cls");

		App* a = appsPendentes.top();

		UI::DisplayFrame(to_upper(a->getName()));
		cout << left << "\t\t" << "Developer: " << a->getDeveloper()->getName()
				<< "\n";
		cout << left << "\t\t" << "Category: " << setw(24) << a->getCategory();
		cout << left << "\t\t" << "Price: $" << fixed << setw(28)
				<< setprecision(2) << a->getPrice();
		cout << "\n\n\t\tDescription: " << endl;
		cout << "\t\t" << a->getDescription() << "\n\n";
		UI::Display("<s> decide later, <e> edit");
		cout << "\nDo you want to publish this app? (y/n): ";

		string tempStr;
		getline(cin, tempStr);

		if (tempStr.size() != 1 || !isalpha(tempStr[0])) {
			throw InvalidParameter("choice");
		}

		if (tempStr[0] == 'e') {
			App* tempApp = appsPendentes.top();
			appsPendentes.pop();
			updateApp(1);
			appsPendentes.push(tempApp);
			displayMessage(pendingAppUpdated);

			break;
		} else if (tempStr[0] == 'y') {
			apps.push_back(appsPendentes.top());
			appsPendentes.pop();
		} else if (tempStr[0] == 's') {
			tempQueue.push(appsPendentes.top());
			appsPendentes.pop();
		} else if (tempStr[0] == 'n') {
			appsPendentes.pop();
		}

	}
	while (!tempQueue.empty()) {
		appsPendentes.push(tempQueue.top());
		tempQueue.pop();
	}
}

const string checkoutCartEmpty = "ERROR: checkout failed - your shopping cart is empty.";
const string checkoutEnoughFunds = "ERROR: checkout failed - you don't have enough funds.";
const string checkoutSuccessful = "INFORMATION: purchase successful - enjoy your new apps!";

void AppStore::App_checkout(int cliIndex, bool voucher) {

	vector<App*> boughtApps = cart.getApps();

	if (boughtApps.size() == 0) {
		displayMessage(checkoutCartEmpty);
		system("pause");
		return;
	}

	if (voucher) {
		cart.setPrice(cart.getPrice() * 0.95);
	}

	if (cart.getPrice() > clientes[cliIndex]->getSaldo()) {
		displayMessage(checkoutEnoughFunds);
		system("pause");
		return;
	}

	clientes[cliIndex]->setSaldo(clientes[cliIndex]->getSaldo() - cart.getPrice());

	if (voucher) {
		clientes[cliIndex]->setVoucher(false);
	}

	for (size_t i = 0; i < boughtApps.size(); i++) {

		Developer* devTemp = boughtApps[i]->getDeveloper();

		int j = indexDeveloper(devTemp->getName());
		if (j != -1) {
			developers[j]->sale(boughtApps[i]->getPrice());
		}

		clientes[cliIndex]->own(boughtApps[i]);
	}

	cart.setOwner(clientes[cliIndex]);
	vendas.push_back(cart);

	IOWriteClientes();
	IOWriteDevelopers();
	IOWriteSales();

	resetCart();
	displayMessage(checkoutSuccessful);

	system("pause");
}

void AppStore::Cliente_browse(int cliIndex) {

	string tempStr;

	while (true) {

		try {

			UI::DisplayFrame("BROWSE APPSTORE");
			listAppsByName();
			cout << endl << "Please choose an app, <0> to go back: ";
			getline(cin, tempStr);
			if (tempStr == "0") {
				return;
			}
			int i = appIndex(tempStr);
			if (i == -1) {
				throw AppInexistente(tempStr);
			}
			App_print(i, cliIndex);

		} catch (AppInexistente &e) {
			cout << e;
			system("pause");
		} catch (AppExisteNoCarrinho &e) {
			cout << e;
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

				UI::DisplayFrame("APPS OWNED");
				listAppsByCliente(cliIndex);
				system("pause");

				break;

			case 4:

				UI::DisplayFrame("CHECKOUT CART");
				GUICheckoutCart(cliIndex);

				break;

			case 5:

				UI::DisplayFrame("YOUR TRANSACTION HISTORY");
				listSalesByCliente(cliIndex);
				system("pause");

				break;

			case 6:

				GUIAddFunds(cliIndex);
				cout << "Funds sucessfully added to your account!" << endl;

				break;

			case 7:

				GUIActivateVoucher(cliIndex);
				system("pause");

				break;
			}

		} catch (InvalidParameter &ip) {
			cout << ip;
			system("pause");
		} catch (AppInexistente &e) {
			cout << e;
			system("pause");
		}
	}
}

const string checkoutRemoveFromCart = "INFORMATION: app removed from cart successfully!";

void AppStore::GUICheckoutCart(int cliIndex) {

	string tempStr;

	GUIAppsTable(cart.getApps());
	cout << endl;

	ostringstream os;
	os << "Total: " << UI::FormatPrice(cart.getPrice());

	if (clientes[cliIndex]->getVoucher()) {
		os << ", w/voucher: " << UI::FormatPrice(cart.getPrice() * 0.95);
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
		} else {
			if (clientes[cliIndex]->getVoucher()) {
				cout
						<< "Do you want to use your voucher with this purchase? (Y/n)";
				getline(cin, tempStr);
				if (tempStr == "n") {
					App_checkout(cliIndex, false);
				} else {
					App_checkout(cliIndex, true);
				}
			} else {
				App_checkout(cliIndex, false);
			}
		}
		break;
	}

	case 'r': {

		if (GUIRemoveFromCart())
		{
			displayMessage(checkoutRemoveFromCart);
		}

		system("pause");
		break;
	}
	}
}

bool AppStore::GUIRemoveFromCart() {

	string tempStr;

	cout << endl << "Please enter the name of the app to be removed: ";

	getline(cin, tempStr);

	vector<App*> cartApps = cart.getApps();

	for (size_t i = 0; i < cartApps.size(); i++) {
		if (cartApps[i]->getName() == tempStr) {
			return (cart.pullApp(cartApps[i]));
		}
	}

	return false;
}

const string voucherOwned = "INFORMATION: you already own a discount code.";
const string voucherActivated = "INFORMATION: code activated successfully.";
const string voucherInvalid = "ERROR: invalid code, please try again...";

void AppStore::GUIActivateVoucher(int cliIndex) {

	string tempStr;
	string voucherCode = "I-LOVE-APPS";

	cout << endl << "Please enter the discount code: ";

	getline(cin, tempStr);

	if (tempStr == voucherCode) {

		if (clientes[cliIndex]->getVoucher()) {
			displayMessage(voucherOwned);
		}

		else {
			clientes[cliIndex]->setVoucher(true);
			IOWriteClientes();
			displayMessage(voucherActivated);
		}
	}

	else {
		displayMessage(voucherInvalid);
	}
}

void AppStore::GUIAddFunds(int cliIndex) {

	string tempStr;
	int userChoice;

	cout << endl;
	cout << "(1) $5.00" << endl;
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
		clientes[cliIndex]->setSaldo(clientes[cliIndex]->getSaldo() + 5.00);
		break;
	case 2:
		clientes[cliIndex]->setSaldo(clientes[cliIndex]->getSaldo() + 10.00);
		break;
	case 3:
		clientes[cliIndex]->setSaldo(clientes[cliIndex]->getSaldo() + 20.00);
		break;
	case 4:
		clientes[cliIndex]->setSaldo(clientes[cliIndex]->getSaldo() + 50.00);
		break;
	}

	IOWriteClientes();
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
			} else {
				cout << " / Type: Individual";
			}
			cout << " / Balance: "
					<< UI::FormatPrice(developers[devIndex]->getBalance());
			cout << " / Apps: "
					<< UI::Format(developers[devIndex]->getNumApps(), 5);
			UI::DisplayFrame("DEVELOPER MENU");
			UI::DisplayMenuTop();
			UI::DisplayMenuItem(1, "Publish a new app");
			UI::DisplayMenuItem(2, "Update existing app");
			UI::DisplayMenuItem(3, "Remove existing app");
			UI::DisplayMenuTop();
			UI::DisplayMenuItem(4, "List published apps by name");
			UI::DisplayMenuItem(5, "List published apps by sales");
			UI::DisplayMenuItem(6, "List pending apps by name");
			UI::DisplayMenuItem(7, "List pending apps by priority");
			UI::DisplayMenuItem(8, "List removed apps by name");
			UI::DisplayMenuItem(9, "List removed apps by price");
			UI::DisplayMenuBottom();
			cout << endl << "Please select an option: ";
			getline(cin, tempStr);
			userChoice = atoi(tempStr.c_str());
			if (userChoice < 0 || userChoice > 4) {
				throw InvalidParameter("choice");
			}
			switch (userChoice) {
			case 1:
				createApp(devIndex);
				system("pause");
				break;
			case 2:
				updateApp(devIndex);
				system("pause");
				break;
			case 3:
				deleteApp(devIndex);
				system("pause");
				break;
			case 4:
				system("cls");
				UI::DisplayFrame("PUBLISHED APPS BY NAME");
				listAppsByDeveloper(developers[devIndex]);
				system("pause");
				break;
			case 5:
				system("cls");
				UI::DisplayFrame("PUBLISHED APPS BY SALES");
				listAppsByDeveloper(developers[devIndex]);
				system("pause");
				break;
			case 6:
				system("cls");
				UI::DisplayFrame("PENDING APPS BY NAME");
				listDevPendingByName(developers[devIndex]);
				system("pause");
				break;
			case 7:
				system("cls");
				UI::DisplayFrame("PENDING APPS BY PRIORITY");
				listDevPendingByPriority(developers[devIndex]);
				system("pause");
				break;
			case 8:
				system("cls");
				UI::DisplayFrame("REMOVED APPS BY NAME");
				listRemovedByName(devIndex);
				system("pause");
				break;
			case 9:
				system("cls");
				UI::DisplayFrame("REMOVED APPS BY PRICE");
				listRemovedByPrice(devIndex);
				system("pause");
				break;
			case 0:
				return;
			}
		} catch (InvalidParameter &ip) {
			cout << ip;
			system("pause");
		} catch (AppInexistente &e) {
			cout << e;
			system("pause");
		} catch (DeveloperInexistente &e) {
			cout << e;
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
			cout << nome;
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
				UI::DisplayFrame("SALES BY ID");
				listSalesByID();
				system("pause");
				break;
			}
			case 6:

				UI::DisplayFrame("SALES BY CUSTOMER");
				listSalesByCliente();
				system("pause");

				break;

			case 7:

				UI::DisplayFrame("SALES BY NO. APPS");
				listSalesByApps();
				system("pause");

				break;

			case 8:

				UI::DisplayFrame("SALES BY PRICE");
				listSalesByPrice();
				system("pause");

				break;

			}
		} catch (InvalidParameter &ip) {
			cout << ip;
			system("pause");
		}
	}
}

const string commentSuccessful = "INFORMATION: comment added successfully.";
const string commentExists = "ERROR: you have already published a comment for this app.";
const string appRated = "INFORMATION: thanks for rating our app!";

void AppStore::App_comment(int appIndex, int cliIndex) {

	string tempComment;
	cout << "Please enter your comment, <enter> to submit:\n";
	getline(cin, tempComment);

	if (apps[appIndex]->comentar(clientes[cliIndex]->getName(), tempComment)) {
		displayMessage(commentSuccessful);
	}

	else {
		displayMessage(commentExists);
	}
}

/**
 * I/O Functions
 */

void AppStore::GUIRateApp(int appIndex) {

	uint8_t tempRating;
	string tempStr;

	cout << "Rate this app: ";

	getline(cin, tempStr);
	tempRating = atoi(tempStr.c_str());

	if (tempRating == 0 || tempRating > 5) {
		throw InvalidParameter("rating");
	}

	apps[appIndex]->classificar(tempRating);
	displayMessage(appRated);
}

void AppStore::IOReadApps() {
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
		fin.read((char*) &tempPrice, sizeof(double));

		// chamar construtor com parametros
		App* newApp = new App(tempName, tempPrice, tempCategory,
				tempDescription);

		// procurar developer
		int devIndex = indexDeveloper(tempDev);
		if (devIndex != -1) {
			newApp->setDeveloper(developers[devIndex]);
		} else {
			newApp->setDeveloper(NULL);
		}

		// ler comentários e classificações para os vectores respectivos
		newApp->read(fin);

		// push para o vector
		apps.push_back(newApp);
	}
}

void AppStore::IOWriteApps() const {
	ofstream fout;
	fout.open("Apps.bin");
	if (!fout.is_open()) {
		throw FileIOException("Apps.bin");
	}
	for (size_t i = 0; i < apps.size(); i++) {
		fout << apps[i]->getName() << endl;
		fout << apps[i]->getDeveloper()->getName() << endl;
		fout << apps[i]->getCategory() << endl;
		fout << apps[i]->getDescription() << endl;
		double tempPrice = apps[i]->getPrice();
		fout.write((char*) &tempPrice, sizeof(double));
		apps[i]->write(fout);
	}
}

void AppStore::IOReadClientes() {
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
		fin.read((char*) &tempSaldo, sizeof(double));
		Cliente* tempCliente = new Cliente(tempName, tempSaldo);
		bool tempVoucher;
		fin.read((char*) &tempVoucher, sizeof(uint8_t));
		tempCliente->setVoucher(tempVoucher);
		uint32_t tempNumTransacoes;
		fin.read((char*) &tempNumTransacoes, sizeof(uint32_t));
		for (size_t i = 0; i < tempNumTransacoes; i++) {
			string tempAppName;
			getline(fin, tempAppName);
			int j = appIndex(tempAppName);
			if (j != -1) {
				tempCliente->own(apps[j]);
			}
		}
		clientes.push_back(tempCliente);
	}
}

void AppStore::IOWriteClientes() const {
	ofstream fout;
	fout.open("Clientes.bin");
	if (!fout.is_open()) {
		throw FileIOException("Clientes.bin");
	}
	for (size_t i = 0; i < clientes.size(); i++) {
		fout << clientes[i]->getName() << endl;
		double tempSaldo = clientes[i]->getSaldo();
		fout.write((char*) &tempSaldo, sizeof(double));
		bool tempVoucher = clientes[i]->getVoucher();
		fout.write((char*) &tempVoucher, sizeof(uint8_t));
		uint32_t tempNumTransacoes = clientes[i]->getNumApps();
		fout.write((char*) &tempNumTransacoes, sizeof(uint32_t));
		vector<App*> ownedApps = clientes[i]->getOwnedApps();
		for (size_t j = 0; j < tempNumTransacoes; j++) {
			fout << ownedApps[j]->getName() << endl;
		}
	}
}

void AppStore::IOReadDevelopers() {
	ifstream fin;
	fin.open("Developers.bin");
	if (!fin.is_open()) {
		throw FileIOException("Developers.bin");
	}
	while (!fin.eof()) {
		uint8_t tempType;
		fin.read((char*) &tempType, sizeof(uint8_t));
		switch (tempType) {
		case DEVELOPER_INDIVIDUAL: {
			Developer* tempDev = new Developer_Individual;
			if (tempDev->read(fin)) {
				developers.push_back(tempDev);
			}
			break;
		}
		case DEVELOPER_EMPRESA: {
			Developer* tempDev = new Developer_Empresa;
			if (tempDev->read(fin)) {
				developers.push_back(tempDev);
			}
			break;
		}
		}
	}
}

void AppStore::IOWriteDevelopers() const {
	ofstream fout;
	fout.open("Developers.bin");
	if (!fout.is_open()) {
		throw FileIOException("Developers.bin");
	}
	for (size_t i = 0; i < developers.size(); i++) {
		uint8_t tempType = developers[i]->getType();
		fout.write((char*) &tempType, sizeof(uint8_t));
		developers[i]->write(fout);
	}
}

void AppStore::IOReadSales() {
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
		int i = indexCliente(tempName);
		if (i == -1) {
			throw ClienteInexistente(tempName);
		}

		Cliente* tempCliente = clientes[i];

		double tempSaldo;
		fin.read((char*) &tempSaldo, sizeof(double));

		vector<App*> boughtApps;
		uint32_t numApps;
		fin.read((char*) &numApps, sizeof(uint32_t));

		for (size_t i = 0; i < numApps; i++) {
			string tempAppName;
			getline(fin, tempAppName);
			int j = appIndex(tempAppName);
			if (j != -1) {
				boughtApps.push_back(apps[j]);
			}
		}

		Sale tempSale = Sale(tempCliente, boughtApps, tempSaldo);
		vendas.push_back(tempSale);
	}
}

void AppStore::IOWriteSales() const {
	ofstream fout;
	fout.open("Vendas.bin", ios::binary);
	if (!fout.is_open()) {
		throw FileIOException("Vendas.bin");
	}
	for (size_t i = 0; i < vendas.size(); i++) {
		fout << vendas[i].getOwner()->getName() << "\n";
		double tempSaldo = vendas[i].getPrice();
		fout.write((char*) &tempSaldo, sizeof(double));
		uint32_t tempNumApps = vendas[i].getApps().size();
		fout.write((char*) &tempNumApps, sizeof(uint32_t));
		vector<App*> boughtApps = vendas[i].getApps();
		for (size_t j = 0; j < boughtApps.size(); j++) {
			fout << boughtApps[j]->getName() << "\n";
		}
	}
}

int AppStore::appIndex(string name) const {

	for (unsigned int i = 0; i < apps.size(); i++) {
		if (apps[i]->getName() == name) {
			return i;
		}
	}

	return -1;
}

int AppStore::indexCliente(string cliName) {

	for (unsigned int i = 0; i < clientes.size(); i++) {
		if (clientes[i]->getName() == cliName) {
			return i;
		}
	}

	return -1;
}

int AppStore::indexDeveloper(string devName) const {

	for (unsigned int i = 0; i < developers.size(); i++) {
		if (developers[i]->getName() == devName) {
			return i;
		}
	}

	return -1;
}

void AppStore::listTopNApps(int topN) const {

	BSTItrIn<App*> it(appsRanking);
	vector<App*> sortedVector;
	int count = 0;

	while (!it.isAtEnd() && count <= topN) {
		sortedVector.push_back(it.retrieve());
		it.advance();
		++count;
	}

	GUIAppsTable(sortedVector);
}

void AppStore::listTop10Apps() const {
	listTopNApps(10);
}

/**
 * BST Functions
 */

BST<App*> AppStore::BSTGetApps() const {
	return appsRanking;
}

bool AppStore::BSTRemoveApp(string appName) {

	BSTItrIn<App*> it(appsRanking);

	while (!it.isAtEnd()) {
		if (it.retrieve()->getName() == appName) {
			appsRanking.remove(it.retrieve());
			return true;
		}
	}

	return false;
}

bool AppStore::BSTRemoveApp(App* app) {
	appsRanking.remove(appsRanking.find(app));
}

bool AppStore::BSTInsertApp(App* app) {
	// find?
	appsRanking.insert(app);
}

/**
 *
 * Priority queue functions
 *
 */

vector<App*> AppStore::queueToVector() const {

	priority_queue<App*> tempQueue(appsPendentes);
	vector<App*> tempVector(tempQueue.size());

	for (size_t i = 0; i < tempVector.size(); i++) {
		tempVector[i] = &tempQueue.top();
		tempQueue.pop();
	}

	return tempVector;
}

void AppStore::queueInsertElement(App* elem) {
	appsPendentes.push(elem);
}

bool AppStore::queueRemoveElement(App* elem) {

	priority_queue<App*> tempQueue;

	if (appsPendentes.empty()) {
		return false;
	}

	while (!appsPendentes.empty()) {

		if (appsPendentes.top() != elem) {
			tempQueue.push(appsPendentes.top());
		}

		appsPendentes.pop();
	}

	while (!tempQueue.empty()) {
		appsPendentes.push(tempQueue.top());
		tempQueue.pop();
	}

	return true;
}

void AppStore::queueUpdateElement(App* o, App* n) {

	queueRemoveElement(o);
	queueInsertElement(n);
}

/**
 *
 * Hash table functions
 *
 */


bool tableInsertElement(hashDeveloper &ht, const App &elem) {

	pair<hashDeveloper::iterator, bool> r = ht.insert(elem);

	return r.second;
}

bool tableRemoveElement(hashDeveloper &ht, const App &elem) {

	hashDeveloper::iterator it = ht.find(elem);

	if (it != ht.end()) {
		ht.erase(it);
		return true;
	}

	return false;
}

bool tableUpdateElement(hashDeveloper &ht, const App &o, const App &n) {

	if (!tableRemoveElement(ht, o)) {
		return false;
	}

	if (!tableInsertElement(ht, n)) {
		return false;
	}

	return true;
}

vector<App> tableToVector(hashDeveloper &ht) {

	vector<App> sortedVector(ht.begin(), ht.end());
	return sortedVector;
}
