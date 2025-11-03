#pragma once

#include <iostream>
#include "clsPerson.h"
#include <vector>
#include <fstream>
#include <string>
#include "clsString.h"

using namespace std;

class clsUser : public clsPerson
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;

	string _UserName;
	string _Password;
	int _Permissions;
	bool _MarkForDelete = false;

	static clsUser _GetEmptyUserObject() {
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static clsUser _ConvertLineToUserObject(string Line, string Seprator = "#//#") {

		vector <string> vUsers;
		vUsers = clsString::Split(Line, Seprator);

		return clsUser(enMode::UpdateMode, vUsers[0], vUsers[1], vUsers[2], vUsers[3], vUsers[4],
			vUsers[5], stod(vUsers[6]));
	}

	string _ConvertUserObjectToLine(clsUser User, string Seprator = "#//#") {

		string stUserRecord = "";

		stUserRecord += User.FirstName + Seprator;
		stUserRecord += User.LastName + Seprator;
		stUserRecord += User.Email + Seprator;
		stUserRecord += User.Phone + Seprator;
		stUserRecord += User.UserName + Seprator;
		stUserRecord += User.Password + Seprator;
		stUserRecord += to_string(User.Permissions);

		return stUserRecord;
	}

	static vector <clsUser> _LoadUsersDataFromFile() {

		vector <clsUser> _vUsers;

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open()) {
			string Line;

			while (getline(MyFile, Line)) {
				clsUser User = _ConvertLineToUserObject(Line);
				_vUsers.push_back(User);
			}

			MyFile.close();
		}

		return _vUsers;
	}

	void _SaveUserDataToFile(vector <clsUser> vUsers) {

		fstream MyFile;
		MyFile.open("Users.txt", ios::out);

		string DataLine;

		if (MyFile.is_open()) {

			for (clsUser& U : vUsers) {
				if (U._MarkForDelete != true) {
					DataLine = _ConvertUserObjectToLine(U, "#//#");
					MyFile << DataLine << endl;
				}
			}

			MyFile.close();
		}
	}

	void AddDataLineToFile(string Line, string FileName = "Users.txt") {

		fstream DataFile;
		DataFile.open(FileName, ios::out | ios::app);

		if (DataFile.is_open()) {
			DataFile << Line << endl;
			DataFile.close();
		}
	}

	void _Update() {

		vector <clsUser> _vUsers;
		_vUsers = _LoadUsersDataFromFile();

		for (clsUser& U : _vUsers) {
			if (U.UserName == UserName) {
				U = *this;
				break;
			}
		}
		_SaveUserDataToFile(_vUsers);

	}

	void _AddNew() {
		AddDataLineToFile(_ConvertUserObjectToLine(*this));
	}

public:
	enum enPermissions {
		eAll = -1, pListClients = 1, pAddNewClients = 2, pDeleteClient = 4,
		pUpdateClient = 8, pFindClient = 16, pTransactions = 32, pManageUsers = 64
	};

	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName, string Password, int Permissions) 
		: clsPerson(FirstName, LastName, Email, Phone) {
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}

	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkedForDeleted() {
		return _MarkForDelete;
	}

	void SetUserName(string UserName) {
		_UserName = UserName;
	}

	string GetUserName() {
		return _UserName;
	}

	__declspec (property(get = GetUserName, put = SetUserName)) string UserName;

	void SetPassword(string Password) {
		_Password = Password;
	}

	string GetPassword() {
		return _Password;
	}

	__declspec (property(get = GetPassword, put = SetPassword)) string Password;

	void SetPermissions(int Permissions) {
		_Permissions = Permissions;
	}

	int GetPermissions() {
		return _Permissions;
	}

	__declspec (property(get = GetPermissions, put = SetPermissions)) int Permissions;

	static clsUser FindUser(string UserName) {
		vector <clsUser> vUsers;

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsUser User = _ConvertLineToUserObject(Line);

				if (User.UserName == UserName) {
					MyFile.close();
					return User;
				}
				vUsers.push_back(User);
			}
			MyFile.close();
		}
		return _GetEmptyUserObject();
	}

	static clsUser FindUser(string UserName, string Password) {
		vector <clsUser> vUsers;

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsUser User = _ConvertLineToUserObject(Line);

				if (User.UserName == UserName && User.Password == Password) {
					MyFile.close();
					return User;
				}
				vUsers.push_back(User);
			}
			MyFile.close();
		}
		return _GetEmptyUserObject();
	}

	static bool IsUserExist(string UserName) {
		clsUser User = clsUser::FindUser(UserName);
		return (!User.IsEmpty());
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserNameExist = 2 };
	enSaveResults Save() {
		switch (_Mode) {
		case UpdateMode:
			_Update();
			return enSaveResults::svSucceeded;
		case AddNewMode:
			if (clsUser::IsUserExist(_UserName))
				return svFaildUserNameExist;
			else {
				_AddNew();
				_Mode = UpdateMode;
				return enSaveResults::svSucceeded;
			}
		case EmptyMode:
			if (IsEmpty())
				return enSaveResults::svFaildEmptyObject;
		}
	}

	bool Delete() {
		vector <clsUser> vUsers;
		vUsers = _LoadUsersDataFromFile();

		for (clsUser& U : vUsers) {
			if (U.UserName == UserName) {
				U._MarkForDelete = true;
				break;
			}
		}

		_SaveUserDataToFile(vUsers);

		*this = _GetEmptyUserObject();

		return true;
	}

	static clsUser GetAddNewUserObject(string UserName) {
		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	static vector <clsUser> GetUsersList() {
		return _LoadUsersDataFromFile();
	}

	bool CheckAccessPermission(enPermissions Permission) {

		if (this->Permissions == enPermissions::eAll)
			return true;

		if ((Permission & this->Permissions) == Permission)
			return true;
		else
			return false;
	}
};