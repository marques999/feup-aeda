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

Cliente::Cliente(string n, double s) {
	this->name = n;
	this->saldo = s;
	this->voucher = false;
}
