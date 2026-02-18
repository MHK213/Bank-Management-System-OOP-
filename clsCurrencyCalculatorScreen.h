#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

using namespace std;

class clsCurrencyCalculatorScreen : protected clsScreen
{
private:
	static clsCurrency _ReadCurrencyCode(string Message) {
		string CurrencyCode1 = "";

		cout << Message;
		CurrencyCode1 = clsInputValidate::ReadString();

		while (!clsCurrency::IsCurrencyExist(CurrencyCode1)) {
			cout << "\nCurrency Code is not found, Enter another one: ";
			CurrencyCode1 = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode1);

		return Currency;
	}

	static float _ReadAmount() {
		float AmountToExchange = 0;

		cout << "\nEnter Amount to Exchange: ";
		cin >> AmountToExchange;

		return AmountToExchange;
	}

	static void _PrintCurrencyCard(clsCurrency Currency, string Message) {
		cout << Message;
		cout << "\n________________________________________";
		cout << "\nCountry : " << Currency.Country;
		cout << "\nCode    : " << Currency.CurrencyCode;
		cout << "\nName    : " << Currency.CurrencyName;
		cout << "\nRate    : " << Currency.Rate;
		cout << "\n________________________________________" << endl;
	}

	static void _PrintCalculationsResult(clsCurrency CurrencyFrom, clsCurrency CurrencyTo , float AmountToExchange) {

		_PrintCurrencyCard(CurrencyFrom, "\nConvert From");

		float AmountInUSD = CurrencyFrom.ConvertToUSD(AmountToExchange);;

		cout << "\n" << AmountToExchange << " " << CurrencyFrom.CurrencyCode << " = " << AmountInUSD
			<< " USD";

		if (CurrencyTo.CurrencyCode == "USD")
			return;

		cout << "\n\nConvert From USD To";

		_PrintCurrencyCard(CurrencyTo, "\n\nTo");

		cout << "\n" << AmountToExchange << " " << CurrencyFrom.CurrencyCode << " = " << CurrencyFrom.ConvertToOtherCurrency(CurrencyTo, AmountToExchange)
			<< " " << CurrencyTo.CurrencyCode;
	}

public:
	static void ShowCurrencyCalculatorScreen() {

		char Answer = 'N';

		do {

			system("cls");

			_DrawScreenHeader("\t\tCurrency Calculator Screen");

			clsCurrency CurrencyFrom = _ReadCurrencyCode("\nEnter Currency1 Code: ");

			clsCurrency CurrencyTo = _ReadCurrencyCode("\nEnter Currency2 Code: ");

			float AmountToExchange = _ReadAmount();

			_PrintCalculationsResult(CurrencyFrom, CurrencyTo, AmountToExchange);

			cout << "\n\nAre you sure you want to update the rate of this currency y/n? ";
			cin >> Answer;

		} while (toupper(Answer) == 'Y');
	}
};