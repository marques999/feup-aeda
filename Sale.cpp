/*!
* \file Sale.cpp
*
* FEUP_AEDA1415_2MIEIC03_D
* \author Carlos Soares
* \author Diogo Marques
* \author Fabio Carneiro
*
* \date Janeiro 2015
*
*/

#include "Sale.h"
#include "UI.h"
#include "Common.h"

bool Sale::push(App *a)
{
	for (auto &x : appsBought)
	{
		if (x == a)
		{
			throw AppExisteNoCarrinho(x->getName());
		}
	}

	price += a->getPrice();
	appsBought.push_back(a);

	return true;
}

bool Sale::pull(App* a)
{
	vector<App*>::iterator it = appsBought.begin();

	for (; it != appsBought.end(); it++)
	{
		if ((*it) == a)
		{
			price -= a->getPrice();
			appsBought.erase(it);
			return true;
		}
	}

	throw AppInexistente(a->getName());
}

void Sale::write(ofstream &fout) const
{
	unsigned numberApps = appsBought.size();

	fout << client->getName() << "\n";
	fout.write((char*) &price, sizeof(double));
	fout.write((char*) &numberApps, sizeof(unsigned));

	for (auto &x : appsBought)
	{
		fout << x->getName() << "\n";
	}
}
