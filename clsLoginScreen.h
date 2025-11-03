#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "Global.h"

using namespace std;

class clsLoginScreen : protected clsScreen
{
private:
	static void _Login() {

		bool LoginFaild = false;
		string UserName, Password;

		do {

			if (LoginFaild)
				cout << "\nInvalid UserName/Password!\n";

			cout << "\nEnter UserName?: ";
			cin >> UserName;

			cout << "Enter Password?: ";
			cin >> Password;

			CurrentUser = clsUser::FindUser(UserName, Password);

			LoginFaild = CurrentUser.IsEmpty();

		} while (LoginFaild);

		clsMainScreen::ShowMainMenu();
	}

public:
	static void ShowLoginScreen() {
		system("cls");
		_DrawScreenHeader("\t   Login Screen");
		_Login();
	}
};