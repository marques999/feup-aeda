/*!
 * \file Cliente.cpp
 *
 * FEUP_AEDA1415_2MIEIC03_D
 * \author Carlos Soares
 * \author Diogo Marques
 * \author Fabio Carneiro
 *
 * \date Dezembro 2014
 *
 */

#include "App.h"
#include "Cliente.h"

void Cliente::write(ofstream &fout) {
	fout << name << endl;
	fout.write((char*) &saldo, sizeof(double));
	fout.write((char*) &voucher, sizeof(uint8_t));
	unsigned numApps = owned.size();
	fout.write((char*) &numApps, sizeof(unsigned));
	for (int i = 0; i < numApps; i++) {
		fout << owned[i]->getName() << endl;
	}
}
