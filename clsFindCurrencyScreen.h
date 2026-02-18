#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"

using namespace std;

class clsFindCurrencyScreen : protected clsScreen
{
private:
	static void _PrintCurrency(clsCurrency Currency) {
		cout << "\nCurrency Card :";
		cout << "\n________________________________________";
		cout << "\nCountry : " << Currency.Country;
		cout << "\nCode    : " << Currency.CurrencyCode;
		cout << "\nName    : " << Currency.CurrencyName;
		cout << "\nRate    : " << Currency.Rate;
		cout << "\n________________________________________" << endl;
	}

	static void _ShowResult(clsCurrency Currency) {
		if (!Currency.IsEmpty()) {
			cout << "\nUser was Found :-)\n";
			_PrintCurrency(Currency);
		}
		else
			cout << "\nUser was Not Found :-(\n";
	}

public:
	static void ShowFindCurrencyScreen() {

		_DrawScreenHeader("\t\tFind Currency Screen");

		short Choice = 1;
		cout << "Find by: [1] Code or [2] Country ? ";

		Choice = clsInputValidate::ReadShortNumberBetween(1, 2, "\nError! Invalid Number, Enter Again? ");

		if (Choice == 1) {

			string CurrencyCode = "";

			cout << "\nEnter Currency Code: ";
			CurrencyCode = clsInputValidate::ReadString();

			clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

			_ShowResult(Currency);
		}
		else if (Choice == 2) {

			string Country = "";

			cout << "\nEnter Country: ";
			Country = clsInputValidate::ReadString();

			clsCurrency Currency = clsCurrency::FindByCountry(Country);

			_ShowResult(Currency);
		}
	}
};