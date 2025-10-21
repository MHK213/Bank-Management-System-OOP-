#pragma once

#include <iostream>
#include <vector>

using namespace std;

class clsString
{
private:
	string _Value;
	enum enWhatToCount { SmallLetter = 1, CapitalLetter = 2, All = 3 };

public:
	clsString() {
		_Value = "";
	}

	clsString(string Value) {
		_Value = Value;
	}

	void SetValue(string Value) {
		_Value = Value;
	}

	string GetValue() {
		return _Value;
	}

	__declspec(property(get = GetValue, put = SetValue)) string Value;

	static short Length(string S1) {
		return S1.length();
	}

	short Length() {
		return Length(_Value);
	}

	static void PrintFirstLetterOfEachWord(string Sentence) {
		bool isFirstLetter = true;

		cout << "First Letters of this string: \n";
		for (short i = 0; i < Sentence.length(); i++) {
			if (Sentence[i] != ' ' && isFirstLetter)
				cout << Sentence[i] << " ";

			isFirstLetter = (Sentence[i] == ' ' ? true : false);
		}
	}

	void PrintFirstLetterOfEachWord() {
		PrintFirstLetterOfEachWord(_Value);
	}

	static string UpperFirstLetterOfEachWord(string Sentence) {
		bool isFirstLetter = true;

		for (short i = 0; i < Sentence.length(); i++) {
			if (Sentence[i] != ' ' && isFirstLetter)
				Sentence[i] = toupper(Sentence[i]);

			isFirstLetter = (Sentence[i] == ' ' ? true : false);
		}

		return Sentence;
	}

	void UpperFirstLetterOfEachWord() {
		_Value = UpperFirstLetterOfEachWord(_Value);
	}

	static string LowerFirstLetterOfEachWord(string Sentence) {
		bool isFirstLetter = true;

		for (short i = 0; i < Sentence.length(); i++) {
			if (Sentence[i] != ' ' && isFirstLetter)
				Sentence[i] = tolower(Sentence[i]);

			isFirstLetter = (Sentence[i] == ' ' ? true : false);
		}

		return Sentence;
	}

	void LowerFirstLetterOfEachWord() {
		_Value = LowerFirstLetterOfEachWord(_Value);
	}

	static string LowerAllLetters(string Sentence) {

		for (short i = 0; i < Sentence.length(); i++) {
			Sentence[i] = tolower(Sentence[i]);
		}

		return Sentence;
	}

	void LowerAllLetters() {
		_Value = LowerAllLetters(_Value);
	}

	static string UpperAllLetters(string Sentence) {

		for (short i = 0; i < Sentence.length(); i++) {
			Sentence[i] = toupper(Sentence[i]);
		}

		return Sentence;
	}

	void UpperAllLetters() {
		_Value = UpperAllLetters(_Value);
	}

	static char InvertLetterCase(char Character) {
		return isupper(Character) ? tolower(Character) : toupper(Character);
	}

	static string InvertAllLettersCase(string S1) {
		for (short i = 0; i < S1.length(); i++) {
			S1[i] = InvertLetterCase(S1[i]);
		}

		return S1;
	}

	void InvertAllLettersCase() {
		_Value = InvertAllLettersCase(_Value);
	}

	static short CountLetter(string S1, enWhatToCount WhatToCount = All) {
		short Counter = 0;

		if (WhatToCount == enWhatToCount::All)
			return S1.length();
		for (short i = 0; i < S1.length(); i++) {
			if (WhatToCount == enWhatToCount::CapitalLetter && isupper(S1[i]))
				Counter++;
			else if (WhatToCount == enWhatToCount::SmallLetter && islower(S1[i]))
				Counter++;
		}

		return Counter;
	}

	static short CountCapitalLetter(string S1) {
		return CountLetter(S1, CapitalLetter);
	}

	short CountCapitalLetter() {
		return CountCapitalLetter(_Value);
	}

	static short CountSmallLetter(string S1) {
		return CountLetter(S1, SmallLetter);
	}

	short CountSmallLetter() {
		return CountSmallLetter(_Value);
	}

	static short CountSpecificLetter(string S1, char Letter, bool MatchCase = true) {
		short Counter = 0;

		for (short i = 0; i < S1.length(); i++) {
			if (MatchCase) {
				if (S1[i] == Letter)
					Counter++;
			}
			else {
				if (tolower(S1[i]) == tolower(Letter))
					Counter++;
			}
		}

		return Counter;
	}

	short CountSpecificLetter(char Letter, bool MatchCase = true) {
		return CountSpecificLetter(_Value, Letter, MatchCase);
	}

	static bool IsVowel(char Letter) {
		static const char Vowels[] = { 'a', 'e', 'i', 'o', 'u' };

		for (char v : Vowels) {
			if (tolower(Letter) == v)
				return true;
		}

		return false;
	}

