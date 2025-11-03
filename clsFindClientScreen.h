#pragma once

#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"

using namespace std;

class clsFindClientScreen : protected clsScreen
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
	static void ShowFindClientScreen() {

		if (!CheckAccessRights(clsUser::enPermissions::pFindClient)) {
			return;
		}

		_DrawScreenHeader("\t\tFind Client Screen");

		string AccountNumber = "";
		cout << "\nEnter Client Account Number: ";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << "\nAccount Number is not found, Enter another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::FindClient(AccountNumber);

		if (!Client.IsEmpty())
			cout << "\nClient was Found :-)\n";
		else
			cout << "\nClient was Not Found :-(\n";

		_PrintClient(Client);

	}
};