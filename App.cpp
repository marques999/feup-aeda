/*!
* \file App.cpp
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
#include "Developer.h"

bool App::comentar(string cli, string c)
{
	for (size_t i = 0; i < comments.size(); i++)
	{
		if (comments[i].clientName == cli)
		{
			return false;
		}
	}

	Comentario tempComment;
	tempComment.clientName = cli;
	tempComment.comment = c;
	comments.push_back(tempComment);

	return true;
}

ostream& operator<<(ostream &os, const Comentario& c)
{
	os << c.clientName << endl << c.comment;
	return os;
}

void App::read(ifstream &fin)
{
	date.read(fin);
	rating.read(fin);

	uint32_t tempNumComments;
	fin.read((char*)&tempNumComments, sizeof(uint32_t));

	for (size_t i = 0; i < tempNumComments; i++)
	{
		Comentario tempComment;
		getline(fin, tempComment.clientName);
		getline(fin, tempComment.comment);
		comments.push_back(tempComment);
	}
}

void App::write(ofstream &fout) const
{
	// APP NAME
	fout << name << endl;
	// DEVELOPER NAME
	fout << dev->getName() << endl;
	// APP CATEGORY
	fout << category << endl;
	// APP DESCRIPTION
	fout << description << endl;
	// APP PRICE
	fout.write((char*) &price, sizeof(double));
	// APP SALES
	fout.write((char*) &sales, sizeof(unsigned));
	// APP PUBLISH DATE
	date.write(fout);
	// APP RATINGS
	rating.write(fout);
	// NUMBER OF COMMENTS
	uint32_t tempNumComments = comments.size();
	fout.write((char*)&tempNumComments, sizeof(uint32_t));
	// APP COMMENTS
	for (auto &x : comments)
	{
		fout << x.clientName << endl;
		fout << x.comment << endl;
	}
}


bool App::operator<(const App &ap2) const {
	if (this->getRating().get() == ap2.getRating().get()) {

		if (this->getPrice() == ap2.getPrice()) {
			return (this->getCategory() < ap2.getCategory());
		}

		return !(this->getPrice() < ap2.getPrice());
	}

	return !(this->getRating().get() < ap2.getRating().get());
}
