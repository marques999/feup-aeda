/*!
 * \file UI.cpp
 *
 * FEUP_AEDA1415_2MIEIC03_D
 * \author Carlos Soares
 * \author Diogo Marques
 * \author Fabio Carneiro
 *
 * \date Dezembro 2014
 *
 */

#include "UI.h"

namespace UI {
	void DisplayFrame(string s)
	{
		system("cls");
		cout << endl;
		int begin = (s.size() % 2 == 0) ? (23 - (s.size() / 2)) : (22 - (s.size() / 2));
		int end = 22 + (s.size() / 2);
		cout << "\t\t-------------------------------------------------" << endl;
		cout << "\t\t| ";
		for (int i = 0; i < begin; i++)
		{
			cout << " ";
		}
		cout << s;
		for (int i = end; i < 45; i++)
		{
			cout << " ";
		}
		cout << "|" << endl;
		cout << "\t\t-------------------------------------------------" << endl << endl;
	}

	void DisplayMessage(string msg)
	{
		cout << endl << msg << endl;
	}

	void Display(string s)
	{
		cout << right << setw(40 + (s.size() / 2)) << setfill(' ') << s << endl;
	}

	void DisplayTable(int c, vector<string> labels, int length[]) {
		stringstream frame_begin;
		stringstream frame_end;
		stringstream ss;
		frame_begin << "-";
		frame_end << "-";
		ss << "|";
		for (int i = 0; i < c; i++) {
			for (int j = 0; j < length[i]; j++) {
				frame_begin << "-";
				frame_end << "-";
			}
			ss << left << setw(length[i]) << labels[i];
			ss << right << "|";
			frame_begin << "-";
			frame_end << "-";
		}
		UI::Display(frame_begin.str());
		UI::Display(ss.str());
		UI::Display(frame_end.str());
	}

	void DisplayTableRow(int c, vector<string> labels, int length[]) {
		stringstream ss;
		ss << "  ";
		for (int i = 0; i < c; i++) {
			ss << left << setw(length[i] - 1) << labels[i];
			if (i != c - 1) {
				ss << right << "  ";
			}
		}
		UI::Display(ss.str());
	}

	void DisplayMenuItem(int i, string label) {
		stringstream ss;
		ss << left << "| " << i << ". " << setw(26) << label << setw(2) << " |";
		UI::Display(ss.str());
	}

	void DisplayMenuTop() {
		UI::Display("---------------------------------");
	}

	void DisplayMenuBottom() {
		UI::Display("---------------------------------");
		UI::DisplayMenuItem(0, "<- GO BACK");
		UI::Display("---------------------------------");
		cout << endl;
	}

	string FormatPrice(double p) {
		ostringstream os;
		os << setw(4) << fixed << setprecision(2) << p;
		return os.str();
	}

	string FormatRating(double r) {
		ostringstream os;
		os << setw(3) << fixed << setprecision(1) << r;
		return os.str();
	}

	string Format(unsigned n, unsigned w) {
		ostringstream os;
		os << setw(w) << left << fixed << setprecision(0) << n;
		return os.str();
	}
}
