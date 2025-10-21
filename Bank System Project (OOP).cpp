#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsUtil.h"

using namespace std;

void ReadClientInfo(clsBankClient& Client) {
	
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

void UpdateClient() {

	string AccountNumber = "";
	cout << "\nEnter Client Account Number: ";
	AccountNumber = clsInputValidate::ReadString();
	while (!clsBankClient::IsClientExist(AccountNumber)) {
		cout << "\nAccount Number is not found, Enter another one: ";
		AccountNumber = clsInputValidate::ReadString();
	}

	clsBankClient Client = clsBankClient::FindClient(AccountNumber);
	Client.Print();

	cout << "\n\nUpdate Client Info: ";
	cout << "\n________________________";

	ReadClientInfo(Client);

	clsBankClient::enSaveResults SaveResult;
	SaveResult = Client.Save();

	switch (SaveResult) {
	case clsBankClient::svSucceeded :
		cout << "\nAccount Updated Succesfully\n";
		Client.Print();
		break;
	case clsBankClient::svFaildEmptyObject:
		cout << "\nError! Account was not Saved because it's Empty\n";
		break;
	}
}

void AddClient() {

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

	ReadClientInfo(Client);

	clsBankClient::enSaveResults SaveResult;
	SaveResult = Client.Save();

	switch (SaveResult) {
	case clsBankClient::svSucceeded:
		cout << "\nClient Added Succesfully\n";
		Client.Print();
		break;
	case clsBankClient::svFaildEmptyObject:
		cout << "\nError! Account was not Saved because it's Empty\n";
		break;
	}
}

void DeleteClient() {
	string AccountNumber = "";
	cout << "\nEnter Client Account Number: ";
	AccountNumber = clsInputValidate::ReadString();
	while (!clsBankClient::IsClientExist(AccountNumber)) {
		cout << "\nAccount Number is not found, Enter another one: ";
		AccountNumber = clsInputValidate::ReadString();
	}

	clsBankClient Client = clsBankClient::FindClient(AccountNumber);
	Client.Print();

	char Answer = 'N';
	cout << "\nAre you sure you want to delete this client? Y/N? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y') {
		if (Client.Delete()) {
			cout << "\n\nClient deleted Successfully" << endl;
			Client.Print();
		}
		else {
			cout << "\n\nError! Client was Not Found" << endl;
		}
	}
}

void PrintClientRecordLine(clsBankClient Client) {

	cout << "| " << left << setw(15) << Client.AccountNumber();
	cout << "| " << left << setw(20) << Client.FullName();
	cout << "| " << left << setw(12) << Client.Phone;
	cout << "| " << left << setw(20) << Client.Email;
	cout << "| " << left << setw(10) << Client.PinCode;
	cout << "| " << left << setw(12) << Client.AccountBalance;
}

void PrintClientsDataForTotalBalances(clsBankClient ClientData) {

	cout << "| " << left << setw(15) << ClientData.AccountNumber();
	cout << "| " << left << setw(40) << ClientData.FullName();
	cout << "| " << left << setw(12) << ClientData.AccountBalance;
}

void ShowClientsList() {
	vector <clsBankClient> vClients = clsBankClient::GetClientsList();

	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
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
			PrintClientRecordLine(Client);
			cout << endl;
		}
	}

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
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
	ShowTotalBalnces();

	return 0;
}