/*!
 * \file AppStore.cpp
 *
 * FEUP_AEDA1415_2MIEIC03_D
 * \author Carlos Soares
 * \author Diogo Marques
 * \author Fabio Carneiro
 *
 * \date Dezembro 2014
 *
 */

#include "AppStore.h"
#include "DateTime.h"

#include <algorithm>
#include <climits>

AppStore::AppStore() : appsRanking(new APP_NOT_FOUND) {
	resetCart();
}

AppStore::AppStore(string n) : nome(n), appsRanking(new APP_NOT_FOUND) {
	resetCart();
}

AppStore::~AppStore() {
}

void AppStore::resetCart() {
	cart = Sale();
	cart.setPrice(0.0);
	cart.setOwner(NULL);
}

unsigned int AppStore::getNumAppsDev(Developer* dev) const {
	return dev->getNumApps();
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
		fout.open("Developers.bin");
		fout.close();
		fout.open("Apps.bin");
		fout.close();
		fout.open("Removed.bin");
		fout.close();
		fout.open("Clientes.bin");
		fout.close();
		fout.open("Vendas.bin");
		fout.close();
	}

	fin.close();

	IOReadDevelopers();
	IOReadApps();
	IOReadRemovedApps();
	IOReadClientes();
	IOReadSales();

	return true;
}

bool AppStore::IOWriteStore() const {

	IOWriteDevelopers();
	IOWriteApps();
	IOWriteRemovedApps();
	IOWriteClientes();
	IOWriteSales();

	return true;
}

void AppStore::GUIDeveloperCRUD() {

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

				createDeveloper();
				IOWriteDevelopers();
				system("pause");
				break;

			case 2:

				updateDeveloper();
				IOWriteDevelopers();
				system("pause");
				break;

			case 3:

				deleteDeveloper();
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

vector<App*> AppStore::sortApps(const vector<App*> &v, AppSort s) const {

	vector<App*> sortedVector(v);

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

			for (j = i; j > 0 && tempApp->getRating().get() > sortedVector[j - 1]->getRating().get(); j--) {
				sortedVector[j] = sortedVector[j - 1];
			}
		}

		else if (s == APP_DATE) {

			for (j = i; j > 0 && tempApp->getDate() < sortedVector[j - 1]->getDate(); j--) {
				sortedVector[j] = sortedVector[j - 1];
			}
		}

		else if (s == APP_SALES) {

			for (j = i; j > 0 && tempApp->getSales() > sortedVector[j - 1]->getSales(); j--) {
				sortedVector[j] = sortedVector[j - 1];
			}
		}

		sortedVector[j] = tempApp;
	}

	return sortedVector;
}

vector<App> AppStore::sortApps(const vector<App> &v, AppSort s) const {

	vector<App> sortedVector(v);

	for (size_t i = 1; i < v.size(); i++) {

		App tempApp = sortedVector[i];
		size_t j = 0;

		if (s == APP_NAME) {

			for (j = i; j > 0 && tempApp.getName() < sortedVector[j - 1].getName(); j--) {
				sortedVector[j] = sortedVector[j - 1];
			}
		}

		else if (s == APP_PRICE) {

			for (j = i; j > 0 && tempApp.getPrice() < sortedVector[j - 1].getPrice(); j--) {
				sortedVector[j] = sortedVector[j - 1];
			}
		}

		else if (s == APP_RATING) {

			for (j = i; j > 0 && tempApp.getRating().get() > sortedVector[j - 1].getRating().get(); j--) {
				sortedVector[j] = sortedVector[j - 1];
			}
		}

		else if (s == APP_DATE) {

			for (j = i; j > 0 && tempApp.getDate() < sortedVector[j - 1].getDate(); j--) {
				sortedVector[j] = sortedVector[j - 1];
			}
		}

		else if (s == APP_SALES) {

			for (j = i; j > 0 && tempApp.getSales() > sortedVector[j - 1].getSales(); j--) {
				sortedVector[j] = sortedVector[j - 1];
			}
		}

		sortedVector[j] = tempApp;
	}

	return sortedVector;
}

vector<Cliente*> AppStore::sortClientes(vector<Cliente*> v, ClienteSort s) const {

	vector<Cliente*> sortedVector = v;

	for (size_t i = 1; i < v.size(); i++) {

		Cliente* tempCliente = sortedVector[i];
		size_t j = 0;

		if (s == CLIENTE_NAME) {

			for (j = i;	j > 0 && tempCliente->getName() < sortedVector[j - 1]->getName(); j--) {
				sortedVector[j] = sortedVector[j - 1];
			}
		}

		else if (s == CLIENTE_APPS) {

			for (j = i; j > 0 && tempCliente->getNumApps() > sortedVector[j - 1]->getNumApps(); j--) {
				sortedVector[j] = sortedVector[j - 1];
			}
		}

		else if (s == CLIENTE_SALDO) {

			for (j = i; j > 0 && tempCliente->getSaldo() > sortedVector[j - 1]->getSaldo(); j--) {
				sortedVector[j] = sortedVector[j - 1];
			}
		}

		sortedVector[j] = tempCliente;
	}

	return sortedVector;
}

vector<Sale> AppStore::sortSales(vector<Sale> v, SaleSort s) const {

	vector<Sale> sortedVector = v;

	for (size_t i = 1; i < v.size(); i++) {

		Sale tempSale = sortedVector[i];
		size_t j = 0;

		if (s == SALES_CLIENTE) {

			for (j = i; j > 0 && tempSale.getOwner()->getName() < sortedVector[j - 1].getOwner()->getName(); j--) {
				sortedVector[j] = sortedVector[j - 1];
			}
		}

		else if (s == SALES_PRICE) {

			for (j = i; j > 0 && tempSale.getPrice() > sortedVector[j - 1].getPrice(); j--) {
				sortedVector[j] = sortedVector[j - 1];
			}
		}

		else if (s == SALES_APPS) {

			for (j = i; j > 0 && tempSale.getApps().size() > sortedVector[j - 1].getApps().size(); j--) {
				sortedVector[j] = sortedVector[j - 1];
			}
		}

		sortedVector[j] = tempSale;
	}

	return sortedVector;
}

