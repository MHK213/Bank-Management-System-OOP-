#pragma once

#include <iostream>
#include "clsDate.h"

using namespace std;

class clsInputValidate
{
private:
	enum enCompareDate { Before = -1, Equal = 0, After = 1 };

public:
	static bool IsNumberBetween(double From, double To, double Number) {
		return (Number >= From && Number <= To);
	}

	static bool IsNumberBetween(float From, float To, float Number) {
		return (Number >= From && Number <= To);
	}

	static bool IsNumberBetween(int From, int To, int Number) {
		return (Number >= From && Number <= To);
	}

	static bool IsNumberBetween(short From, short To, short Number) {
		return (Number >= From && Number <= To);
	}

	static bool IsDateBetween(clsDate Date, clsDate StartDate, clsDate EndDate) {
		if (clsDate::CompareDates(StartDate, Date) == Before && clsDate::CompareDates(EndDate, Date) == After) {
			return true;
		}

		if (clsDate::CompareDates(StartDate, Date) == After && clsDate::CompareDates(EndDate, Date) == Before) {
			return true;
		}

		return false;
	}

	static int ReadIntNumber(string ErrorMessage = "Invalid Number, Enter Again: ") {
		int Number = 0;

		cout << "Please Enter a number?\n";
		cin >> Number;

		while (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits < std::streamsize>::max(), '\n');

			cout << ErrorMessage << endl;

			cin >> Number;
		}

		return Number;
	}

	static double ReadDblNumber(string ErrorMessage = "Invalid Number, Enter Again: ") {
		double Number = 0;

		cout << "Please Enter a number?\n";
		cin >> Number;

		while (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits < std::streamsize>::max(), '\n');

			cout << ErrorMessage << endl;

			cin >> Number;
		}

		return Number;
	}

	static float ReadFloatNumber(string ErrorMessage = "Invalid Number, Enter Again: ") {
		float Number = 0;

		cin >> Number;

		while (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits < std::streamsize>::max(), '\n');

			cout << ErrorMessage << endl;

			cin >> Number;
		}

		return Number;
	}

	static int ReadIntNumberBetween(int From, int To, string ErrorMessage) {
		int Number = ReadIntNumber();

		while (!IsNumberBetween(From, To, Number)) {
			cout << ErrorMessage;
			Number = ReadIntNumber();
		};

		return Number;
	}

	static double ReadDblNumberBetween(double From, double To, string ErrorMessage) {
		double Number = ReadDblNumber();

		while (!IsNumberBetween(From, To, Number)) {
			cout << ErrorMessage;
			Number = ReadDblNumber();
		};

		return Number;
	}

	static  bool IsValidDate(clsDate Date) {
		return clsDate::IsValidDate(Date);
	}

	static string ReadString() {
		string S1 = "";
		getline(cin >> ws, S1);

		return S1;
	}
};