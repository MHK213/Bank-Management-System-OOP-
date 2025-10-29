#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsWithdrawScreen : protected clsScreen
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
	static void ShowWithdrawScreen(){

		_DrawScreenHeader("\t\tWithdraw Screen");

		string AccountNumber = _ReadAccountNumber();

		while (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << "\nAccount Number is not found, Enter another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::FindClient(AccountNumber);
		_PrintClient(Client);

		double Amount = 0;
		cout << "\nPlease enter Withdraw Amount? ";
		Amount = clsInputValidate::ReadDblNumber();

		char Answer = 'N';
		cout << "\nAre you Sure you want perform this transaction? y/n ? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y') {
			if (Client.Withdraw(Amount)) {
				cout << "\n\nAmount Deposited Successfully" << endl;
				cout << "\nNew Balance is: " << Client.AccountBalance << endl;
			}
			else {
				cout << "\nCannot withdraw, Insuffecient Balance!\n";
				cout << "\nAmount to withdraw is : " << Amount;
				cout << "\nYour Balance is : " << Client.AccountBalance;
			}
		}
		else {
			cout << "\nOperation was Cancelled.\n";
		}
	}
};

