/*!
* \file Sale.cpp
*
* FEUP_AEDA1415_2MIEIC03_D
* \author Carlos Soares
* \author Diogo Marques
* \author Fabio Carneiro
*
* \date Novembro 2014
*
*/

#include "Sale.h"
#include "UI.h"
#include "Common.h"

void Sale::pushApp(const App &a) {
	for (size_t i = 0; i < appsBought.size(); i++) {
		if (appsBought[i] == a) {
			throw JaExiste(a.getName());
		}
	}
	price += a.getPrice();
	appsBought.push_back(a);
}

void Sale::pullApp(const App &a) {
	for (size_t i = 0; i < appsBought.size(); i++) {
		if (appsBought[i] == a) {
			price -= a.getPrice();
			appsBought.erase(appsBought.begin() + i);
			cout << "\nINFORMATION: app removed from cart successfully!\n";
			return;
		}
	}
	throw AppInexistente(a.getName());
}
