#pragma once
#pragma warning (disable : 4996)

#include <iostream>
#include <ctime>
#include <vector>
#include <string>

using namespace std;

class clsDate
{
private:
    short _Day = 1;
    short _Month = 1;
    short _Year = 1900;

    vector <string> SplitString(string Text, string delim) {

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

    enum enCompareDate { Before = -1, Equal = 0, After = 1 };

public:
    clsDate() {
        time_t t = time(0);
        tm* now = localtime(&t);

        _Year = now->tm_year + 1900;
        _Month = now->tm_mon + 1;
        _Day = now->tm_mday;
    }

    clsDate(string Date) {
        vector <string> vDate = SplitString(Date, "/");

        _Day = stoi(vDate[0]);
        _Month = stoi(vDate[1]);
        _Year = stoi(vDate[2]);
    }

    clsDate(short Day, short Month, short Year) {
        _Day = Day;
        _Month = Month;
        _Year = Year;
    }

    clsDate(short NumberOfDays, short Year) {
        clsDate Date1 = DateFromDayOrderInAYear(NumberOfDays, Year);

        _Day = Date1.Day;
        _Month = Date1.Month;
        _Year = Date1.Year;
    }

    void SetDay(short Day) {
        _Day = Day;
    }

    short GetDay() {
        return _Day;
    }

    __declspec(property(get = GetDay, put = SetDay)) short Day;

    void SetMonth(short Month) {
        _Month = Month;
    }

    short GetMonth() {
        return _Month;
    }

    __declspec(property(get = GetMonth, put = SetMonth)) short Month;

    void SetYear(short Year) {
        _Year = Year;
    }

    short GetYear() {
        return _Year;
    }

    __declspec(property(get = GetYear, put = SetYear)) short Year;

    void Print() {
        cout << DateToString() << endl;
    }

    static string DateToString(clsDate Date) {
        return to_string(Date.Day) + '/' + to_string(Date.Month) + "/" + to_string(Date.Year);
    }

    string DateToString() {
        return DateToString(*this);
    }

    static clsDate GetSystemDate() {

        short Day, Month, Year;

        time_t t = time(0);
        tm* now = localtime(&t);

        Year = now->tm_year + 1900;
        Month = now->tm_mon + 1;
        Day = now->tm_mday;

        return clsDate(Day, Month, Year);
    }

    static string GetSystemDateTimeString() {

        short Day, Month, Year, Hour, Minute, Second;

        time_t t = time(0);
        tm* now = localtime(&t);

        Year = now->tm_year + 1900;
        Month = now->tm_mon + 1;
        Day = now->tm_mday;
        Hour = now->tm_hour;
        Minute = now->tm_min;
        Second = now->tm_sec;

        return (to_string(Day) + "/" + to_string(Month) + "/" + to_string(Year) +
            "-" + to_string(Hour) + ":" + to_string(Minute) + ":" + to_string(Second));
    }

    static bool IsValidDate(clsDate Date) {
        return (Date.Year >= 0 && (Date.Month > 0 && Date.Month < 13) && (Date.Day <= NumberOfDaysInAMonth(Date.Month, Date.Year) && Date.Day > 0));
    }

    bool IsValid() {
        return IsValidDate(*this);
    }

    static bool IsLeap(short Year) {
        return (Year % 400 == 0) || (Year % 4 == 0 && Year % 100 != 0);
    }

    bool IsLeap() {
        return IsLeap(_Year);
    }

    static short NumberOfDaysInAYear(short Year) {
        return IsLeap(Year) ? 366 : 365;
    }

    short NumberOfDaysInAYear() {
        return NumberOfDaysInAYear(_Year);
    }

    static short NumberOfHoursInAYear(short Year) {
        return NumberOfDaysInAYear(Year) * 24;
    }

    short NumberOfHoursInAYear() {
        return NumberOfHoursInAYear(_Year);
    }

    static int NumberOfMinutesInAYear(short Year) {
        return NumberOfHoursInAYear(Year) * 60;
    }

    int NumberOfMinutesInAYear() {
        return NumberOfMinutesInAYear(_Year);
    }

    static int NumberOfSecondsInAYear(short Year) {
        return NumberOfMinutesInAYear(Year) * 60;
    }

    int NumberOfSecondsInAYear() {
        return NumberOfSecondsInAYear(_Year);
    }

    static short NumberOfDaysInAMonth(short Month, short Year) {

        if (Month <= 0 || Month > 12)
            return 0;

        short arr[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        return (Month == 2) ? (IsLeap(Year) ? 29 : 28) : arr[Month - 1];

    }

    short NumberOfDaysInAMonth() {
        return NumberOfDaysInAMonth(_Month, _Year);
    }

    static short NumberOfHoursInAMonth(short Month, short Year) {
        return NumberOfDaysInAMonth(Month, Year) * 24;
    }

    short NumberOfHoursInAMonth() {
        return NumberOfHoursInAMonth(_Month, _Year);
    }

    static int NumberOfMinutesInAMonth(short Month, short Year) {
        return NumberOfHoursInAMonth(Month, Year) * 60;
    }

    int NumberOfMinutesInAMonth() {
        return NumberOfMinutesInAMonth(_Month, _Year);
    }

    static int NumberOfSecondsInAMonth(short Month, short Year) {
        return NumberOfMinutesInAMonth(Month, Year) * 60;
    }

    int NumberOfSecondsInAMonth() {
        return NumberOfSecondsInAMonth(_Month, _Year);
    }

    static short DayOfWeekOrder(short Day, short Month, short Year) {

        int a = (14 - Month) / 12;
        int y = Year - a;
        int m = Month + 12 * a - 2;

        return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
    }

    short DayOfWeekOrder() {
        return DayOfWeekOrder(_Day, _Month, _Year);
    }

    static string DayName(short DayOfWeekOrder) {
        string arrDaysOfWeek[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

        return arrDaysOfWeek[DayOfWeekOrder];
    }

    static string DayName(short Day, short Month, short Year) {
        string arrDaysOfWeek[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

        return arrDaysOfWeek[DayOfWeekOrder(Day, Month, Year)];
    }

    string DayName() {
        string arrDaysOfWeek[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

        return arrDaysOfWeek[DayOfWeekOrder(_Day, _Month, _Year)];
    }

    static string MonthName(short MonthNumber) {
        string arrMonths[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

        return arrMonths[MonthNumber - 1];
    }

    string MonthName() {
        return MonthName(_Month);
    }

    static void PrintMonthCalendar(short Month, short Year) {

        short Current = DayOfWeekOrder(1, Month, Year);
        short NumberOfDays = NumberOfDaysInAMonth(Month, Year);

        printf("\n  _______________%s_______________\n\n",
            MonthName(Month).c_str());

        printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

        short i;
        for (i = 0; i < Current; i++) {
            printf("     ");
        }

        for (int j = 1; j <= NumberOfDays; j++) {
            printf("%5d", j);

            if (++i == 7) {
                i = 0;
                printf("\n");
            }
        }
        printf("\n  _________________________________\n");
    }

    void PrintMonthCalendar() {
        PrintMonthCalendar(_Month, _Year);
    }

    static void PrintYearCalendar(short Year) {
        printf("\n  _________________________________\n\n");
        printf("           Calendar - %d", Year);
        printf("\n  _________________________________\n");

        for (short i = 1; i <= 12; i++) {
            PrintMonthCalendar(i, Year);
        }
    }

    void PrintYearCalendar() {
        PrintYearCalendar(_Year);
    }

    static short NumberOfDaysFromTheBeginningOfTheYear(short Day, short Month, short Year) {
        short NumberOfDays = 0;

        for (short i = 1; i < Month; i++) {
            NumberOfDays += NumberOfDaysInAMonth(i, Year);
        }

        NumberOfDays += Day;

        return NumberOfDays;
    }

    short NumberOfDaysFromTheBeginningOfTheYear() {
        return NumberOfDaysFromTheBeginningOfTheYear(_Day, _Month, _Year);
    }

    static clsDate DateFromDayOrderInAYear(short RemainingDays, short Year) {

        clsDate Date;

        Date.Year = Year;
        Date.Month = 1;
        Date.Day = 0;

        while (true) {

            short NumberOfDays = NumberOfDaysInAMonth(Date.Month, Year);

            if (RemainingDays >= NumberOfDays) {
                RemainingDays -= NumberOfDays;
                Date.Month++;
            }
            else {
                Date.Day = RemainingDays;
                break;
            }
        }

        return Date;
    }

    void AddDays(short DaysToAdd, clsDate& Date) {

        short RemainingDays = DaysToAdd + NumberOfDaysFromTheBeginningOfTheYear(Date.Day, Date.Month, Date.Year);
        short MonthDays = 0;

        Date.Month = 1;

        while (true) {

            MonthDays = NumberOfDaysInAMonth(Date.Month, Date.Year);

            if (RemainingDays > MonthDays) {

                RemainingDays -= MonthDays;
                Date.Month++;

                if (Date.Month > 12) {

                    Date.Month = 1;
                    Date.Year++;
                }
            }
            else {
                Date.Day = RemainingDays;
                break;
            }
        }

    }

    static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2) {
        return (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ? (Date1.Month < Date2.Month ? true : (Date1.Month == Date2.Month ? Date1.Day < Date2.Day : false)) : false);
    }

    bool IsDate1BeforeDate2(clsDate Date2) {
        return IsDate1BeforeDate2(*this, Date2);
    }

    static bool IsDate1EqualToDate2(clsDate Date1, clsDate Date2) {
        return (Date1.Year == Date2.Year) ? ((Date1.Month == Date2.Month) ? ((Date1.Day == Date2.Day) ? true : false) : false) : false;
    }

    bool IsDate1EqualToDate2(clsDate Date2) {
        return IsDate1EqualToDate2(*this, Date2);
    }

    static bool IsLastDay(clsDate Date) {
        return (Date.Day == NumberOfDaysInAMonth(Date.Month, Date.Year));
    }

    bool IsLastDay() {
        return IsLastDay(*this);
    }

    static bool IsLastMonth(short Month) {
        return (Month == 12);
    }

    bool IsLastMonth() {
        return IsLastMonth(_Month);
    }

    static clsDate AddOneDay(clsDate& Date) {

        if (IsLastDay(Date)) {
            if (IsLastMonth(Date.Month)) {
                Date.Day = 1;
                Date.Month = 1;
                Date.Year++;
            }
            else {
                Date.Day = 1;
                Date.Month++;
            }
        }
        else {
            Date.Day++;
        }

        return Date;
    }

    void AddOneDay() {
        AddOneDay(*this);
    }

    static void  SwapDates(clsDate& Date1, clsDate& Date2) {
        clsDate TempDate;

        TempDate = Date1;
        Date1 = Date2;
        Date2 = TempDate;
    }

    static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false) {

        int Days = 0;
        int SwapFlagValue = 1;

        if (!IsDate1BeforeDate2(Date1, Date2)) {
            SwapDates(Date1, Date2);
            SwapFlagValue = -1;
        }


        while (IsDate1BeforeDate2(Date1, Date2)) {
            Days++;
            Date1 = AddOneDay(Date1);
        }

        return (IncludeEndDay == true) ? ++Days * SwapFlagValue : Days * SwapFlagValue;

    }

    int GetDifferenceInDays(clsDate Date2, bool IncludeEndDay = false) {
        return GetDifferenceInDays(*this, Date2, IncludeEndDay);
    }

    static int CalculateMyAgeInDays(clsDate DateOfBirth) {
        return  GetDifferenceInDays(DateOfBirth, clsDate::GetSystemDate(), true);
    }

    static clsDate IncreaseDateByXDays(clsDate& Date, int NumberOfDays) {

        for (int i = 0; i < NumberOfDays; i++) {
            Date = AddOneDay(Date);
        }

        return Date;
    }

    void IncreaseDateByXDays(int NumberOfDays) {
        IncreaseDateByXDays(*this, NumberOfDays);
    }

    static clsDate IncreaseDateByOneWeek(clsDate& Date) {

        Date = IncreaseDateByXDays(Date, 7);

        return Date;
    }

    void IncreaseDateByOneWeek() {
        IncreaseDateByOneWeek(*this);
    }

    static clsDate IncreaseDateByXWeeks(clsDate& Date, int NumberOfWeeks) {

        for (int i = 0; i < NumberOfWeeks; i++) {
            Date = IncreaseDateByOneWeek(Date);
        }

        return Date;
    }

    void IncreaseDateByXWeeks(int NumberOfWeeks) {
        IncreaseDateByXWeeks(*this, NumberOfWeeks);
    }

    static clsDate IncreaseDateByOneMonth(clsDate& Date) {

        if (IsLastMonth(Date.Month)) {
            Date.Month = 1;
            Date.Year++;
        }
        else {
            Date.Month++;
        }

        short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);

        if (NumberOfDaysInCurrentMonth < Date.Day)
            Date.Day = NumberOfDaysInCurrentMonth;

        return Date;
    }

    void IncreaseDateByOneMonth() {
        IncreaseDateByOneMonth(*this);
    }

    static clsDate IncreaseDateByXMonths(clsDate& Date, int NumberOfMonths) {

        for (int i = 0; i < NumberOfMonths; i++) {
            Date = IncreaseDateByOneMonth(Date);
        }

        return Date;
    }

    void IncreaseDateByXMonths(int NumberOfMonths) {
        IncreaseDateByXMonths(*this, NumberOfMonths);
    }

    static clsDate IncreaseDateByOneYear(clsDate& Date) {

        Date.Year++;
        return Date;
    }

    void IncreaseDateByOneYear() {
        IncreaseDateByOneYear(*this);
    }

    static clsDate IncreaseDateByXYears(clsDate& Date, int NumberOfYears) {

        Date.Year += NumberOfYears;

        return Date;
    }

    void IncreaseDateByXYears(int NumberOfYears) {
        IncreaseDateByXYears(*this, NumberOfYears);
    }

    static clsDate IncreaseDateByOneDecade(clsDate& Date) {

        Date = IncreaseDateByXYears(Date, 10);

        return Date;
    }

    void IncreaseDateByOneDecade() {
        IncreaseDateByOneDecade(*this);
    }

    static clsDate IncreaseDateByXDecadesFaster(clsDate& Date, int NumberOfDecades) {

        Date.Year += (NumberOfDecades * 10);

        return Date;
    }

    void IncreaseDateByXDecadesFaster(int NumberOfDecades) {
        IncreaseDateByXDecadesFaster(*this, NumberOfDecades);
    }

    static clsDate IncreaseDateByOneCentury(clsDate& Date) {

        Date = IncreaseDateByXDecadesFaster(Date, 10);

        return Date;
    }

    void IncreaseDateByOneCentury() {
        IncreaseDateByOneCentury(*this);
    }

    static clsDate IncreaseDateByOneMillennium(clsDate& Date) {

        for (int i = 0; i < 10; i++) {
            Date = IncreaseDateByOneCentury(Date);
        }
        return Date;
    }

    void IncreaseDateByOneMillennium() {
        IncreaseDateByOneMillennium(*this);
    }

    static clsDate DecreaseDateByOneDay(clsDate& Date) {

        if (Date.Day == 1) {
            if (Date.Month == 1) {
                Date.Year--;
                Date.Month = 12;
                Date.Day = 31;
            }
            else {
                Date.Month--;
                Date.Day = NumberOfDaysInAMonth(Date.Month, Date.Year);
            }
        }
        else {
            Date.Day--;
        }

        return Date;
    }

    void DecreaseDateByOneDay() {
        DecreaseDateByOneDay(*this);
    }

    static clsDate DecreaseDateByXDays(clsDate& Date, int NumberOfDays) {

        for (int i = 0; i < NumberOfDays; i++) {
            Date = DecreaseDateByOneDay(Date);
        }

        return Date;
    }

    void DecreaseDateByXDays(int NumberOfDays) {
        DecreaseDateByXDays(*this, NumberOfDays);
    }

    static clsDate DecreaseDateByOneWeek(clsDate& Date) {

        Date = DecreaseDateByXDays(Date, 7);

        return Date;
    }

    void DecreaseDateByOneWeek() {
        DecreaseDateByOneWeek(*this);
    }

    static clsDate DecreaseDateByXWeeks(clsDate& Date, int NumberOfWeeks) {

        for (int i = 0; i < NumberOfWeeks; i++) {
            Date = DecreaseDateByOneWeek(Date);
        }

        return Date;
    }

    void DecreaseDateByXWeeks(int NumberOfWeeks) {
        DecreaseDateByXWeeks(*this, NumberOfWeeks);
    }

    static clsDate DecreaseDateByOneMonth(clsDate& Date) {

        if (Date.Month == 1) {
            Date.Month = 12;
            Date.Year--;
        }
        else {
            Date.Month--;
        }

        short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);

        if (NumberOfDaysInCurrentMonth < Date.Day)
            Date.Day = NumberOfDaysInCurrentMonth;

        return Date;
    }

    void DecreaseDateByOneMonth() {
        DecreaseDateByOneMonth(*this);
    }

    static clsDate DecreaseDateByXMonths(clsDate& Date, int NumberOfMonths) {

        for (int i = 0; i < NumberOfMonths; i++) {
            Date = DecreaseDateByOneMonth(Date);
        }

        return Date;
    }

    void DecreaseDateByXMonths(int NumberOfMonths) {
        DecreaseDateByXMonths(*this, NumberOfMonths);
    }

    static clsDate DecreaseDateByOneYear(clsDate& Date) {

        Date.Year--;
        return Date;
    }

    void DecreaseDateByOneYear() {
        DecreaseDateByOneYear(*this);
    }

    static clsDate DecreaseDateByXYears(clsDate& Date, int NumberOfYears) {

        Date.Year -= NumberOfYears;

        return Date;
    }

    void DecreaseDateByXYears(int NumberOfYears) {
        DecreaseDateByXYears(*this, NumberOfYears);
    }

    static clsDate DecreaseDateByOneDecade(clsDate& Date) {

        Date = DecreaseDateByXYears(Date, 10);

        return Date;
    }

    void DecreaseDateByOneDecade() {
        DecreaseDateByOneDecade(*this);
    }

    static clsDate DecreaseDateByXDecades(clsDate& Date, int NumberOfDecades) {

        Date.Year -= (NumberOfDecades * 10);

        return Date;
    }

    void DecreaseDateByXDecades(int NumberOfDecades) {
        DecreaseDateByXDecades(*this, NumberOfDecades);
    }

    static clsDate DecreaseDateByOneCentury(clsDate& Date) {

        Date = DecreaseDateByXDecades(Date, 10);

        return Date;
    }

    void DecreaseDateByOneCentury() {
        DecreaseDateByOneCentury(*this);
    }

    static clsDate DecreaseDateByOneMillennium(clsDate& Date) {

        for (int i = 0; i < 10; i++) {
            Date = DecreaseDateByOneCentury(Date);
        }
        return Date;
    }

    void DecreaseDateByOneMillennium() {
        DecreaseDateByOneMillennium(*this);
    }

    static bool IsEndOfWeek(clsDate Date) {
        return DayOfWeekOrder(Date.Day, Date.Month, Date.Year) == 6;
    }

    bool IsEndOfWeek() {
        return IsEndOfWeek(*this);
    }

    static bool IsWeekEnd(clsDate Date) {
        return (DayOfWeekOrder(Date.Day, Date.Month, Date.Year) == 5 || DayOfWeekOrder(Date.Day, Date.Month, Date.Year) == 6);
    }

    bool IsWeekEnd() {
        return IsWeekEnd(*this);
    }

    static bool IsBusinessDay(clsDate Date) {
        return (!IsWeekEnd(Date));
    }

    bool IsBusinessDay() {
        return IsBusinessDay(*this);
    }

    static short DaysUntilTheEndOfWeek(clsDate Date) {
        return 6 - DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
    }

    short DaysUntilTheEndOfWeek() {
        return DaysUntilTheEndOfWeek(*this);
    }

    static short DaysUntilTheEndOfMonth(clsDate Date) {
        return NumberOfDaysInAMonth(Date.Month, Date.Year) - Date.Day;
    }

    short DaysUntilTheEndOfMonth() {
        return DaysUntilTheEndOfMonth(*this);
    }

    static short DaysUntilTheEndOfYear(clsDate Date) {
        short YearDays = (IsLeap(Date.Year)) ? 366 : 365;
        return YearDays - NumberOfDaysFromTheBeginningOfTheYear(Date.Day, Date.Month, Date.Year);

    }

    short DaysUntilTheEndOfYear() {
        return DaysUntilTheEndOfYear(*this);
    }

    static short CalculateVacationDays(clsDate StartDate, clsDate EndDate) {
        short VacationDays = 0;
        while (IsDate1BeforeDate2(StartDate, EndDate)) {
            if (!IsWeekEnd(StartDate))
                VacationDays++;

            StartDate = AddOneDay(StartDate);
        }

        return VacationDays;
    }

    static clsDate CalculateVacationReturnDate(clsDate FromDate, short VacationDays) {
        while (VacationDays > 0) {
            if (!IsWeekEnd(FromDate))
                VacationDays--;

            FromDate = AddOneDay(FromDate);
        }

        while (IsWeekEnd(FromDate)) {
            FromDate = AddOneDay(FromDate);
        }

        return FromDate;
    }

    static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2) {
        return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualToDate2(Date1, Date2));
    }

    bool IsDate1AfterDate2(clsDate Date2) {
        return IsDate1AfterDate2(*this, Date2);
    }

    static enCompareDate CompareDates(clsDate Date1, clsDate Date2) {

        if (IsDate1BeforeDate2(Date1, Date2))
            return Before;
        else if (IsDate1EqualToDate2(Date1, Date2))
            return Equal;
        else
            return After;

    }

    enCompareDate CompareDates(clsDate Date2) {
        return CompareDates(*this, Date2);
    }
};