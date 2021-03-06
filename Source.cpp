/*!
 * \file Source.cpp
 *
 * FEUP_AEDA1415_2MIEIC03_D
 * \author Carlos Soares
 * \author Diogo Marques
 * \author Fabio Carneiro
 *
 * \date Janeiro 2015
 *
 */

#include "AppStore.h"

string to_upper(const string &s)
{
	string r = s;
	for (unsigned i = 0; i < s.size(); i++)
	{
		r[i] = toupper(r[i]);
	}
	return r;
}

void GUIDeveloperLogin(AppStore &as)
{
	string developerName;

	UI::DisplayFrame("DEVELOPER LOGIN");

	cout << "Username: ";
	getline(cin, developerName);

	int i = as.indexDeveloper(developerName);
	if (i == -1)
	{
		throw DeveloperInexistente(developerName);
	}

	as.GUIDeveloperMenu(i);
}

void GUIClienteLogin(AppStore &as)
{
	string clienteName;

	UI::DisplayFrame("CUSTOMER LOGIN");

	cout << "Username: ";
	getline(cin, clienteName);

	int i = as.indexCliente(clienteName);
	if (i == -1)
	{
		throw ClienteInexistente(clienteName);
	}

	as.GUIClienteMenu(i);
}

int main()
{
	AppStore appStore("BL@CK M@RKET");

	try
	{
		appStore.IOReadStore();
	}
	catch (FileIOException &e)
	{
		cout << e;
		system("pause");
	}

	string tempStr;
	string tempUser;
	int userChoice;

	while (true)
	{
		try
		{
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

			cout << "\nPlease select an option: ";
			getline(cin, tempStr);

			userChoice = atoi(tempStr.c_str());
			if (userChoice < 0 || userChoice > 3)
			{
				throw InvalidParameter("choice");
			}

			switch (userChoice)
			{
			case 0:

				appStore.IOWriteStore();
				return 0;

			case 1:

				appStore.GUIAdminMenu();
				break;

			case 2:

				GUIDeveloperLogin(appStore);
				break;

			case 3:

				GUIClienteLogin(appStore);
				break;
			}
		}
		catch (DeveloperInexistente &e)
		{
			cout << e;
			system("pause");
		}
		catch (ClienteInexistente &e)
		{
			cout << e;
			system("pause");
		}
		catch (InvalidParameter &e)
		{
			cout << e;
			system("pause");
		}
	}
	return 0;
}
