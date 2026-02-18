#pragma once

#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsInputValidate.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"

using namespace std;

class clsCurrencyExchangeScreen : protected clsScreen
{
private:
	enum enCurrencyExchangeMenuOptions { enShowCurrenciesList = 1, enFindCurrency = 2, enUpdateRate = 3, 
		enCurrencyCalculator = 4, enMainMenu = 5 };

	static enCurrencyExchangeMenuOptions _ReadCurrencyExchangeMenuOption() {
		short MenuChoice = 0;

		cout << setw(37) << left << "" << "Choose What do you want to do? [1 to 5]? ";
		MenuChoice = clsInputValidate::ReadShortNumberBetween(1, 5, "\nInvalid Number! Enter a Number between 1 and 5: ");

		return (enCurrencyExchangeMenuOptions)MenuChoice;

	}

	static void _PrintListCurrenciesScreen() {
		clsCurrenciesListScreen::ShowCurrenciesList();
	}

	static void _ShowFindCurrencyScreen() {
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}

	static void _ShowUpdateRateScreen() {
		clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
	}

	static void _ShowCurrencyCalculatorScreen() {
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
	}

	static void _GoBackToCurrencyExchangeMenu() {
		cout << "\n\nPress any key to back to Currency Exchange Menu..." << endl;
		system("pause>0");
		ShowCurrencyExchangeMenu();
	}

	static void _PerformCurrencyExchangeMenuOptions(enCurrencyExchangeMenuOptions CurrencyExchangeMenuOptions) {
		switch (CurrencyExchangeMenuOptions) {
		case enShowCurrenciesList: {
			system("cls");
			_PrintListCurrenciesScreen();
			_GoBackToCurrencyExchangeMenu();
			break;
		}
		case enFindCurrency: {
			system("cls");
			_ShowFindCurrencyScreen();
			_GoBackToCurrencyExchangeMenu();
			break;
		}
		case enUpdateRate: {
			system("cls");
			_ShowUpdateRateScreen();
			_GoBackToCurrencyExchangeMenu();
			break;
		}
		case enCurrencyCalculator: {
			system("cls");
			_ShowCurrencyCalculatorScreen();
			_GoBackToCurrencyExchangeMenu();
			break;
		}
		case enMainMenu: {}
		}
	}

public:
	static void ShowCurrencyExchangeMenu() {

		system("cls");

		_DrawScreenHeader("\t\tCurrency Exchange Main Screen");

		cout << setw(37) << left << "" << "========================================\n";
		cout << setw(37) << left << "" << "\t\tCurrency Exchange  Menu\n";
		cout << setw(37) << left << "" << "========================================\n";
		cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
		cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
		cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
		cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
		cout << setw(37) << left << "" << "\t[5] Main Menu.\n";
		cout << setw(37) << left << "" << "========================================" << endl;

		_PerformCurrencyExchangeMenuOptions(_ReadCurrencyExchangeMenuOption());
	}
};