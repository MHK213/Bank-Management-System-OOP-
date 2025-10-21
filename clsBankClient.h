#pragma once

#include <iostream>
#include "clsPerson.h"
#include <vector>
#include <fstream>
#include <string>
#include "clsString.h"

using namespace std;

class clsBankClient : public clsPerson
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2};
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkForDelete;

	static clsBankClient _ConvertLineToClientObject(string Line, string Seprator = "#//#") {

		vector <string> vClientsdata;
		vClientsdata = clsString::Split(Line, Seprator);

		return clsBankClient(enMode::UpdateMode, vClientsdata[0], vClientsdata[1], vClientsdata[2], vClientsdata[3], vClientsdata[4], 
			vClientsdata[5], stod(vClientsdata[6]));
	}

	string _ConvertClientObjectToLine(clsBankClient Client, string Seprator = "#//#") {

		string stClientRecord = "";

		stClientRecord += Client.FirstName + Seprator;
		stClientRecord += Client.LastName + Seprator;
		stClientRecord += Client.Email + Seprator;
		stClientRecord += Client.Phone + Seprator;
		stClientRecord += Client.AccountNumber() + Seprator;
		stClientRecord += Client.PinCode + Seprator;
		stClientRecord += to_string(Client.AccountBalance);

		return stClientRecord;
	}

	static vector <clsBankClient> _LoadClientsDataFromFile() {

		vector <clsBankClient> _vClients;

		fstream MyFile;
		MyFile.open("BankClient.txt", ios::in);

		if (MyFile.is_open()) {
			string Line;

			while (getline(MyFile, Line)) {
				clsBankClient Client = _ConvertLineToClientObject(Line);
				_vClients.push_back(Client);
			}

			MyFile.close();
		}

		return _vClients;
	}

	void _SaveClientsDataToFile(vector <clsBankClient> vClients) {

		fstream MyFile;
		MyFile.open("BankClient.txt", ios::out);

		string DataLine;

		if (MyFile.is_open()) {

			for (clsBankClient& C : vClients) {
				if (C._MarkForDelete != true) {
					DataLine = _ConvertClientObjectToLine(C, "#//#");
					MyFile << DataLine << endl;
				}
			}

			MyFile.close();
		}
	}

	void AddDataLineToFile(string Line, string FileName = "BankClient.txt") {

		fstream DataFile;
		DataFile.open(FileName, ios::out | ios::app);

		if (DataFile.is_open()) {
			DataFile << Line << endl;
			DataFile.close();
		}
	}

	static clsBankClient _GetEmptyClientObject() {
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	void _Update() {

		vector <clsBankClient> _vClients;
		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients) {
			if (C.AccountNumber() == AccountNumber()) {
				C = *this;
				break;
				}
		}
		_SaveClientsDataToFile(_vClients);

	}

	void _AddNew() {
		AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

public:
	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, float AccountBalance)
		: clsPerson(FirstName, LastName, Email, Phone) {
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}

	string AccountNumber() {
		return _AccountNumber;
	}

	void SetPinCode(string PinCode) {
		_PinCode = PinCode;
	}

	string GetPinCode() {
		return _PinCode;
	}

	__declspec (property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(float AccountBalance) {
		_AccountBalance = AccountBalance;
	}

	float GetAccountBalance() {
		return _AccountBalance;
	}

	__declspec (property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

	void Print() {
		cout << "\nClient Card :";
		cout << "\n________________________________________";
		cout << "\nFirst Name   : " << FirstName;
		cout << "\nLast Name    : " << LastName;
		cout << "\nFull Name    : " << FullName();
		cout << "\nEmail        : " << Email;
		cout << "\nPhone        : " << Phone;
		cout << "\nAcc. Number  : " << _AccountNumber;
		cout << "\nPinCode      : " << _PinCode;
		cout << "\nBalance      : " << _AccountBalance;
		cout << "\n________________________________________" << endl;
	}

	static clsBankClient FindClient(string AccountNumber) {
		vector <clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("BankClient.txt", ios::in);

		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsBankClient Client = _ConvertLineToClientObject(Line);

				if (Client.AccountNumber() == AccountNumber) {
					MyFile.close();
					return Client;
				}
				vClients.push_back(Client);
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	static clsBankClient FindClient(string AccountNumber, string PinCode) {
		vector <clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("BankClient.txt", ios::in);

		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsBankClient Client = _ConvertLineToClientObject(Line);

				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode) {
					MyFile.close();
					return Client;
				}
				vClients.push_back(Client);
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	static bool IsClientExist(string AccountNumber) {
		clsBankClient Client1 = clsBankClient::FindClient(AccountNumber);
		return (!Client1.IsEmpty());
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExist = 2};
	enSaveResults Save() {
		switch (_Mode) {
		case UpdateMode:
			_Update();
			return enSaveResults::svSucceeded;
		case AddNewMode:
			if (clsBankClient::IsClientExist(_AccountNumber))
				return svFaildAccountNumberExist;
			else {
				_AddNew();
				return enSaveResults::svSucceeded;
			}
		case EmptyMode:
			if(IsEmpty())
				return enSaveResults::svFaildEmptyObject;
		}
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber) {
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	bool Delete() {
		vector <clsBankClient> vClients;
		vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : vClients) {
			if (C.AccountNumber() == AccountNumber()) {
				C._MarkForDelete = true;
				break;
			}
		}

		_SaveClientsDataToFile(vClients);

		*this = _GetEmptyClientObject();

		return true;
	}

	static vector <clsBankClient> GetClientsList() {
		return _LoadClientsDataFromFile();
	}

	static double GetTotalBalances() {
		vector <clsBankClient> vClients = _LoadClientsDataFromFile();

		double TotalBalances = 0;

		for (clsBankClient& Client : vClients) {
			TotalBalances += Client.AccountBalance;
		}

		return TotalBalances;
	}
};