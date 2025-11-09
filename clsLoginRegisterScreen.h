#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"
#include <fstream>

using namespace std;

class clsLoginRegisterScreen : protected clsScreen
{
private:
	static void _PrintLoginRecordLine(clsUser::stLoginRegisterRecord Record) {

		cout << setw(8) << left << "" << "| " << setw(35) << left << Record.DateTime;
		cout << "| " << setw(20) << left << Record.UserName;
		cout << "| " << setw(20) << left << Record.Password;
		cout << "| " << setw(10) << left << Record.Permissions;
	}

public:
	static void ShowLoginRegisterList() {

		if (!CheckAccessRights(clsUser::enPermissions::pLoginRegister)) {
			return;
		}

		vector <clsUser::stLoginRegisterRecord> vLoginRegisterRecord = clsUser::LoginRegistersList();
		string Title = "\t\tLogin Register List Screen";
		string Subtitle = "\t\t  (" + to_string(vLoginRegisterRecord.size()) + ") Record(s).";

		clsScreen::_DrawScreenHeader(Title, Subtitle);

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
		cout << "| " << left << setw(20) << "UserName";
		cout << "| " << left << setw(20) << "Password";
		cout << "| " << left << setw(10) << "Permissions";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		if (vLoginRegisterRecord.size() == 0) {
			cout << "\t\t\t\tNo Logins Available In the System!";
		}
		else {
			for (clsUser::stLoginRegisterRecord& Record : vLoginRegisterRecord) {
				_PrintLoginRecordLine(Record);
				cout << endl;
			}
		}

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
	}
};