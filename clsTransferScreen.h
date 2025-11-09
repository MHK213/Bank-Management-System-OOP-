#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "Global.h"

using namespace  std;

class clsTransferScreen : protected clsScreen
{
private:
	static string _ReadAccountNumber(string Message) {
		string AccountNumber = "";

		cout << Message;
		AccountNumber = clsInputValidate::ReadString();

		return AccountNumber;
	}

	static void _PrintClient(clsBankClient Client) {
		cout << "\nClient Card :";
		cout << "\n________________________________________";
		cout << "\nFull Name    : " << Client.FullName();
		cout << "\nAcc. Number  : " << Client.AccountNumber();
		cout << "\nBalance      : " << Client.AccountBalance;
		cout << "\n________________________________________" << endl;
	}

	static double _ReadAmount(clsBankClient SourceClient) {
		double Amount = 0;

		cout << "\nEnter Transfer Amount? ";
		Amount = clsInputValidate::ReadDblNumber();

		while (Amount > SourceClient.AccountBalance) {
			cout << "\nAmount Exceeds the available balance, Enter Another Amount? ";
			Amount = clsInputValidate::ReadDblNumber();
		}

		return Amount;
	}

public:
	static void ShowTransferScreen() {
		
		_DrawScreenHeader("\t\tTransfer Screen");

		string AccountNumber1 = _ReadAccountNumber("\nEnter Account Number to Transfer From: ");

		while (!clsBankClient::IsClientExist(AccountNumber1)) {
			cout << "\nAccount Number is not found, Enter another one: ";
			AccountNumber1 = clsInputValidate::ReadString();
		}

		clsBankClient SourceClient = clsBankClient::FindClient(AccountNumber1);
		_PrintClient(SourceClient);

		string AccountNumber2 = _ReadAccountNumber("\nEnter Account Number to Transfer To: ");

		while (!clsBankClient::IsClientExist(AccountNumber2)) {
			cout << "\nAccount Number is not found, Enter another one: ";
			AccountNumber2 = clsInputValidate::ReadString();
		}

		clsBankClient DestinationClient = clsBankClient::FindClient(AccountNumber2);
		_PrintClient(DestinationClient);

		double Amount = _ReadAmount(SourceClient);

		char Answer = 'N';
		cout << "\nAre you Sure you want perform this transaction? y/n ? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y') {
			if (SourceClient.Transfer(Amount, DestinationClient, CurrentUser.UserName))
				cout << "\nTransfer done Successfuly\n";
			else
				cout << "\nTransfer Faild\n";
		}
		_PrintClient(SourceClient);
		_PrintClient(DestinationClient);
		}
};