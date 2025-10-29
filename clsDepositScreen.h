#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsDepositScreen : protected clsScreen
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

	static string _ReadAccountNumber() {
		string AccountNumber = "";

		cout << "\nEnter Client Account Number: ";
		AccountNumber = clsInputValidate::ReadString();

		return AccountNumber;
	}

public:
	static void ShowDepositScreen() {

		_DrawScreenHeader("\t\tDeposit Screen");

		string AccountNumber = _ReadAccountNumber();

		while (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << "\nAccount Number is not found, Enter another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::FindClient(AccountNumber);
		_PrintClient(Client);

		double Amount = 0;
		cout << "\nPlease enter Deposit Amount? ";
		Amount = clsInputValidate::ReadDblNumber();

		char Answer = 'N';
		cout << "\nAre you Sure you want perform this transaction? y/n ? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y') {
			Client.Deposit(Amount);
			cout << "\n\nAmount Deposited Successfully" << endl;
			cout << "\nNew Balance is: " << Client.AccountBalance << endl;
		}
		else {
			cout << "\nOperation was Cancelled.\n";
		}
	}
};