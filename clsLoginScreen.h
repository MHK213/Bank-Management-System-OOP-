#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "Global.h"

using namespace std;

class clsLoginScreen : protected clsScreen
{
private:
	static bool _Login() {

		bool LoginFaild = false;
		short FaildLoginCount = 0;
		string UserName, Password;

		do {

			if (LoginFaild) {
				FaildLoginCount++;
				cout << "\nInvalid UserName/Password!\n";
				cout << "\nyou have " << (3 - FaildLoginCount) << " Trials to login.\n\n";
			}

			if (FaildLoginCount == 3) {
				cout << "\nYou are locked after 3 faild trials\n\n";
				return false;
			}

			cout << "\nEnter UserName?: ";
			cin >> UserName;

			cout << "Enter Password?: ";
			cin >> Password;

			CurrentUser = clsUser::FindUser(UserName, Password);

			LoginFaild = CurrentUser.IsEmpty();

		} while (LoginFaild);

		CurrentUser.RegisterLogIn();
		clsMainScreen::ShowMainMenu();
		
		return true;
	}

public:
	static bool ShowLoginScreen() {
		system("cls");
		_DrawScreenHeader("\t   Login Screen");
		return _Login();
	}
};