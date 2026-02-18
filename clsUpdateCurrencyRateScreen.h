#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"

using namespace std;

class clsUpdateCurrencyRateScreen : protected clsScreen
{
private:

	static float _ReadNewCurrencyRate() {

		float NewRate = 0;

		cout << "\nEnter New Rate? ";
		NewRate = clsInputValidate::ReadFloatNumber();

		return NewRate;
	}

	static void _PrintCurrency(clsCurrency Currency) {
		cout << "\nCurrency Card :";
		cout << "\n________________________________________";
		cout << "\nCountry : " << Currency.Country;
		cout << "\nCode    : " << Currency.CurrencyCode;
		cout << "\nName    : " << Currency.CurrencyName;
		cout << "\nRate    : " << Currency.Rate;
		cout << "\n________________________________________" << endl;
	}

public:
	static void ShowUpdateCurrencyRateScreen() {

		_DrawScreenHeader("\t\tUpdate Currency Rate Screen");

		string CurrencyCode = "";

		cout << "\nEnter Currency Code: ";
		CurrencyCode = clsInputValidate::ReadString();

		while (!clsCurrency::IsCurrencyExist(CurrencyCode)) {
			cout << "\nCurrency Code is not found, Enter another one: ";
			CurrencyCode = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		_PrintCurrency(Currency);

		char Answer = 'N';

		cout << "Are you sure you want to update the rate of this currency y/n? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y') {
			cout << "\n\nUpdate Currency Rate: ";
			cout << "\n________________________";

			Currency.UpdateRate(_ReadNewCurrencyRate());

			cout << "\nCurrency Rate Updated Succesfully\n";
			_PrintCurrency(Currency);
		}
	}
};