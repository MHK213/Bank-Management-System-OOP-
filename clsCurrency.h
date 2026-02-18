#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "clsString.h"

using namespace std;

class clsCurrency
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1 };
	enMode _Mode;

	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

	static clsCurrency _ConvertLineToCurrencyObject(string Line, string Seprator = "#//#") {

		vector <string> _vCurrencies;
		_vCurrencies = clsString::Split(Line, Seprator);

		return clsCurrency(enMode::UpdateMode, _vCurrencies[0], _vCurrencies[1], _vCurrencies[2], stof(_vCurrencies[3]));
	}

	static vector <clsCurrency> _LoadCurrencyDataFromFile() {

		vector <clsCurrency> _vCurrencies;

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open()) {
			string Line;

			while (getline(MyFile, Line)) {
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				_vCurrencies.push_back(Currency);
			}

			MyFile.close();
		}

		return _vCurrencies;
	}

	string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Seprator = "#//#") {

		string stCurrencyRecord = "";

		stCurrencyRecord += Currency.Country + Seprator;
		stCurrencyRecord += Currency.CurrencyCode + Seprator;
		stCurrencyRecord += Currency.CurrencyName + Seprator;
		stCurrencyRecord += to_string(Currency.Rate);

		return stCurrencyRecord;
	}

	void _SaveCurrencyDataToFile(vector <clsCurrency> _vCurrencies) {

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);

		string DataLine;

		if (MyFile.is_open()) {

			for (clsCurrency& C : _vCurrencies) {
				DataLine = _ConvertCurrencyObjectToLine(C, "#//#");
				MyFile << DataLine << endl;
			}

			MyFile.close();
		}
	}

	void _Update() {

		vector <clsCurrency> _vCurrencies;
		_vCurrencies = _LoadCurrencyDataFromFile();

		for (clsCurrency& C : _vCurrencies) {
			if (C.CurrencyCode == CurrencyCode) {
				C = *this;
				break;
			}
		}
		_SaveCurrencyDataToFile(_vCurrencies);

	}

	static clsCurrency _GetEmptyCurrencyObject() {
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}

public:
	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate) {
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	string GetCountry() {
		return _Country;
	}

	__declspec (property(get = GetCountry)) string Country;

	string GetCurrencyCode() {
		return _CurrencyCode;
	}

	__declspec (property(get = GetCurrencyCode)) string CurrencyCode;

	string GetCurrencyName() {
		return _CurrencyName;
	}

	__declspec (property(get = GetCurrencyName)) string CurrencyName;

	void UpdateRate(float NewRate) {
		_Rate = NewRate;
		_Update();
	}

	float GetRate() {
		return _Rate;
	}

	__declspec (property(get = GetRate)) float Rate;

	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}

	static clsCurrency FindByCode(string CurrencyCode) {
		vector <clsCurrency> vCurrencies;

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);

				if (Currency.CurrencyCode == clsString::UpperAllLetters(CurrencyCode)) {
					MyFile.close();
					return Currency;
				}
				vCurrencies.push_back(Currency);
			}
			MyFile.close();
		}
		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCountry(string Country) {
		vector <clsCurrency> vCurrencies;

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);

				if (clsString::UpperAllLetters(Currency.Country) == clsString::UpperAllLetters(Country)) {
					MyFile.close();
					return Currency;
				}
				vCurrencies.push_back(Currency);
			}
			MyFile.close();
		}
		return _GetEmptyCurrencyObject();
	}

	static bool IsCurrencyExist(string CurrencyCode) {
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		return (!Currency.IsEmpty());
	}

	static vector <clsCurrency> GetCurrenciesList() {
		return _LoadCurrencyDataFromFile();
	}

	float ConvertToUSD(float Amount) {
		return (float)(Amount / Rate);
	}

	float ConvertToOtherCurrency(clsCurrency Currency2, float Amount) {
		float AmountInUSD = ConvertToUSD(Amount);

		if (Currency2.CurrencyCode == "USD")
			return AmountInUSD;

		return (float)(AmountInUSD * Currency2.Rate);
	}
};