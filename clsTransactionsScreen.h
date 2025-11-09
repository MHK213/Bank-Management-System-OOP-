#pragma once

#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsInputValidate.h"
#include "clsMainScreen.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"

using namespace std;

class clsTransactionsScreen : protected clsScreen
{
private:
	enum enTransactionsMenuOptions { enDeposit = 1, enWithdraw = 2, enTotalBalances = 3, enTransfer = 4, enTransferLog = 5, enMainMenu = 6 };

	static enTransactionsMenuOptions _ReadTransactionsMenuOption() {
		short TransactionsMenuChoice = 0;

		cout << "\t\t\t\t     Choose What do you want to do? [1 to 6]? ";
		TransactionsMenuChoice = clsInputValidate::ReadShortNumberBetween(1, 6, "\nInvalid Number! Enter a Number between 1 and 6: ");

		return (enTransactionsMenuOptions)TransactionsMenuChoice;

	}

	static void _ShowDepositScreen() {
		clsDepositScreen::ShowDepositScreen();
	};

	static void _ShowWithdrawScreen() {
		clsWithdrawScreen::ShowWithdrawScreen();
	};

	static void _ShowTotalBalnces() {
		clsTotalBalancesScreen::ShowTotalBalancesScreen();
	};

	static void _ShowTransferScreen(){
		clsTransferScreen::ShowTransferScreen();
	}

	static void _ShowTransferLogScreen() {
		clsTransferLogScreen::ShowTransferLogList();
	}

	static void _GoBackToTransactionsMenu() {
		cout << "\n\nPress any key to back to Transactions Menu..." << endl;
		system("pause>0");
		ShowTransactionsMenu();
	}

	static void _PerformTransactionsMenuoption(enTransactionsMenuOptions TransactionsMenuOptions) {
		switch (TransactionsMenuOptions) {
		case enDeposit: {
			system("cls");
			_ShowDepositScreen();
			_GoBackToTransactionsMenu();
			break;
		}
		case enWithdraw: {
			system("cls");
			_ShowWithdrawScreen();
			_GoBackToTransactionsMenu();
			break;
		}
		case enTotalBalances: {
			system("cls");
			_ShowTotalBalnces();
			_GoBackToTransactionsMenu();
			break;
		}
		case enTransfer: {
			system("cls");
			_ShowTransferScreen();
			_GoBackToTransactionsMenu();
			break;
		}
		case enTransferLog: {
			system("cls");
			_ShowTransferLogScreen();
			_GoBackToTransactionsMenu();
			break;
		}
		case enMainMenu: {}
		}
	}

public:
	static void ShowTransactionsMenu() {
		
		system("cls");

		if (!CheckAccessRights(clsUser::enPermissions::pTransactions)) {
			return;
		}

		_DrawScreenHeader("\t\tTransactions Screen");

		cout << setw(37) << left << "" << "========================================\n";
		cout << setw(37) << left << "" << "\t\tTransactions Menu Screen\n";
		cout << setw(37) << left << "" << "========================================\n";
		cout << setw(37) << left << "" << "\t[1] Deposit.\n";
		cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
		cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
		cout << setw(37) << left << "" << "\t[4] Transfer.\n";
		cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
		cout << setw(37) << left << "" << "========================================" << endl;

		_PerformTransactionsMenuoption(_ReadTransactionsMenuOption());
	}
};