/*!
* \file Sale.cpp
*
* FEUP_AEDA1415_2MIEIC03_D
* \author Carlos Soares
* \author Diogo Marques
* \author Fabio Carneiro
*
* \date Dezembro 2014
*
*/

#include "Sale.h"
#include "UI.h"
#include "Common.h"

void Sale::pushApp(App *a) {

	vector<App*>::const_iterator it = appsBought.begin();

	for (; it != appsBought.end(); it++) {
		if ((*it) == a) {
			throw JaExiste((*it)->getName());
		}
	}

	price += a->getPrice();
	appsBought.push_back(a);
}

void Sale::pullApp(App* a) {

	vector<App*>::iterator it = appsBought.begin();

	for (; it != appsBought.end(); it++) {
		if ((*it) == a) {
			price -= a->getPrice();
			appsBought.erase(it);
			cout << "\nINFORMATION: app removed from cart successfully!\n";
			return;
		}
	}

	throw AppInexistente(a->getName());
}