	static short CountVowels(string S1) {
		short Counter = 0;

		for (short i = 0; i < S1.length(); i++) {
			if (IsVowel(S1[i]))
				Counter++;
		}

		return Counter;
	}

	short CountVowels() {
		return CountVowels(_Value);
	}

	static void PrintVowel(string S1) {

		cout << "\nVowels in string are:   ";
		for (short i = 0; i < S1.length(); i++) {
			if (IsVowel(S1[i]))
				cout << S1[i] << "   ";
		}
	}

	void PrintVowel() {
		PrintVowel(_Value);
	}

	static void PrintEachWordInString(string S1) {

		string delim = " ";
		short pos = 0;
		string sWord;

		while ((pos = S1.find(delim)) != std::string::npos) {
			sWord = S1.substr(0, pos);
			if (sWord != "")
				cout << sWord << endl;
			S1.erase(0, pos + delim.length());
		}
		if (S1 != "")
			cout << S1 << endl;
	}

	void PrintEachWordInString() {
		PrintEachWordInString(_Value);
	}

	static short CountWords(string S1) {

		short Count = 0;
		string delim = " ";
		short pos = 0;
		string sWord;

		while ((pos = S1.find(delim)) != std::string::npos) {
			sWord = S1.substr(0, pos);
			if (sWord != "")
				Count++;
			S1.erase(0, pos + delim.length());
		}
		if (S1 != "")
			Count++;

		return Count;
	}

	short CountWords() {
		return CountWords(_Value);
	}

	static vector <string> Split(string Text, string delim) {

		vector <string> vString{};
		short pos = 0;
		string sWord;

		while ((pos = Text.find(delim)) != std::string::npos) {
			sWord = Text.substr(0, pos);
			if (sWord != "")
				vString.push_back(sWord);
			Text.erase(0, pos + delim.length());
		}
		if (Text != "")
			vString.push_back(Text);

		return vString;
	}

	vector <string> Split(string delim) {
		return Split(_Value, delim);
	}

	static string TrimLeft(string Text) {

		for (short i = 0; i < Text.length(); i++) {
			if (Text[i] != ' ')
				return Text.substr(i, Text.length() - i);
		}

		return "";
	}

	void TrimLeft() {
		_Value = TrimLeft(_Value);
	}

	static string TrimRight(string Text) {

		for (short i = Text.length() - 1; i >= 0; i--) {
			if (Text[i] != ' ')
				return Text.substr(0, i + 1);
		}

		return "";
	}

	void TrimRight() {
		_Value = TrimRight(_Value);
	}

	static string Trim(string Text) {

		return TrimLeft(TrimRight(Text));
	}

	void Trim() {
		_Value = Trim(_Value);
	}

	static string JoinString(vector <string> vString, string delim) {

		string Text = "";

		for (string& Word : vString) {
			Text += Word + delim;
		}

		return Text.substr(0, Text.length() - delim.length());
	}

	static string JoinString(string arrString[], short length, string delim) {

		string Text = "";

		for (short i = 0; i < length; i++) {
			Text += arrString[i] + delim;
		}

		return Text.substr(0, Text.length() - delim.length());
	}

	static string ReverseWordsInString(string Text1, string delim) {

		string Text = "";

		vector <string> vReverseString = Split(Text1, delim);
		vector<string>::reverse_iterator iter;

		for (iter = vReverseString.rbegin(); iter != vReverseString.rend(); ++iter) {
			Text += *iter + delim;
		}

		return Text.substr(0, Text.length() - delim.length());
	}

	void ReverseWordsInString(string delim) {
		_Value = ReverseWordsInString(_Value, delim);
	}

	static string ReplaceWords(string String, string delim, string StringToReplace, string ReplaceTo, bool MatchCase = true) {

		string Text = "";

		vector <string> vString = Split(String, delim);
		for (string& Word : vString) {
			if (MatchCase) {
				if (Word == StringToReplace)
					Word = ReplaceTo;
			}
			else {
				if (LowerAllLetters(Word) == LowerAllLetters(StringToReplace))
					Word = ReplaceTo;
			}
		}

		return JoinString(vString, delim);
	}

	string ReplaceWords(string delim, string StringToReplace, string ReplaceTo) {
		return ReplaceWords(_Value, delim, StringToReplace, ReplaceTo);
	}

	static string RemovePounctuationsFromString(string Text) {
		string NewString = "";
		for (short i = 0; i < Text.length(); i++) {
			if (!ispunct(Text[i])) {
				NewString += Text[i];
			}
		}

		return NewString;
	}

	string RemovePounctuationsFromString() {
		return RemovePounctuationsFromString(_Value);
	}

};