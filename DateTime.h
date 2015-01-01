/*!
 * \file DateTime.h
 *
 * FEUP_AEDA1415_2MIEIC03_D
 * \author Carlos Soares
 * \author Diogo Marques
 * \author Fabio Carneiro
 *
 * \date Dezembro 2014
 *
 */

#ifndef __DATETIME_H_
#define __DATETIME_H_

#include "Common.h"

struct tm tm_localtime();

void tm_write(struct tm timeinfo, ofstream &fout);
void tm_read(struct tm *timeinfo, ifstream &fin);

bool operator<(struct tm t1, struct tm t2);
bool operator==(struct tm t1, struct tm t2);

string tm_converttime(struct tm t1);
string tm_convertdate(struct tm t1);

ostream &operator<<(ostream& os, struct tm t1);

#endif /* __DATETIME_H_ */
