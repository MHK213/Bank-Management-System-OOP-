#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"

using namespace std;

class clsFindUserScreen : protected clsScreen
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
	static void ShowFindUserScreen() {
		_DrawScreenHeader("\t\tFind User Screen");

		string UserName = "";
		cout << "\nEnter UserName: ";
		UserName = clsInputValidate::ReadString();
		while (!clsUser::IsUserExist(UserName)) {
			cout << "\nUserName is not found, Enter another one: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::FindUser(UserName);

		if (!User.IsEmpty())
			cout << "\nUser was Found :-)\n";
		else
			cout << "\nUser was Not Found :-(\n";

		_PrintUser(User);
	}
};