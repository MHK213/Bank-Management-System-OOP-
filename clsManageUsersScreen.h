#pragma once

#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsInputValidate.h"
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

using namespace std;

class clsManageUsersScreen : protected clsScreen
{
private:
	enum enManageUserMenuOptions { enShowUsersList = 1, enAddNewUser = 2, enDeleteUser = 3, enUpdateUser = 4, enFindUser = 5, enMainMenuUsers = 6 };

	static enManageUserMenuOptions _ReadManageUsersMenuOption() {
		short ManageUsersMenuChoice = 0;

		cout << setw(37) << left << "" << "Choose What do you want to do? [1 to 6]? ";
		ManageUsersMenuChoice = clsInputValidate::ReadShortNumberBetween(1, 6, "\nInvalid Number! Enter a Number between 1 and 6: ");

		return (enManageUserMenuOptions)ManageUsersMenuChoice;

	}

	static void _GoBackToManageUsersMenu() {
		cout << "\n\nPress any key to back to Manage Users Menu..." << endl;
		system("pause>0");
		ShowManageUsersMenu();
	}

	static void _PrintListUsersScreen() {
		clsListUsersScreen::ShowUsersList();
	}

	static void _ShowAddNewUserScreen() {
		clsAddNewUserScreen::ShowAddNewUserScreen();
	}

	static void _ShowDeleteUserScreen() {
		clsDeleteUserScreen::ShowDeleteUserScreen();
	}

	static void _ShowUpdateUserInfoScreen() {
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}

	static void _ShowFindUserScreen() {
		clsFindUserScreen::ShowFindUserScreen();
	}

	static void _PerformManageUsersMenuOptions(enManageUserMenuOptions ManageUsersMenuOptions) {
		switch (ManageUsersMenuOptions) {
		case enShowUsersList: {
			system("cls");
			_PrintListUsersScreen();
			_GoBackToManageUsersMenu();
			break;
		}
		case enAddNewUser: {
			system("cls");
			_ShowAddNewUserScreen();
			_GoBackToManageUsersMenu();
			break;
		}
		case enDeleteUser: {
			system("cls");
			_ShowDeleteUserScreen();
			_GoBackToManageUsersMenu();
			break;
		}
		case enUpdateUser: {
			system("cls");
			_ShowUpdateUserInfoScreen();
			_GoBackToManageUsersMenu();
			break;
		}
		case enFindUser: {
			system("cls");
			_ShowFindUserScreen();
			_GoBackToManageUsersMenu();
			break;
		}
		case enMainMenuUsers: {}
		}
	}

public:
	static void ShowManageUsersMenu() {

		system("cls");

		if (!CheckAccessRights(clsUser::enPermissions::pManageUsers)) {
			return;
		}

		_DrawScreenHeader("\t\tManage Users Screen");

		cout << setw(37) << left << "" << "========================================\n";
		cout << setw(37) << left << "" << "\t\tManage Users Menu Screen\n";
		cout << setw(37) << left << "" << "========================================\n";
		cout << setw(37) << left << "" << "\t[1] List Users.\n";
		cout << setw(37) << left << "" << "\t[2] Add New User.\n";
		cout << setw(37) << left << "" << "\t[3] Delete User.\n";
		cout << setw(37) << left << "" << "\t[4] Update User.\n";
		cout << setw(37) << left << "" << "\t[5] Find User.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
		cout << setw(37) << left << "" << "========================================" << endl;

		_PerformManageUsersMenuOptions(_ReadManageUsersMenuOption());
	}
};