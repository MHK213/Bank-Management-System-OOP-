#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsUtil.h"
#include "clsMainScreen.h"

using namespace std;

void PrintClientsDataForTotalBalances(clsBankClient ClientData) {

	cout << "| " << left << setw(15) << ClientData.AccountNumber();
	cout << "| " << left << setw(40) << ClientData.FullName();
	cout << "| " << left << setw(12) << ClientData.AccountBalance;
}

void ShowTotalBalnces() {
	vector <clsBankClient> vClients = clsBankClient::GetClientsList();

	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	double TotalBalances = clsBankClient::GetTotalBalances();

	if (vClients.size() == 0) {
		cout << "\t\t\t\tNo Clients Available In the System!";
	}
	else {
		for (clsBankClient& Client : vClients) {
			PrintClientsDataForTotalBalances(Client);
			cout << endl;
		}
	}

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	cout << "\t\t\t\tTotal Balances = " << TotalBalances << endl;;
	cout << "\t\t\t(" << clsUtil::NumberToText(TotalBalances) << ")" << endl;
}

int main()
{
	clsMainScreen::ShowMainMenu();

	return 0;
}