#pragma once

#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"

using namespace std;

class clsUpdateClientScreen : protected clsScreen
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
	static void ShowUpdateClientScreen() {

		if (!CheckAccessRights(clsUser::enPermissions::pUpdateClient)) {
			return;
		}

		_DrawScreenHeader("\t\tUpdate Client Screen");

		string AccountNumber = "";
		cout << "\nEnter Client Account Number: ";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << "\nAccount Number is not found, Enter another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::FindClient(AccountNumber);
		_PrintClient(Client);

		cout << "\n\nUpdate Client Info: ";
		cout << "\n________________________";

		_ReadClientInfo(Client);

		clsBankClient::enSaveResults SaveResult;
		SaveResult = Client.Save();

		switch (SaveResult) {
		case clsBankClient::svSucceeded :
			cout << "\nAccount Updated Succesfully\n";
			_PrintClient(Client);
			break;
		case clsBankClient::svFaildEmptyObject:
			cout << "\nError! Account was not Saved because it's Empty\n";
			break;
		}
	}
};