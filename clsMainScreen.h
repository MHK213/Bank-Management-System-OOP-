#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientsListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "Global.h"
#include "clsUser.h"

using namespace std;

class clsMainScreen : protected clsScreen
{
private:
	enum enMainMenuOption { enShowClientList = 1, enAddNewClient = 2, enDeleteClient = 3, enUpdateClient = 4,
		enFindClient = 5, enTransactions = 6, enManageUsers = 7, Logout = 8 };

	static enMainMenuOption _ReadMainMenuOption() {

		cout << "\t\t\t\t     Choose What do you want to do? [1 to 8]? ";
		short MainMenuChoice = clsInputValidate::ReadIntNumberBetween(1,8, "\nInvalid Number! Enter a Number between 1 and 8: ");

		return (enMainMenuOption)MainMenuChoice;

	}

	static void _GoBackToMainMenu() {
		cout << "\n\nPress any key to back to Main Menu..." << endl;
		system("pause>0");
		ShowMainMenu();
	}

	static void _ShowAllClientsListScreen() {
		clsClientsListScreen::ShowClientsList();
	};

	static void _ShowAddNewClientScreen() {
		clsAddNewClientScreen::ShowAddNewClientScreen();
	};

	static void _ShowDeleteClientScreen() {
		clsDeleteClientScreen::ShowDeleteClientScreen();
	};

	static void _ShowUpdateClientInfoScreen() {
		clsUpdateClientScreen::ShowUpdateClientScreen();
	};

	static void _ShowFindClientScreen() {
		clsFindClientScreen::ShowFindClientScreen();
	};

	static void _ShowTransactionsMenu() {
		clsTransactionsScreen::ShowTransactionsMenu();
	};

	static void _ShowManageUsersMenuScreen() {
		clsManageUsersScreen::ShowManageUsersMenu();
	};

	static void _Logout() {
		CurrentUser = clsUser::FindUser("", "");
	};

	static void _PerformMainMenuOption(enMainMenuOption MainMenuOption) {
		switch (MainMenuOption) {
		case enShowClientList: {
			system("cls");
			_ShowAllClientsListScreen();
			_GoBackToMainMenu();
			break;
		}
		case enAddNewClient: {
			system("cls");
			_ShowAddNewClientScreen();
			_GoBackToMainMenu();
			break;
		}
		case enDeleteClient: {
			system("cls");
			_ShowDeleteClientScreen();
			_GoBackToMainMenu();
			break;
		}
		case enUpdateClient: {
			system("cls");
			_ShowUpdateClientInfoScreen();
			_GoBackToMainMenu();
			break;
		}
		case enFindClient: {
			system("cls");
			_ShowFindClientScreen();
			_GoBackToMainMenu();
			break;
		}
		case enTransactions: {
			system("cls");
			_ShowTransactionsMenu();
			_GoBackToMainMenu();
			break;
		}
		case enManageUsers: {
			system("cls");
			_ShowManageUsersMenuScreen();
			_GoBackToMainMenu();
			break;
		}
		case Logout: {
			system("cls");
			_Logout();
			break;
		}
		}
	}

public:

	static void ShowMainMenu() {
		system("cls");
		_DrawScreenHeader("\t\tMain Screen");

		cout << setw(37) << left << "" << "========================================\n";
		cout << setw(37) << left << "" << "\t\tMain Menu Screen\n";
		cout << setw(37) << left << "" << "========================================\n";
		cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
		cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
		cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
		cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
		cout << setw(37) << left << "" << "\t[5] Find Client.\n";
		cout << setw(37) << left << "" << "\t[6] Transactions.\n";
		cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
		cout << setw(37) << left << "" << "\t[8] Logout.\n";
		cout << setw(37) << left << "" << "========================================" << endl;

		_PerformMainMenuOption(_ReadMainMenuOption());
	}
};