#pragma once

#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"

using namespace std;

class clsDeleteClientScreen : protected clsScreen
{
private:
	static void _PrintClient(clsBankClient Client) {
		cout << "\nClient Card :";
		cout << "\n________________________________________";
		cout << "\nFirst Name   : " << Client.FirstName;
		cout << "\nLast Name    : " << Client.LastName;
		cout << "\nFull Name    : " << Client.FullName();
		cout << "\nEmail        : " << Client.Email;
		cout << "\nPhone        : " << Client.Phone;
		cout << "\nAcc. Number  : " << Client.AccountNumber();
		cout << "\nPinCode      : " << Client.PinCode;
		cout << "\nBalance      : " << Client.AccountBalance;
		cout << "\n________________________________________" << endl;
	}

public:
	static void ShowDeleteClientScreen() {

		if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient)) {
			return;
		}

		_DrawScreenHeader("\t\tDelete Client Screen");

		string AccountNumber = "";
		cout << "\nEnter Client Account Number: ";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << "\nAccount Number is not found, Enter another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}
		
		clsBankClient Client = clsBankClient::FindClient(AccountNumber);
		_PrintClient(Client);
		
		char Answer = 'N';
		cout << "\nAre you sure you want to delete this client? Y/N? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y') {
			if (Client.Delete()) {
				cout << "\n\nClient deleted Successfully" << endl;
				_PrintClient(Client);
			}
			else {
				cout << "\n\nError! Client was Not Found" << endl;
			}
		}
	}
};