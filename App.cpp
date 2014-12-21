/*!
* \file App.cpp
*
* FEUP_AEDA1415_2MIEIC03_D
* \author Carlos Soares
* \author Diogo Marques
* \author Fabio Carneiro
* \author Joao Santos
*
* \date Novembro 2014
*
*/

#include "App.h"
#include "Developer.h"

bool App::comentar(string cli, string c) {
	for (size_t i = 0; i < comments.size(); i++) {
		if (comments[i].clientName == cli) {
			return false;
		}
	}
	Comentario tempComment;
	tempComment.clientName = cli;
	tempComment.comment = c;
	comments.push_back(tempComment);
	return true;
}

ostream& operator<<(ostream &os, const Comentario& c) {
	os << c.clientName << endl << c.comment;
	return os;
}

void App::read(ifstream &fin) {
	rating.read(fin);
	uint32_t tempNumComments;
	fin.read((char*)&tempNumComments, sizeof(uint32_t));
	for (size_t i = 0; i < tempNumComments; i++) {
		Comentario tempComment;
		getline(fin, tempComment.clientName);
		getline(fin, tempComment.comment);
		comments.push_back(tempComment);
	}
}

void App::write(ofstream &fout) const {
	rating.write(fout);
	uint32_t tempNumComments = comments.size();
	fout.write((char*)&tempNumComments, sizeof(uint32_t));
	for (size_t i = 0; i < comments.size(); i++) {
		fout << comments[i].clientName << endl;
		fout << comments[i].comment << endl;
	}
}
