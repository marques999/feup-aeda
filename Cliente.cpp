/*!
 * \file Cliente.cpp
 *
 * FEUP_AEDA1415_2MIEIC03_D
 * \author Carlos Soares
 * \author Diogo Marques
 * \author Fabio Carneiro
 *
 * \date Janeiro 2015
 *
 */

#include "App.h"
#include "Cliente.h"

void Cliente::write(ofstream &fout)
{
	// CUSTOMER NAME
	fout << name << endl;

	// CUSTOMER BALANCE
	fout.write((char*) &saldo, sizeof(double));

	// CUSTOMER VOUCHER
	fout.write((char*) &voucher, sizeof(uint8_t));

	// CUSTOMER NUMBER OF APPS
	unsigned numApps = owned.size();
	fout.write((char*) &numApps, sizeof(unsigned));

	// CUSTOMER OWNED APPS
	for (auto &x : owned)
	{
		fout << x->getName() << endl;
	}
}
