#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"

using namespace std;

class clsAddNewUserScreen : protected clsScreen
{
private:
	static int _ReadPermissions() {
		char Answer = 'n';
		int Permissions = 0;

		do {
			cout << "\nDo you want to give full access? Y/N? ";
			cin >> Answer;
		} while (toupper(Answer) != 'Y' && toupper(Answer) != 'N');

		if (toupper(Answer) == 'Y')
			return -1;

		cout << "\nDo you want to give to? \n";

		cout << "\nShow Client List? y/n? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
			Permissions += clsUser::enPermissions::pListClients;

		cout << "\nAdd New Client? y/n? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
			Permissions += clsUser::enPermissions::pAddNewClients;

		cout << "\nDelete Client? y/n? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
			Permissions += clsUser::enPermissions::pDeleteClient;

		cout << "\nUpdate Client? y/n? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
			Permissions += clsUser::enPermissions::pUpdateClient;

		cout << "\nFind Client? y/n? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
			Permissions += clsUser::enPermissions::pFindClient;

		cout << "\nTransactions? y/n? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
			Permissions += clsUser::enPermissions::pTransactions;

		cout << "\nmanage Users? y/n? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
			Permissions += clsUser::enPermissions::pManageUsers;

		return Permissions;
	}

	static void _ReadUserInfo(clsUser& User) {

		cout << "\nEnter First Name? ";
		User.FirstName = clsInputValidate::ReadString();

		cout << "Enter Last Name? ";
		User.LastName = clsInputValidate::ReadString();

		cout << "Enter Email? ";
		User.Email = clsInputValidate::ReadString();

		cout << "Enter Phone? ";
		User.Phone = clsInputValidate::ReadString();

		cout << "Enter Password? ";
		User.Password = clsInputValidate::ReadString();

		User.Permissions = _ReadPermissions();
	}

	static void _PrintUser(clsUser User) {
		cout << "\nUser Card :";
		cout << "\n________________________________________";
		cout << "\nFirst Name   : " << User.FirstName;
		cout << "\nLast Name    : " << User.LastName;
		cout << "\nFull Name    : " << User.FullName();
		cout << "\nEmail        : " << User.Email;
		cout << "\nPhone        : " << User.Phone;
		cout << "\nUserName     : " << User.UserName;
		cout << "\nPassword     : " << User.Password;
		cout << "\nPermissions   : " << User.Permissions;
		cout << "\n________________________________________" << endl;
	}

public:
	static void ShowAddNewUserScreen() {
		_DrawScreenHeader("\t\tAdd New User Screen");

		string UserName = "";
		cout << "\nEnter UserName: ";
		UserName = clsInputValidate::ReadString();
		while (clsUser::IsUserExist(UserName)) {
			cout << "\nUserName is Already used, Enter another one: ";
			UserName = clsInputValidate::ReadString();
		}

		cout << "\n\Add New User : ";
		cout << "\n________________________";
		

		clsUser User = clsUser::GetAddNewUserObject(UserName);

		_ReadUserInfo(User);

		clsUser::enSaveResults SaveResult;
		SaveResult = User.Save();

		switch (SaveResult) {
		case clsUser::svSucceeded:
			cout << "\nUser Added Succesfully\n";
			_PrintUser(User);
			break;
		case clsUser::svFaildEmptyObject:
			cout << "\nError! Account was not Saved because it's Empty\n";
			break;
		}
	}
};