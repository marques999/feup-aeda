/*!
 * \file Source.cpp
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

#include "AppStore.h"

string to_upper(const string &s) {
	string r = s;
	for (unsigned i = 0; i < s.size(); i++) {
		r[i] = toupper(r[i]);
	}
	return r;
}

void testDeveloper() {
	AppStore appStore("BL@CK M@RKET");
	Developer* me = new Developer_Individual("Diogo Marques", "Valongo");
	Developer* mycompany = new Developer_Empresa("My Company", "Porto", 192314455);
	Developer* urcompany = new Developer_Empresa("Faz Merda", "Coimbra", 104988343);
	appStore.insertDeveloper(mycompany);
	appStore.insertDeveloper(me);
	appStore.insertDeveloper(urcompany);
	//ASSERT_EQUAL(mycompany->getType(), DEVELOPER_EMPRESA);
	//ASSERT_EQUAL(urcompany->getBalance(), 0);
	//ASSERT_EQUAL(appStore.getDevelopers();
	//ASSERT_EQUAL(appStore.getNumDevelopers(), 3);
}

void testApps() {
	AppStore appStore("BL@CK M@RKET");
	Developer* me = new Developer_Individual("Diogo Marques", "Valongo");
	Developer* mycompany = new Developer_Empresa("My Company", "Porto", 192314455);
	Developer* urcompany = new Developer_Empresa("Faz Merda", "Coimbra", 104988343);
	appStore.insertDeveloper(mycompany);
	appStore.insertDeveloper(me);
	appStore.insertDeveloper(urcompany);
	App Facebook("Facebook", 0.0, "Internet", "This is a description");
	Facebook.setDeveloper(me);
	App Whatsapp("WhatsApp", 1.99, "Internet", "This is a description");
	App Retrica("Retrica", 0.79, "Multimedia", "This is a description");
	Retrica.setDeveloper(mycompany);
	Whatsapp.setDeveloper(me);
	appStore.insertApp(Facebook);
	appStore.insertApp(Retrica);
	appStore.insertApp(Whatsapp);
	//ASSERT_EQUAL(Facebook.getRating().get(), 0);
	//ASSERT_EQUAL(appStore.getNumAppsTotal(), 3);
	//ASSERT_EQUAL(appStore.getNumAppsDev(me), 2);
	//Cliente* eu = new Cliente("Diogo Marques", 1.95);
	//Cliente* you = new Cliente("Carlos Soares", 100.0);
	//Cliente* we = new Cliente("Fabio Carneiro", 23.5);
	//appStore.Cliente_add(you);
	//appStore.Cliente_add(eu);
	//appStore.Cliente_add(we);
}

int main() {
	AppStore appStore("BL@CK M@RKET");

	try {
		appStore.read();
	}
	catch (FileIOException &e) {
		cout << "File I/O exception occured while trying to read/write " << e.what() << endl;
		system("pause");
	}

	string tempStr;
	int userChoice;

	while (true) {
		try {
			system("cls");
			UI::DisplayFrame("APPSTORE SIMULATOR");
			UI::Display("");
			UI::Display("FEUP_AEDA1415_2MIEIC03_D");
			UI::Display("\n");
			UI::Display("AUTHORS:");
			UI::Display("");
			UI::Display("Carlos Soares");
			UI::Display("Diogo Marques");
			UI::Display("Fabio Carneiro");
			UI::Display("Joao Santos");
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
				system("cls");
				string tempUser;
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
				system("cls");
				string tempUser;
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
			cout << "\nERROR: developer " << e.getName() << " not found.\n";
			system("pause");
		}
		catch (ClienteInexistente &e) {
			cout << "\nERROR: customer " << e.getName() << " not found.\n";
			system("pause");
		}
		catch (InvalidParameter &e) {
			cout << "\nERROR: invalid parameter " << e.what() << "\n";
			system("pause");
		}
	}
	return 0;
}