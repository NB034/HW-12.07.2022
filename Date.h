#pragma once
#include <iostream>

// Class

class Date {
	int day;
	int month;
	int year;
	int amountOfDays[12]{ 31,28,31,30,31,30,31,31,30,31,30,31 };
public:
	Date(int day = 1, int month = 1, int year = 1970);

	void setDay(int day);
	void setMonth(int month);
	void setYear(int year);

	void setDate(int day);
	void setDate(int day, int month);
	void setDate(int day, int month, int year);

	inline int getDay() const { return this->day; }
	inline int getMonth() const { return this->month; }
	inline int getYear() const { return this->year; }

	void print() const;

	Date& operator++();
	Date& operator--();

	Date operator++(int);
	Date operator--(int);

	Date& operator+=(int days);
	Date& operator-=(int days);
};

// Global functions

bool isLeap(int year) {
	if (year % 4 != 0)
		return false;
	if (year % 100 != 0)
		return true;
	if (year % 400 != 0)
		return false;
	return true;
}

std::ostream& operator<<(std::ostream& out, const Date& date) {
	date.print();
	return out;
}

std::istream& operator>>(std::istream& in, Date& date) {
	int tmp;
	in >> tmp;
	date.setDay(tmp);
	in >> tmp;
	date.setMonth(tmp);
	in >> tmp;
	date.setYear(tmp);
	return in;
}

Date operator+(Date date, int days) {
	Date result{ date };
	result += days;
	return result;
}

Date operator-(Date date, int days) {
	Date result{ date };
	result -= days;
	return result;
}

bool operator<(const Date& left, const Date& right) {
	if (left.getYear() < right.getYear())
		return true;
	if (left.getYear() > right.getYear())
		return false;
	if (left.getMonth() < right.getMonth())
		return true;
	if (left.getMonth() > right.getMonth())
		return false;
	if (left.getDay() < right.getDay())
		return true;
	return false;
}

bool operator==(const Date& left, const Date& right) {
	if (left.getYear() == right.getYear())
		if (left.getMonth() == right.getMonth())
			return left.getDay() == right.getDay();
	return false;
}

bool operator>(const Date& left, const Date& right) {
	return !(left < right || left == right);
}

bool operator<=(const Date& left, const Date& right) {
	return left < right || left == right;
}

bool operator>=(const Date& left, const Date& right) {
	return left > right || left == right;
}

bool operator!=(const Date& left, const Date& right) {
	return !(left == right);
}

// Member functions 

Date::Date(int day, int month, int year) {
	this->setMonth(month);
	this->setDay(day);
	this->setYear(year);
}

void Date::setDay(int day) {
	if (day < 1)
		day = 1;
	if (isLeap(this->year) && this->month == 2 && 29 < day)
		day = 29;
	if (this->amountOfDays[this->month - 1] < day)
		day = this->amountOfDays[this->month - 1];
	this->day = day;
}

void Date::setMonth(int month) {
	if (month < 1)
		month = 1;
	if (12 < month)
		month = 12;
	this->month = month;
}

void Date::setYear(int year) {
	if (year < 1900 || 2099 < year) {
		this->year = 1970;
		return;
	}
	if (isLeap(this->year) && !isLeap(year) && this->month == 2 && this->day == 29)
		(*this)--;
	this->year = year;
}

void Date::setDate(int day) {
	this->setDay(day);
}

void Date::setDate(int day, int month) {
	this->setDay(day);
	this->setMonth(month);
}

void Date::setDate(int day, int month, int year) {
	this->setDay(day);
	this->setMonth(month);
	this->setYear(year);
}

void Date::print() const {
	if (this->day < 10)
		std::cout << '0';
	std::cout << this->day << '.';
	if (this->month < 10)
		std::cout << '0';
	std::cout << this->month << '.' << this->year;
}

Date& Date::operator++() {
	this->day++;
	if (this->day > this->amountOfDays[this->month - 1]) {
		this->day = 1;
		this->month++;
		if (this->month > 12) {
			this->month = 1;
			this->year++;
			if (this->year > 2099)
				this->year--;
		}
	}
	return *this;
}

Date& Date::operator--() {
	this->day--;
	if (this->day < 1) {
		int tmp = this->month - 2;
		if (tmp < 0)
			tmp = 11;
		this->day = this->amountOfDays[tmp];
		this->month--;
		if (this->month < 1) {
			this->month = 12;
			this->year--;
			if (this->year < 1900)
				this->year++;
		}
	}
	return *this;
}

Date Date::operator++(int) {
	Date tmp{ *this };
	++(*this);
	return tmp;
}

Date Date::operator--(int) {
	Date tmp{ *this };
	--(*this);
	return tmp;
}

Date& Date::operator+=(int days) {
	for (size_t i = 0; i < days; i++)
		(*this)++;
	return *this;
}

Date& Date::operator-=(int days) {
	for (size_t i = 0; i < days; i++)
		(*this)--;
	return *this;
}