#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"

using namespace std;

class clsDeleteUserScreen : protected clsScreen
{
private:
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
	static void ShowDeleteUserScreen() {
		_DrawScreenHeader("\t\tDelete User Screen");

		string UserName = "";
		cout << "\nEnter UserName: ";
		UserName = clsInputValidate::ReadString();
		while (!clsUser::IsUserExist(UserName)) {
			cout << "\nUserName is not found, Enter another one: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::FindUser(UserName);
		_PrintUser(User);

		char Answer = 'N';
		cout << "\nAre you sure you want to delete this User? Y/N? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y') {
			if (User.Delete()) {
				cout << "\n\nUser deleted Successfully" << endl;
				_PrintUser(User);
			}
			else {
				cout << "\n\nError! User was Not Found" << endl;
			}
		}
	}
};