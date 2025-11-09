#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include <fstream>
#include "clsTransferLogScreen.h"
#include "clsBankClient.h"

using namespace std;

class clsTransferLogScreen : protected clsScreen
{
private:
	static void _PrintTransferLogRecordLine(clsBankClient::stTransferLogRecord Record) {

		cout << setw(8) << left << "" << "| " << setw(23) << left << Record.DateTime;
		cout << "| " << setw(8) << left << Record.SourceAccNumber;
		cout << "| " << setw(8) << left << Record.DestinationAccNumber;
		cout << "| " << setw(8) << left << Record.Amount;
		cout << "| " << setw(10) << left << Record.SourceBalance;
		cout << "| " << setw(10) << left << Record.DestinationBalance;
		cout << "| " << setw(8) << left << Record.UserName;
	}

public:
	static void ShowTransferLogList() {

		vector <clsBankClient::stTransferLogRecord> vTransferLogRecord = clsBankClient::GetTransferLogList();
		string Title = "\t\tTransfer Log List Screen";
		string Subtitle = "\t\t  (" + to_string(vTransferLogRecord.size()) + ") Transfer(s).";

		clsScreen::_DrawScreenHeader(Title, Subtitle);

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
		cout << "| " << left << setw(8) << "s.Acct";
		cout << "| " << left << setw(8) << "d.Acct";
		cout << "| " << left << setw(8) << "Amount";
		cout << "| " << left << setw(10) << "s.Balance";
		cout << "| " << left << setw(10) << "d.Balance";
		cout << "| " << left << setw(8) << "User";

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		if (vTransferLogRecord.size() == 0) {
			cout << "\t\t\t\tNo Transfers Available In the System!";
		}
		else {
			for (clsBankClient::stTransferLogRecord& Record : vTransferLogRecord) {
				_PrintTransferLogRecordLine(Record);
				cout << endl;
			}
		}

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
	}
};