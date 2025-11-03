#pragma once

#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsBankClient.h"

using namespace std;

class clsAddNewClientScreen : protected clsScreen
{
private:
	static void _ReadClientInfo(clsBankClient& Client) {

		cout << "\nEnter First Name? ";
		Client.FirstName = clsInputValidate::ReadString();

		cout << "Enter Last Name? ";
		Client.LastName = clsInputValidate::ReadString();

		cout << "Enter Email? ";
		Client.Email = clsInputValidate::ReadString();

		cout << "Enter Phone? ";
		Client.Phone = clsInputValidate::ReadString();

		cout << "Enter PinCode? ";
		Client.PinCode = clsInputValidate::ReadString();

		cout << "Enter AccountBalance? ";
		Client.AccountBalance = clsInputValidate::ReadFloatNumber();
	}

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
	static void ShowAddNewClientScreen() {

		if (!CheckAccessRights(clsUser::enPermissions::pAddNewClients)) {
			return;
		}

		_DrawScreenHeader("\t\tAdd New Client Screen");

		string AccountNumber = "";
		cout << "\nEnter Client Account Number: ";
		AccountNumber = clsInputValidate::ReadString();
		while (clsBankClient::IsClientExist(AccountNumber)) {
			cout << "\nAccount Number is Already used, Enter another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		cout << "\n\Add New Client : ";
		cout << "\n________________________";

		clsBankClient Client = clsBankClient::GetAddNewClientObject(AccountNumber);

		_ReadClientInfo(Client);

		clsBankClient::enSaveResults SaveResult;
		SaveResult = Client.Save();

		switch (SaveResult) {
		case clsBankClient::svSucceeded:
			cout << "\nClient Added Succesfully\n";
			_PrintClient(Client);
			break;
		case clsBankClient::svFaildEmptyObject:
			cout << "\nError! Account was not Saved because it's Empty\n";
			break;
		}
	}
};