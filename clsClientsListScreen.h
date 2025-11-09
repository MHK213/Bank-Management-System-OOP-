#pragma once

#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsUser.h"

using namespace std;

class clsClientsListScreen : protected clsScreen
{
private:
	static void _PrintClientRecordLine(clsBankClient Client) {

		cout << "| " << left << setw(15) << Client.AccountNumber();
		cout << "| " << left << setw(20) << Client.FullName();
		cout << "| " << left << setw(12) << Client.Phone;
		cout << "| " << left << setw(20) << Client.Email;
		cout << "| " << left << setw(10) << Client.PinCode;
		cout << "| " << left << setw(12) << Client.AccountBalance;
	}

public:
	static void ShowClientsList() {

		if (!CheckAccessRights(clsUser::enPermissions::pListClients)) {
			return;
		}

		vector <clsBankClient> vClients = clsBankClient::GetClientsList();
		string Title = "\t\tClients List Screen";
		string Subtitle = "\t\t  (" + to_string(vClients.size()) + ") Client(s).";

		clsScreen::_DrawScreenHeader(Title, Subtitle);

		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		cout << "| " << left << setw(15) << "Accout Number";
		cout << "| " << left << setw(20) << "Client Name";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(20) << "Email";
		cout << "| " << left << setw(10) << "Pin Code";
		cout << "| " << left << setw(12) << "Balance";
		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		if (vClients.size() == 0) {
			cout << "\t\t\t\tNo Clients Available In the System!";
		}
		else {
			for (clsBankClient& Client : vClients) {
				_PrintClientRecordLine(Client);
				cout << endl;
			}
		}

		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;
	}
};