/*!
 * \file Source.cpp
 *
 * FEUP_AEDA1415_2MIEIC03_D
 * \author Carlos Soares
 * \author Diogo Marques
 * \author Fabio Carneiro
 *
 * \date Dezembro 2014
 *
 */

#include "AppStore.h"

string to_upper(const string &s) {
	string r = s;
	for (unsigned i = 0; i < s.size(); i++) {
		r[i] = toupper(r[i]);
	}
	return r;
}

int main() {
	AppStore appStore("BL@CK M@RKET");

	try {
		appStore.read();
	}
	catch (FileIOException &e) {
		cout << e;
		system("pause");
	}

	string tempStr;
	string tempUser;
	int userChoice;

	while (true) {
		try {

			UI::DisplayFrame("APPSTORE SIMULATOR");
			UI::Display("");
			UI::Display("FEUP_AEDA1415_2MIEIC03_D");
			UI::Display("\n");
			UI::Display("AUTHORS:");
			UI::Display("");
			UI::Display("Carlos Soares");
			UI::Display("Diogo Marques");
			UI::Display("Fabio Carneiro");
			UI::Display("\n");
			UI::Display("Press <1> for administration mode");
			UI::Display("Press <2> for developer mode");
			UI::Display("Press <3> for customer mode");
			UI::Display("\n");
			UI::Display("Press <0> to save and exit");

			cout << endl;
			cout << "Please select an option: ";
			getline(cin, tempStr);
			userChoice = atoi(tempStr.c_str());
			if (userChoice < 0 || userChoice > 3) {
				throw InvalidParameter("choice");
			}
			switch (userChoice) {
			case 0:

				appStore.write();

				return 0;

			case 1:

				appStore.Main_admin();

				break;

			case 2:
			{
				UI::DisplayFrame("DEVELOPER LOGIN");
				cout << "Username: ";
				getline(cin, tempUser);
				int i = appStore.Developer_index(tempUser);
				if (i == -1) {
					throw DeveloperInexistente(tempUser);
				}
				appStore.Main_developer(i);
				break;
			}
			case 3:
			{
				UI::DisplayFrame("CUSTOMER LOGIN");
				cout << "Username: ";
				getline(cin, tempUser);
				int i = appStore.Cliente_index(tempUser);
				if (i == -1) {
					throw ClienteInexistente(tempUser);
				}
				appStore.Main_user(i);
				break;
			}
			}
		}
		catch (DeveloperInexistente &e) {
			cout << e;
			system("pause");
		}
		catch (ClienteInexistente &e) {
			cout << e;
			system("pause");
		}
		catch (InvalidParameter &e) {
			cout << e;
			system("pause");
		}
	}
	return 0;
}