vector<Developer*> AppStore::sortDevelopers(const vector<Developer*> &v, DeveloperSort s) const {

	vector<Developer*> sortedVector = v;

	for (size_t i = 1; i < v.size(); i++) {

		Developer* tempDev = sortedVector[i];
		size_t j = 0;

		if (s == DEV_NAME) {

			for (j = i;	j > 0 && tempDev->getName() < sortedVector[j - 1]->getName(); j--) {
				sortedVector[j] = sortedVector[j - 1];
			}
		}

		else if (s == DEV_APPS) {

			for (j = i; j > 0 && tempDev->getNumApps() > sortedVector[j - 1]->getNumApps(); j--) {
				sortedVector[j] = sortedVector[j - 1];
			}
		}

		else if (s == DEV_SALES) {

			for (j = i; j > 0 && tempDev->getBalance() > sortedVector[j - 1]->getBalance(); j--) {
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

void AppStore::listDevPendingByName(const Developer* dev) const {
	GUIAppsTable(sortApps(listDeveloperPending(dev), APP_NAME));
}

void AppStore::listDevPendingByPrice(const Developer* dev) const {
	GUIAppsTable(sortApps(listDeveloperPending(dev), APP_PRICE));
}

void AppStore::listDevPendingByPriority(const Developer* dev) const {
	GUIAppsTable(listDeveloperPending(dev));
}

void AppStore::listPendingByDate() const {
	GUIAppsTable(sortApps(queueToVector(), APP_DATE));
}

void AppStore::listPendingByName() const {
	GUIAppsTable(sortApps(queueToVector(), APP_NAME));
}

void AppStore::listPendingByPrice() const {
	GUIAppsTable(sortApps(queueToVector(), APP_PRICE));
}

void AppStore::listPendingByPriority() const {
	GUIAppsTable(queueToVector());
}

///////////////////////////////
// LIST&SORT HASH TABLE
//////////////////////////////

vector<App> AppStore::listDeveloperRemoved(int devIndex) const
{
	vector<App> sortedVector;

	if (devIndex != -1)
	{
		hashDeveloper devTable = developers[devIndex]->getRemovedApps();
		hashDeveloper::const_iterator it = devTable.begin();
		for (; it != devTable.end(); it++)
		{
			sortedVector.push_back(*it);
		}
	}

	return sortedVector;
}

void AppStore::listRemovedByName(int devIndex) const
{
	vector<App> sortedVector = listDeveloperRemoved(devIndex);
	GUIAppsTable(sortApps(sortedVector,APP_NAME));
}

void AppStore::listRemovedByPrice(int devIndex) const
{
	vector<App> sortedVector = listDeveloperRemoved(devIndex);
	GUIAppsTable(sortApps(sortedVector, APP_PRICE));
}

void AppStore::listRemovedBySales(int devIndex) const
{
	vector<App> sortedVector = listDeveloperRemoved(devIndex);
	GUIAppsTable(sortApps(sortedVector, APP_SALES));
}

///////////////////////////////
// LIST&SORT SALES
//////////////////////////////

void AppStore::GUISalesTable(const vector<Sale> &s) const
{
	const int rowCount = 3;
	int tableLength[3] = { 32, 10, 10 };

	vector<string> tableLabel = { " Customer name", " No. Apps ", " Price" };
	vector<Sale>::const_iterator it = s.begin();

	UI::DisplayTable(rowCount, tableLabel, tableLength);

	for (; it != s.end(); it++)
	{
		vector<string> tableRow(rowCount);
		tableRow[0] =  it->getOwner()->getName();
		tableRow[1] = UI::Format(it->getApps().size(), 5);
		tableRow[2] = UI::FormatPrice(it->getPrice());
		UI::DisplayTableRow(rowCount, tableRow, tableLength);
	}
}

void AppStore::listSalesByCliente() const
{
	GUISalesTable(sortSales(vendas, SALES_CLIENTE));
}

void AppStore::listSalesByCliente(int cliIndex) const
{
	vector<Sale> sortedVector;
	vector<Sale>::const_iterator it = vendas.begin();

	for (; it != vendas.end(); it++)
	{
		if (it->getOwner() == clientes[cliIndex])
		{
			sortedVector.push_back(*it);
		}
	}

	GUISalesTable(sortedVector);
}

void AppStore::listSalesByID() const
{
	GUISalesTable(vendas);
}

void AppStore::listSalesByApps() const
{
	GUISalesTable(sortSales(vendas, SALES_APPS));
}

void AppStore::listSalesByPrice() const
{
	GUISalesTable(sortSales(vendas, SALES_PRICE));
}

///////////////////////////////
// LIST&SORT APPS
//////////////////////////////

void AppStore::GUIAppsTable(const vector<App*> &v) const {

	const int rowCount = 5;
	int tableLength[rowCount] = { 24, 16, 12, 8, 10 };

	vector<string> tableLabel = { " Name", " Developer", " Category", " Price", " Rating" };
	vector<App*>::const_iterator it = v.begin();

	UI::DisplayTable(rowCount, tableLabel, tableLength);

	for (; it != v.end(); it++) {

		vector<string> tableRow(rowCount);

		tableRow[0] = (*it)->getName();
		if ((*it)->getDeveloper() == NULL) {
			tableRow[1] = "Unknown";
		} else {
			tableRow[1] = (*it)->getDeveloper()->getName();
		}
		tableRow[2] = (*it)->getCategory();
		if ((*it)->getPrice() == 0.0) {
			tableRow[3] = "FREE";
		} else {
			tableRow[3] = UI::FormatPrice((*it)->getPrice());
		}
		if ((*it)->getRating().get() == 0.0) {
			tableRow[4] = "N/A";
		} else {
			tableRow[4] = UI::FormatRating((*it)->getRating().get());
		}

		UI::DisplayTableRow(rowCount, tableRow, tableLength);
	}
}

void AppStore::GUIAppsTable2(const vector<App*> &v) const {

	const int rowCount = 5;
	int tableLength[rowCount] = { 24, 16, 12, 8, 10 };

	vector<string> tableLabel = { " Name", " Developer", " Date ", " Price", " Rating" };
	vector<App*>::const_iterator it = v.begin();

	UI::DisplayTable(rowCount, tableLabel, tableLength);

	for (; it != v.end(); it++) {

		vector<string> tableRow(rowCount);

		tableRow[0] = (*it)->getName();
		if ((*it)->getDeveloper() == NULL) {
			tableRow[1] = "Unknown";
		} else {
			tableRow[1] = (*it)->getDeveloper()->getName();
		}
		tableRow[2] = tm_convertdate((*it)->getDate());
		if ((*it)->getPrice() == 0.0) {
			tableRow[3] = "FREE";
		} else {
			tableRow[3] = UI::FormatPrice((*it)->getPrice());
		}
		if ((*it)->getRating().get() == 0.0) {
			tableRow[4] = "N/A";
		} else {
			tableRow[4] = UI::FormatRating((*it)->getRating().get());
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
			tableRow[1] = "Unknown";
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
	GUIAppsTable2(sortApps(apps, APP_DATE));
}

void AppStore::listAppsByDateDescending() const {
	vector<App*> sortedVector = sortApps(apps, APP_DATE);
	reverse(sortedVector.begin(), sortedVector.end());
	GUIAppsTable2(sortedVector);
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

const string voucherNoCostumers = "\nINFORMATION: not enough customers on the database\n";

void AppStore::GUIFreeVoucher() {

	unsigned int numeroClientes = (unsigned int) round(clientes.size() * 0.1);

	if (numeroClientes == 0) {
		UI::DisplayMessage(voucherNoCostumers);
	}
	while (numeroClientes) {
		unsigned int j = rand() % clientes.size();
		if (clientes[j]->getVoucher() == false) {
			clientes[j]->setVoucher(true);
			numeroClientes--;
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

bool AppStore::createCliente() {

	string tempName;
	string tempStr;
	double tempSaldo = 0.0;

	UI::DisplayFrame("CREATE CUSTOMER");

	cout << "Please enter the customer's name:";
	getline(cin, tempName);

	if (tempName == "") {
		throw InvalidParameter("name");
	}

	int i = indexCliente(tempName);
	if (i != -1) {
		throw ClienteJaExiste(tempName);
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

	Cliente* novoCliente = new Cliente(tempName, tempSaldo);
	clientes.push_back(novoCliente);
	UI::DisplayMessage(customerCreated);

	return true;
}

bool AppStore::updateCliente() {

	string tempName;
	string tempStr;
	double tempSaldo;

	UI::DisplayFrame("UPDATE CUSTOMER");

	cout << "Please enter the customer's name, <enter> to cancel:" << endl;
	getline(cin, tempName);

	if (tempName == "") {
		return true;
	}

	int i = indexCliente(tempName);
	if (i == -1) {
		throw ClienteInexistente(tempName);
	}

	cout << "New name, <enter> to skip: ";
	getline(cin, tempStr);

	int j = indexCliente(tempStr);
	if (tempStr != "") {
		if (j != -1) {
			throw ClienteJaExiste(tempStr);
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
	UI::DisplayMessage(customerUpdated);

	return true;
}

bool AppStore::deleteCliente() {

	string tempName;

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
	UI::DisplayMessage(customerDeleted);

	return true;
}

void AppStore::GUIClienteCRUD() {

	int userChoice;
	string tempStr;

	while (true) {

		try {

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

			case 0:

				return;

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

void AppStore::GUISearchCategory() const {

	string tempCategory;

	cout << "\nPlease choose a category: ";
	getline(cin, tempCategory);

	if (tempCategory == "") {
		throw InvalidParameter("category");
	}

	UI::DisplayFrame("APPS BY CATEGORY");
	listAppsByCategory(tempCategory);
}

void AppStore::GUISearchDeveloper() const {

	string tempDeveloper;

	cout << "\nPlease enter the developer's name: ";
	getline(cin, tempDeveloper);

	if (tempDeveloper == "") {
		throw InvalidParameter("developer");
	}

	int i = indexDeveloper(tempDeveloper);
	if (i == -1) {
		throw DeveloperInexistente(tempDeveloper);
	}

	UI::DisplayFrame("APPS BY DEVELOPER");
	listAppsByDeveloper(developers[indexDeveloper(tempDeveloper)]);
}

void AppStore::GUISearchPrice() const {

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

	UI::DisplayFrame("APPS BY PRICE");
	listAppsByPrice(minTempPrice, maxTempPrice);
	cin.ignore(INT_MAX, '\n');
}

void AppStore::GUISearchRating() const {

	unsigned tempRating;

	cout << "\nPlease enter the rating: ";

	if (!(cin >> tempRating)) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		throw InvalidParameter("rating");
	}

	UI::DisplayFrame("APPS BY RATING");
	cin.ignore(INT_MAX, '\n');
	listAppsByRating(tempRating);
}

void AppStore::GUIListApps() const {

	int userChoice;
	string tempStr;

	while (true) {

		try {

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

			case 6:

				GUISearchCategory();
				system("pause");
				break;

			case 7:

				GUISearchDeveloper();
				system("pause");
				break;

			case 8:

				GUISearchPrice();
				system("pause");
				break;

			case 9:

				GUISearchRating();
				system("pause");
				break;

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

void AppStore::GUIAppCRUD() {

	int userChoice;
	string tempStr;

	while (true) {

		try {


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
				IOWriteApps();
				system("pause");
				break;

			case 2:

				updateApp(-1);
				IOWriteApps();
				system("pause");
				break;

			case 3:

				deleteApp(-1);
				IOWriteApps();
				system("pause");
				break;

			case 4:

				GUIFreeVoucher();
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
	int j;

	UI::DisplayFrame("CREATE APP");

	cout << "Please enter the app name:\n";
	getline(cin, tempName);

	if (tempName == "")
	{
		throw InvalidParameter("name");
	}

	int i = appIndex(tempName);
	if (i != -1) {
		throw AppJaExiste(tempName);
	}

	if (devIndex == -1)
	{
		cout << "\nPlease enter the developer name:\n";
		getline(cin, tempDeveloper);

		j = indexDeveloper(tempDeveloper);
		if (j == -1)
		{
			throw DeveloperInexistente(tempDeveloper);
		}
	}
	else
	{
		j = devIndex;
	}

	cout << "\nPlease enter the category:\n";
	getline(cin, tempCategory);

	cout << "\nPlease enter a description:\n";
	getline(cin, tempDescription);

	cout << "\nPlease enter the price:\n";
	cin >> tempPrice;

	if (cin.fail())
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		throw InvalidParameter("price");
	}

	if (tempPrice < 0)
	{
		throw InvalidParameter("price");
	}

	App* newApp = new App(tempName, tempPrice, tempCategory, tempDescription);

	newApp->setDeveloper(developers[j]);
	newApp->setDate(tm_localtime());

	if (devIndex == -1)
	{
		cin.ignore(INT_MAX, '\n');
		UI::DisplayMessage(appPublished);

		++(*developers[j]);
		appsRanking.insert(newApp);
		apps.push_back(newApp);
	}
	else
	{
		cin.ignore(INT_MAX, '\n');
		UI::DisplayMessage(appWaitingValidation);
		appsPendentes.push(newApp);
	}

	return true;
}

bool AppStore::deletePendingApp(int devIndex) {

	string tempName;

	UI::DisplayFrame("DELETE PENDING APP");

	cout << "\nPlease enter the app name:\n";
	getline(cin, tempName);

	App* tempApp = queueFindElement(tempName, devIndex);

	if (tempApp == APP_NOT_FOUND) {
		throw AppInexistente(tempName);
	}

	if (devIndex != -1) {
		if (developers[devIndex] != tempApp->getDeveloper()) {
			throw PermissoesInsuficientes("delete");
		}
	}

	queueRemoveElement(tempApp);
	UI::DisplayMessage(appRemoved);

	if (devIndex != -1) {
		developers[devIndex]->push(*tempApp);
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

	if (devIndex == -1)
	{
		int j = indexDeveloper(apps[i]->getDeveloper()->getName());
		if (j != -1)
		{
			--(*developers[j]);
			developers[j]->push(*apps[i]);
		}

		apps.erase(apps.begin() + i);
		BSTRemoveApp(apps[i]);
		UI::DisplayMessage(appRemoved);

		return true;
	}
	if (apps[i]->getDeveloper() == developers[devIndex])
	{
		--(*developers[devIndex]);
		developers[devIndex]->push(*apps[i]);

		apps.erase(apps.begin() + i);
		BSTRemoveApp(apps[i]);
		UI::DisplayMessage(appRemoved);

		return true;
	}
	else
	{
		UI::DisplayMessage(appPermissionsRemove);
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
			UI::DisplayMessage(appPermissionsUpdate);
			return false;
		}
	}

	cout << "\nPlease enter a new name, <enter> to skip:\n";
	getline(cin, tempStr);

	if (tempStr != "") {
		int j = appIndex(tempStr);
		if (j != -1) {
			throw AppJaExiste(tempStr);
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

	apps[i]->setDate(tm_localtime());
	UI::DisplayMessage(appUpdated);
	return true;
}

bool AppStore::updateRemovedApp(int devIndex) {

	string tempDescription;
	string tempCategory;
	string tempName;
	double tempPrice;

	UI::DisplayFrame("UPDATE REMOVED APP");

	cout << "\nPlease enter the app name, <enter> to cancel:\n" << endl;
	getline(cin, tempName);

	if (tempName == "") {
		return false;
	}

	hashDeveloper tempApps = developers[devIndex]->getRemovedApps();
	hashDeveloper::iterator it = tempApps.begin();

	for (; it != tempApps.end(); it++) {
		if (it->getName() == tempName) {
			break;
		}
	}

	if (it == tempApps.end()) {
		throw AppInexistente(tempName);
	}

	App tempApp = *it;

	developers[devIndex]->pop(*it);

	cout << "\nPlease enter a new category, <enter> to skip:\n";
	getline(cin, tempCategory);

	if (tempCategory != "") {
		tempApp.setCategory(tempCategory);
	}

	cout << "\nPlease enter a new description, <enter> to skip:\n";
	getline(cin, tempDescription);

	if (tempDescription != "") {
		tempApp.setDescription(tempDescription);
	}

	cout << "\nPlease enter a new price, (-1) to skip:\n";
	cin >> tempPrice;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		throw InvalidParameter("price");
	}

	if (tempPrice >= 0) {
		tempApp.setPrice(tempPrice);
	}

	tempApp.setDate(tm_localtime());
	developers[devIndex]->push(tempApp);
	UI::DisplayMessage(appUpdated);

	return true;
}

bool AppStore::updatePendingApp(int devIndex) {

	string tempDescription;
	string tempCategory;
	string tempName;
	double tempPrice;

	UI::DisplayFrame("UPDATE PENDING APP");

	cout << "\nPlease enter the app name, <enter> to cancel:\n" << endl;
	getline(cin, tempName);

	if (tempName == "") {
		return false;
	}

	App* tempApp = queueFindElement(tempName);

	if (tempApp == APP_NOT_FOUND) {
		throw AppInexistente(tempName);
	}

	if (devIndex != -1) {
		if (tempApp->getDeveloper() != developers[devIndex]) {
			throw PermissoesInsuficientes("update");
		}
	}

	queueRemoveElement(tempApp);

	cout << "\nPlease enter a new category, <enter> to skip:\n";
	getline(cin, tempCategory);

	if (tempCategory != "") {
		tempApp->setCategory(tempCategory);
	}

	cout << "\nPlease enter a new description, <enter> to skip:\n";
	getline(cin, tempDescription);

	if (tempDescription != "") {
		tempApp->setDescription(tempDescription);
	}

	cout << "\nPlease enter a new price, (-1) to skip:\n";
	cin >> tempPrice;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		throw InvalidParameter("price");
	}

	if (tempPrice >= 0) {
		tempApp->setPrice(tempPrice);
	}

	tempApp->setDate(tm_localtime());
	queueInsertElement(tempApp);
	UI::DisplayMessage(appUpdated);

	return true;
}

const string developerCreated = "INFORMATION: developer created successfully.";
const string developerUpdated = "INFORMATION: developer information updated successfully.";
const string developerRemoved = "INFORMATION: developer deleted sucessfully.";

bool AppStore::createDeveloper() {

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
		throw DeveloperJaExiste(tempName);
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
		Developer* novoDeveloper = new Developer_Empresa(tempName, tempAddress, tempNIF);
		developers.push_back(novoDeveloper);
	} else {
		Developer* novoDeveloper = new Developer_Individual(tempName, tempAddress);
		developers.push_back(novoDeveloper);
	}

	UI::DisplayMessage(developerCreated);
	return true;
}

bool AppStore::updateDeveloper() {

	string tempName;
	string tempStr;
	int tempNIF;

	UI::DisplayFrame("UPDATE DEVELOPER");

	cout << "\nPlease enter the developer/company name:\n";
	getline(cin, tempName);

	int i = indexDeveloper(tempName);
	if (i == -1) {
		throw DeveloperInexistente(tempName);
	}

	if (developers[i]->getType() == DEVELOPER_EMPRESA) {
		cout << "\nPlease enter a new company name, <enter> to skip:\n";
	} else {
		cout << "\nPlease enter a new name, <enter> to skip:\n";
	}

	getline(cin, tempStr);

	int j = indexDeveloper(tempStr);
	if (j != -1) {
		throw DeveloperJaExiste(tempStr);
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

		if (tempStr.size() > 0 && tempStr.size() < 9) {
			throw InvalidParameter("NIF");
		}

		if (tempStr != "") {
			tempNIF = atoi(tempStr.c_str());
			dynamic_cast<Developer_Empresa*>(developers[i])->setNIF(tempNIF);
		}
	}

	UI::DisplayMessage(developerUpdated);
	return true;
}

bool AppStore::deleteDeveloper() {

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
	UI::DisplayMessage(developerRemoved);

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
			throw AppExisteNoCarrinho(apps[appIndex]->getName());
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

void AppStore::publishRemovedApp(int devIndex) {

	string tempName;

	cout << "\nPlease enter the app name:\n";
	getline(cin, tempName);

	hashDeveloper tempApps = developers[devIndex]->getRemovedApps();
	hashDeveloper::const_iterator it = tempApps.begin();

	for (; it != tempApps.end(); it++) {
		if (it->getName() == tempName) {
			break;
		}
	}

	if (it == tempApps.end()) {
		throw AppInexistente(tempName);
	}

	App* newApp = new App();

	newApp->setName(it->getName());
	newApp->setPrice(it->getPrice());
	newApp->setDate(tm_localtime());
	newApp->setDescription(it->getDescription());
	newApp->setDeveloper(it->getDeveloper());
	newApp->setSales(0);

	developers[devIndex]->pop(*it);
	++(*developers[devIndex]);
	appsPendentes.push(newApp);
}


void AppStore::GUIPendingMenu() {

	priority_queue<App*> tempQueue;

	while (!appsPendentes.empty()) {

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

		if (tempStr[0] == 'e')
		{
			App* tempApp = appsPendentes.top();

			appsPendentes.pop();
			updateApp(tempApp);
			appsPendentes.push(tempApp);

			UI::DisplayMessage(pendingAppUpdated);
			break;
		}
		else if (tempStr[0] == 'y')
		{
			apps.push_back(appsPendentes.top());
			BSTInsertApp(appsPendentes.top());
			appsPendentes.pop();
		}
		else if (tempStr[0] == 's')
		{
			tempQueue.push(appsPendentes.top());
			appsPendentes.pop();
		}
		else if (tempStr[0] == 'n')
		{
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

void AppStore::App_checkout(int cliIndex, bool voucher)
{
	vector<App*> boughtApps = cart.getApps();
	int newPrice = cart.getPrice() * 0.95;

	if (boughtApps.empty())
	{
		UI::DisplayMessage(checkoutCartEmpty);
		return;
	}

	if (newPrice > clientes[cliIndex]->getSaldo())
	{
		UI::DisplayMessage(checkoutEnoughFunds);
		return;
	}

	if (voucher)
	{
		cart.setPrice(cart.getPrice() * 0.95);
		clientes[cliIndex]->setVoucher(false);
	}

	clientes[cliIndex]->setSaldo(clientes[cliIndex]->getSaldo() - cart.getPrice());

	for (int i = 0; i < boughtApps.size(); i++)
	{
		Developer* devTemp = boughtApps[i]->getDeveloper();

		int j = indexDeveloper(devTemp->getName());
		if (j != -1)
		{
			developers[j]->sale(boughtApps[i]->getPrice());
		}

		clientes[cliIndex]->own(boughtApps[i]);
		boughtApps[i]->sale();
	}

	cart.setOwner(clientes[cliIndex]);
	vendas.push_back(cart);

	IOWriteClientes();
	IOWriteDevelopers();
	IOWriteSales();
	resetCart();
	UI::DisplayMessage(checkoutSuccessful);
}

void AppStore::GUIBrowseApps(int cliIndex) {

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

bool AppStore::GUIClienteMenu(int cliIndex) {

	string tempStr;
	int userChoice;

	while (true) {

		try {

			GUIClienteBar(cliIndex);

			UI::DisplayFrame("CUSTOMER MENU");
			UI::DisplayMenuTop();
			UI::DisplayMenuItem(1, "Purchase app");
			UI::DisplayMenuItem(2, "List apps");
			UI::DisplayMenuItem(3, "List top 10");
			UI::DisplayMenuTop();
			UI::DisplayMenuItem(4, "Bought apps");
			UI::DisplayMenuItem(5, "Checkout cart");
			UI::DisplayMenuItem(6, "Transaction history");
			UI::DisplayMenuTop();
			UI::DisplayMenuItem(7, "Add funds");
			UI::DisplayMenuItem(8, "Activate voucher");
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

				GUIBrowseApps(cliIndex);
				break;

			case 2:

				GUIListApps();
				break;

			case 3:

				UI::DisplayFrame("TOP 10 APPS");
				listTop10Apps();
				system("pause");
				break;

			case 4:

				UI::DisplayFrame("APPS OWNED");
				listAppsByCliente(cliIndex);
				system("pause");

				break;

			case 5:

				UI::DisplayFrame("CHECKOUT CART");
				GUICheckoutCart(cliIndex);
				break;

			case 6:

				UI::DisplayFrame("YOUR TRANSACTION HISTORY");
				listSalesByCliente(cliIndex);
				system("pause");
				break;

			case 7:

				GUIAddFunds(cliIndex);
				cout << "Funds sucessfully added to your account!" << endl;
				break;

			case 8:

				GUIActivateVoucher(cliIndex);
				system("pause");
				break;
			}

		} catch (InvalidParameter &ip) {
			cout << ip;
			system("pause");
		} catch (AppExisteNoCarrinho &e) {
			cout << e;
			system("pause");
		} catch (AppInexistente &e) {
			cout << e;
			system("pause");
		}
	}
}

const string checkoutRemoveFromCart = "INFORMATION: app removed from cart successfully!";

void AppStore::GUIRemovedApps(int devIndex) {

	string tempStr;
	int userChoice;

	while (true) {

		try {

			UI::DisplayFrame("REMOVED APPS MENU");
			UI::DisplayMenuTop();
			UI::DisplayMenuItem(1, "Publish removed app");
			UI::DisplayMenuItem(2, "Update removed app");
			UI::DisplayMenuTop();
			UI::DisplayMenuItem(3, "List removed apps by name");
			UI::DisplayMenuItem(4, "List removed apps by price");
			UI::DisplayMenuItem(5, "List removed apps by sales");
			UI::DisplayMenuBottom();

			cout << "\nPlease select an option: ";
			getline(cin, tempStr);
			userChoice = atoi(tempStr.c_str());

			if (userChoice < 0 || userChoice > 5) {
				throw InvalidParameter("choice");
			}

			switch (userChoice) {

			case 0:

				return;

			case 1:
				publishRemovedApp(devIndex);
				system("pause");
				break;

			case 2:

				updateRemovedApp(devIndex);
				system("pause");
				break;

			case 3:

				UI::DisplayFrame("REMOVED APPS BY NAME");
				listRemovedByName(devIndex);
				system("pause");
				break;

			case 4:

				UI::DisplayFrame("REMOVED APPS BY PRICE");
				listRemovedByPrice(devIndex);
				system("pause");
				break;

			case 5:

				UI::DisplayFrame("REMOVED APPS BY SALES");
				listRemovedBySales(devIndex);
				system("pause");
				break;
			}

		} catch (InvalidParameter &ip) {
			cout << ip;
			system("pause");
		} catch (AppExisteNoCarrinho &e) {
			cout << e;
			system("pause");
		} catch (AppInexistente &e) {
			cout << e;
			system("pause");
		}
	}
}

void AppStore::GUIListPending() const {
	string tempStr;
	int userChoice;

	while (true) {

		UI::DisplayFrame("LIST PENDING APPS");
		UI::DisplayMenuTop();
		UI::DisplayMenuItem(1, "List pending apps by name");
		UI::DisplayMenuItem(2, "List pending apps by date");
		UI::DisplayMenuItem(3, "List pending apps by price");
		UI::DisplayMenuItem(4, "List pending apps by priority");
		UI::DisplayMenuBottom();

		cout << "\nPlease select an option: ";
		getline(cin, tempStr);
		userChoice = atoi(tempStr.c_str());

		if (userChoice < 0 || userChoice > 7) {
			throw InvalidParameter("choice");
		}

		switch (userChoice) {

		case 0:

			return;

		case 1:

			UI::DisplayFrame("PENDING APPS BY NAME");
			listPendingByName();
			system("pause");
			break;

		case 2:

			UI::DisplayFrame("PENDING APPS BY DATE");
			listPendingByDate();
			system("pause");
			break;

		case 4:

			UI::DisplayFrame("PENDING APPS BY PRICE");
			listPendingByPrice();
			system("pause");
			break;

		case 3:

			UI::DisplayFrame("PENDING APPS BY PRIORITY");
			listPendingByPriority();
			system("pause");
			break;
		}
	}
}

void AppStore::GUIDeveloperPending(int devIndex) {

	string tempStr;
	int userChoice;

	while (true) {

		try {

			UI::DisplayFrame("PENDING APPS MENU");
			UI::DisplayMenuTop();
			UI::DisplayMenuItem(1, "Update pending app");
			UI::DisplayMenuItem(2, "Remove pending app");
			UI::DisplayMenuTop();
			UI::DisplayMenuItem(3, "List pending apps by name");
			UI::DisplayMenuItem(4, "List pending apps by priority");
			UI::DisplayMenuItem(5, "List pending apps by price");
			UI::DisplayMenuBottom();

			cout << "\nPlease select an option: ";
			getline(cin, tempStr);
			userChoice = atoi(tempStr.c_str());

			if (userChoice < 0 || userChoice > 5) {
				throw InvalidParameter("choice");
			}

			switch (userChoice) {

			case 0:

				return;

			case 1:

				updatePendingApp(devIndex);
				system("pause");
				break;

			case 2:

				deletePendingApp(devIndex);
				system("pause");
				break;

			case 3:

				UI::DisplayFrame("PENDING APPS BY NAME");
				listDevPendingByName(developers[devIndex]);
				system("pause");
				break;

			case 4:

				UI::DisplayFrame("PENDING APPS BY PRICE");
				listDevPendingByPrice(developers[devIndex]);
				system("pause");
				break;

			case 5:

				UI::DisplayFrame("PENDING APPS BY PRIORITY");
				listDevPendingByPriority(developers[devIndex]);
				system("pause");
				break;
			}

		} catch (InvalidParameter &ip) {
			cout << ip;
			system("pause");
		} catch (AppExisteNoCarrinho &e) {
			cout << e;
			system("pause");
		} catch (AppInexistente &e) {
			cout << e;
			system("pause");
		}
	}
}

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
			system("pause");
		}
		break;
	}

	case 'r': {

		if (GUIRemoveFromCart())
		{
			UI::DisplayMessage(checkoutRemoveFromCart);
		}

		system("pause");
		break;
	}
	}
}

bool AppStore::GUIRemoveFromCart() {

	string appName;

	cout << "\nPlease enter the name of the app to be removed: ";

	getline(cin, appName);

	vector<App*> cartApps = cart.getApps();

	for (size_t i = 0; i < cartApps.size(); i++) {
		if (cartApps[i]->getName() == appName) {
			return (cart.pullApp(cartApps[i]));
		}
	}

	throw AppInexistente(appName);
}

const string voucherOwned = "INFORMATION: you already own a discount code.";
const string voucherActivated = "INFORMATION: code activated successfully.";
const string voucherInvalid = "ERROR: invalid code, please try again...";
const string voucherCode = "I-LOVE-APPS";

void AppStore::GUIActivateVoucher(int cliIndex) {

	string tempStr;

	cout << endl << "Please enter the discount code: ";

	getline(cin, tempStr);

	if (tempStr == voucherCode) {

		if (clientes[cliIndex]->getVoucher()) {
			UI::DisplayMessage(voucherOwned);
		}

		else {
			clientes[cliIndex]->setVoucher(true);
			IOWriteClientes();
			UI::DisplayMessage(voucherActivated);
		}
	}

	else {
		UI::DisplayMessage(voucherInvalid);
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

void AppStore::GUIAdminBar() const {

	system("cls");

	cout << nome;
	cout << " / Apps: " << apps.size();
	cout << " / Developers: " << developers.size();
	cout << " / Customers: " << clientes.size() << endl;
}

void AppStore::GUIClienteBar(int cliIndex) const {

	system("cls");

	cout << "Customer: " << clientes[cliIndex]->getName();
	cout << " / Balance: " << UI::FormatPrice(clientes[cliIndex]->getSaldo());
	cout << " / Apps: " << clientes[cliIndex]->getNumApps();
	cout << " / Voucher: " << (clientes[cliIndex]->getVoucher() ? "Yes" : "No") << endl;
}

void AppStore::GUIDeveloperBar(int devIndex) const {

	system("cls");

	cout << "Developer: " << developers[devIndex]->getName();

	if (developers[devIndex]->getType() == DEVELOPER_EMPRESA)
	{
		cout << " / Type: Company";
	}
	else
	{
		cout << " / Type: Individual";
	}

	cout << " / Balance: " << UI::FormatPrice(developers[devIndex]->getBalance());
	cout << " / Apps: " << UI::Format(developers[devIndex]->getNumApps(), 5);
}


void AppStore::GUIDeveloperMenu(int devIndex) {

	string tempStr;
	int userChoice;

	while (true) {

		try {

			GUIDeveloperBar(devIndex);

			UI::DisplayFrame("DEVELOPER MENU");
			UI::DisplayMenuTop();
			UI::DisplayMenuItem(1, "Publish a new app");
			UI::DisplayMenuItem(2, "Update existing app");
			UI::DisplayMenuItem(3, "Remove existing app");
			UI::DisplayMenuTop();
			UI::DisplayMenuItem(4, "Removed apps");
			UI::DisplayMenuItem(5, "Pending apps");
			UI::DisplayMenuTop();
			UI::DisplayMenuItem(6, "List published apps by name");
			UI::DisplayMenuItem(7, "List published apps by sales");
			UI::DisplayMenuBottom();

			cout << endl << "Please select an option: ";
			getline(cin, tempStr);
			userChoice = atoi(tempStr.c_str());

			if (userChoice < 0 || userChoice > 4) {
				throw InvalidParameter("choice");
			}

			switch (userChoice) {

			case 0:

				return;

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

				GUIRemovedApps(devIndex);
				break;

			case 5:

				GUIDeveloperPending(devIndex);
				break;

			case 6:

				UI::DisplayFrame("PUBLISHED APPS BY NAME");
				listAppsByDeveloper(developers[devIndex]);
				system("pause");
				break;

			case 7:

				UI::DisplayFrame("PUBLISHED APPS BY SALES");
				//TODO::listAppsBySalesDeveloper(developers[devIndex]);
				system("pause");
				break;
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

void AppStore::GUIListSales() const
{
	string tempStr;
	int userChoice;

	while (true)
	{
		UI::DisplayFrame("SALES MENU");

		UI::DisplayMenuItem(1, "List sales by ID");
		UI::DisplayMenuItem(2, "List sales by customer");
		UI::DisplayMenuItem(3, "List sales by apps");
		UI::DisplayMenuItem(4, "List sales by price");

		cout << "Please select an option: ";

		getline(cin, tempStr);
		userChoice = atoi(tempStr.c_str());

		if (userChoice < 0 || userChoice > 8)
		{
			throw InvalidParameter("choice");
		}

		switch (userChoice)
		{

		case 0:

			return;

		case 1:

			UI::DisplayFrame("SALES BY ID");
			listSalesByID();
			system("pause");
			break;

		case 2:

			UI::DisplayFrame("SALES BY CUSTOMER");
			listSalesByCliente();
			system("pause");
			break;

		case 3:

			UI::DisplayFrame("SALES BY NO. APPS");
			listSalesByApps();
			system("pause");
			break;

		case 4:

			UI::DisplayFrame("SALES BY PRICE");
			listSalesByPrice();
			system("pause");
			break;
		}

	}
}

void AppStore::GUIAdminMenu() {

	string tempStr;
	int userChoice;

	while (true) {

		try {

			GUIAdminBar();

			UI::DisplayFrame("ADMINISTRATION MENU");
			UI::DisplayMenuTop();
			UI::DisplayMenuItem(1, "Manage apps");
			UI::DisplayMenuItem(2, "Manage developers");
			UI::DisplayMenuItem(3, "Manage customers");
			UI::DisplayMenuTop();
			UI::DisplayMenuItem(4, "Validate submitted apps");
			UI::DisplayMenuTop();
			UI::DisplayMenuItem(5, "List top 10");
			UI::DisplayMenuItem(6, "List apps");
			UI::DisplayMenuItem(7, "List pending apps");
			UI::DisplayMenuItem(8, "List sales");
			UI::DisplayMenuBottom();

			cout << "Please select an option: ";

			getline(cin, tempStr);
			userChoice = atoi(tempStr.c_str());

			if (userChoice < 0 || userChoice > 8) {
				throw InvalidParameter("choice");
			}

			switch (userChoice) {

			case 0:

				return;

			case 1:

				GUIAppCRUD();
				break;

			case 2:

				GUIDeveloperCRUD();
				break;

			case 3:

				GUIClienteCRUD();
				break;

			case 4:

				GUIPendingMenu();
				break;

			case 5:

				UI::DisplayFrame("TOP 10 APPS");
				listTop10Apps();
				system("pause");
				break;

			case 6:

				GUIListApps();
				break;

			case 7:

				GUIListPending();
				break;

			case 8:

				GUIListSales();
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
		UI::DisplayMessage(commentSuccessful);
	} else {
		UI::DisplayMessage(commentExists);
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
	UI::DisplayMessage(appRated);
}

/**
 * READ APPS
 */
void AppStore::IOReadApps()
{
	ifstream fin;

	fin.open("Apps.bin");

	if (!fin.is_open())
	{
		throw FileIOException("Apps.bin");
	}

	while (!fin.eof() && IOReadApp(fin))
	{
	}
}

void AppStore::IOReadRemovedApps()
{
	ifstream fin;

	fin.open("Removed.bin");

	if (!fin.is_open())
	{
		throw FileIOException("Removed.bin");
	}

	while (!fin.eof() && IOReadRemovedApp(fin))
	{
	}
}

bool AppStore::IOReadApp(ifstream &fin)
{
	// APP NAME
	string tempName;
	getline(fin, tempName);

	if (tempName == "")
	{
		return false;
	}

	// DEVELOPER NAME
	string tempDev;
	getline(fin, tempDev);
	// APP CATEGORY
	string tempCategory;
	getline(fin, tempCategory);
	// APP DESCRIPTION
	string tempDescription;
	getline(fin, tempDescription);
	// APP PRICE
	double tempPrice;
	fin.read((char*) &tempPrice, sizeof(double));
	// APP SALES
	unsigned tempSales;
	fin.read((char*) &tempSales, sizeof(unsigned));
	// APP PUBLISH DATE
	struct tm tempDate;
	tm_read(&tempDate, fin);
	// APP CONSTRUCTOR
	App* newApp = new App(tempName, tempPrice, tempCategory, tempDescription);
	// FIND DEVELOPER
	int devIndex = indexDeveloper(tempDev);
	if (devIndex != -1)
	{
		newApp->setDeveloper(developers[devIndex]);
		++(*developers[devIndex]);
	}
	else
	{
		newApp->setDeveloper(NULL);
	}
	// READ COMMENTS AND RATINGS
	newApp->read(fin);
	// READ PENDING STATUS
	uint8_t tempPending;
	fin.read((char*) &tempPending, sizeof(uint8_t));
	// PUSH NEW APP
	if (tempPending)
	{
		appsPendentes.push(newApp);
	}
	else
	{
		apps.push_back(newApp);
		appsRanking.insert(newApp);
	}
	return true;
}

bool AppStore::IOReadRemovedApp(ifstream &fin)
{
	// APP NAME
	string tempName;
	getline(fin, tempName);

	if (tempName == "")
	{
		return false;
	}

	// DEVELOPER NAME
	string tempDev;
	getline(fin, tempDev);
	// APP CATEGORY
	string tempCategory;
	getline(fin, tempCategory);
	// APP DESCRIPTION
	string tempDescription;
	getline(fin, tempDescription);
	// APP PRICE
	double tempPrice;
	fin.read((char*) &tempPrice, sizeof(double));
	// APP SALES
	unsigned tempSales;
	fin.read((char*) &tempSales, sizeof(unsigned));
	// APP PUBLISH DATE
	struct tm tempDate;
	tm_read(&tempDate, fin);
	// APP CONSTRUCTOR
	App newApp(tempName, tempPrice, tempCategory, tempDescription);
	// READ COMMENTS AND RATINGS
	newApp.read(fin);
	// FIND DEVELOPER AND PUSH APP
	int devIndex = indexDeveloper(tempDev);
	if (devIndex != -1)
	{
		newApp.setDeveloper(developers[devIndex]);
		developers[devIndex]->push(newApp);
	}
	return true;
}

/**
 * WRITE APPS
 */

void AppStore::IOWriteApps() const {

	ofstream fout;
	uint8_t tempPending;
	vector<App*> pendingApps = queueToVector();
	vector<App*>::const_iterator it;

	fout.open("Apps.bin");

	if (!fout.is_open()) {
		throw FileIOException("Apps.bin");
	}

	tempPending = 0;

	for (it = apps.begin(); it != apps.end(); it++) {
		(*it)->write(fout);
		fout.write((char*) &tempPending, sizeof(uint8_t));
	}

	tempPending = 1;

	for (it = pendingApps.begin(); it != pendingApps.end(); it++) {
		(*it)->write(fout);
		fout.write((char*) &tempPending, sizeof(uint8_t));
	}
}

void AppStore::IOWriteRemovedApps() const {

	ofstream fout;

	fout.open("Removed.bin");

	if (!fout.is_open()) {
		throw FileIOException("Removed.bin");
	}

	vector<Developer*>::const_iterator it = developers.begin();

	for (; it != developers.end(); it++) {

		hashDeveloper removedApps = (*it)->getRemovedApps();
		hashDeveloper::const_iterator itt = removedApps.begin();

		for (; itt != removedApps.end(); itt++) {
			itt->write(fout);
		}
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
		clientes[i]->write(fout);
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
		IOWriteDeveloper(developers[i], fout);
	}
}

void AppStore::IOWriteDeveloper(Developer* dev, ofstream &fout) const {

	uint8_t developerType = dev->getType();
	hashDeveloper developerRemovedApps = dev->getRemovedApps();
	hashDeveloper::const_iterator it = developerRemovedApps.begin();

	fout.write((char*) &developerType, sizeof(uint8_t));

	dev->write(fout);

	for (; it != developerRemovedApps.end(); it++) {
		it->write(fout);
	}

}

void AppStore::IOReadSales() {

	ifstream fin;

	fin.open("Vendas.bin", ios::binary);

	if (!fin.is_open()) {
		throw FileIOException("Vendas.bin");
	}

	while (!fin.eof()) {
		IOReadSale(fin);
	}
}

void AppStore::IOReadSale(ifstream &fin) {

	string tempName;
	getline(fin, tempName);

	if (tempName == "") {
		return;
	}

	int i = indexCliente(tempName);
	if (i == -1) {
		throw ClienteInexistente(tempName);
	}

	double tempSaldo;
	fin.read((char*) &tempSaldo, sizeof(double));

	uint32_t numApps;
	fin.read((char*) &numApps, sizeof(uint32_t));

	vector<App*> boughtApps;
	for (int k = 0; k < numApps; k++) {

		string tempAppName;
		getline(fin, tempAppName);

		int j = appIndex(tempAppName);
		if (j != -1) {
			boughtApps.push_back(apps[j]);
		}
	}

	Sale tempSale = Sale(clientes[i], boughtApps, tempSaldo);
	vendas.push_back(tempSale);
}

void AppStore::IOWriteSales() const {

	ofstream fout;

	fout.open("Vendas.bin", ios::binary);

	if (!fout.is_open()) {
		throw FileIOException("Vendas.bin");
	}

	for (size_t i = 0; i < vendas.size(); i++) {
		IOWriteSale(vendas[i], fout);
	}
}

void AppStore::IOWriteSale(const Sale &sale, ofstream& fout) const {

	double saleBalance = sale.getPrice();
	uint32_t saleNumApps = sale.getApps().size();
	vector<App*> saleApps = sale.getApps();

	fout << sale.getOwner()->getName() << "\n";
	fout.write((char*) &saleBalance, sizeof(double));
	fout.write((char*) &saleNumApps, sizeof(uint32_t));

	for (size_t j = 0; j < saleApps.size(); j++) {
		fout << saleApps[j]->getName() << "\n";
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
	return true;
}

bool AppStore::BSTInsertApp(App* app) {
	// find?
	appsRanking.insert(app);
	return true;
}

/**
 *
 * Priority queue functions
 *
 */

vector<App*> AppStore::queueToVector() const {

	priority_queue<App*> tempQueue(appsPendentes);
	vector<App*> tempVector;

	while (!tempQueue.empty()) {
		tempVector.push_back(tempQueue.top());
		tempQueue.pop();
	}

	return tempVector;
}

void AppStore::queueInsertElement(App* elem) {
	appsPendentes.push(elem);
}

bool AppStore::queueRemoveElement(string name) {

	priority_queue<App*> tempQueue;

	if (appsPendentes.empty()) {
		return false;
	}

	while (!appsPendentes.empty()) {

		if (appsPendentes.top()->getName() != name) {
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

App* AppStore::queueFindElement(string name, int devIndex) const {

	priority_queue<App*> tempQueue(appsPendentes);

	if (appsPendentes.empty()) {
		return false;
	}

	while (!tempQueue.empty()) {

		App* tempApp = tempQueue.top();
		tempQueue.pop();

		if (tempApp->getName() == name) {
			if (tempApp->getDeveloper() == developers[devIndex]) {
				return tempApp;
			}
		}
	}

	return APP_NOT_FOUND;
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

App* AppStore::queueFindElement(string name) const {

	priority_queue<App*> tempQueue(appsPendentes);

	if (appsPendentes.empty()) {
		return false;
	}

	while (!tempQueue.empty()) {

		App* tempApp = tempQueue.top();
		tempQueue.pop();

		if (tempApp->getName() == name) {
				return tempApp;
			}

	}

	return (new APP_NOT_FOUND);
}


App tableRetrieveElement(hashDeveloper &ht, string name) {

	App appProcurada = App(name, 0, "", "");
	hashDeveloper::iterator it = ht.find(appProcurada);

	if (it != ht.end()) {
		return *it;
	}

	throw AppInexistente(name);
	return APP_NOT_FOUND;
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
