#pragma once
#include"Date.h"


//析构函数
//对于日期类没有需要清理的，可以不显示写出
//~Date


//拷贝构造函数
Date::Date(const Date& d)
{
	_year = d._year;
	_month = d._month;
	_day = d._day;
}

//赋值重载
// d2 = d3 -> d2.operator=(d3) -> d2.operator=(&d2, d3)
Date& Date::operator=(const Date& d)
{
	_year = d._year;
	_month = d._month;
	_day = d._day;

	return *this;
}

//取地址重载
Date* Date::operator&()
{
	return this;
}

const Date* Date::operator&() const
{
	return this;
}

// 获取某年某月的天数
int Date::GetMonthDay(int year, int month)
{
	static int array[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	int day = array[month];
	if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
	{
		return 29;
	}
	else
		//return day;
		return array[month];

}

//检查日期是否符合规则
bool Date::CheckDate()
{
	if ((*this)._day > GetMonthDay((*this)._year, (*this)._month))
	{
		return false;
	}
	return true;
}

// 日期+=天数

Date& Date::operator+=(int day)
{
	if (day < 0)
	{
		return *this -= (-day);
	}
	_day += day;
	while (_day > GetMonthDay(_year, _month))
	{
		_day -= GetMonthDay(_year, _month);
		_month++;
		if (_month > 12)
		{
			_month = 1;
			_year++;
		}
	}
	return *this;
}

// 日期+天数

Date Date::operator+(int day)
{

	Date d = *this;
	d += day;
	return d;
}

// 日期-=天数

Date& Date::operator-=(int day)
{
	_day -= day;
	while (_day < 0)
	{
		_month--;
		_day += GetMonthDay(_year, _month);
		if (_month < 1)
		{
			_year--;
			_month = 12;
		}
	}
	return *this;
}

// 日期-天数

Date Date::operator-(int day)
{
	Date d = *this;
	d -= day;
	return d;
}

//逻辑运算符重载
//大于
bool Date::operator>(const Date& d)
{
	return (_year > d._year)
		|| (_year == d._year && _month > d._month)
		|| (_year == d._year && _month == d._month && _day > d._day);
}

//小于
bool Date::operator<(const Date& d)
{
	return (_year < d._year)
		|| (_year == d._year && _month < d._month)
		|| (_year == d._year && _month == d._month && _day < d._day);
}

//等于
bool Date::operator==(const Date& d)
{
	return (_year == d._year)
		&& (_month == d._month)
		&& (_day == d._day);
}

//大于等于
bool Date::operator>=(const Date& d)
{
	return !(*this < d);
}

//小于等于
bool Date::operator<=(const Date& d)
{
	return !(*this > d);
}

//前置++
Date& Date::operator++()
{
	return *this += 1;
}

//后置++
Date Date::operator++(int)
{
	Date d = *this;
	*this += 1;
	return d;
}

//前置--
Date& Date::operator--()
{
	return *this -= 1;
}

//后置--
Date Date::operator--(int)
{
	Date d = *this;
	*this -= 1;
	return d;
}

//不等于
bool Date::operator!=(const Date& d)
{
	return !(*this == d);
}


// 日期-日期 返回天数
int Date::operator-(const Date& d) const
{
	Date max = *this;
	Date min = d;

	int flag = 1;
	int n = 0;

	if (max < min)
	{
		max = d;
		min = *this;
		flag = -1;
	}


	while (max > min)
	{
		++min;
		n++;
	}

	return (flag * n);

}

//将日期转为星期
void Date::ChangeDay()
{
	Date d1(1, 1, 1);
	int day = *this - d1;
	const char* Day[] = { 0, "周一", "周二", "周三", "周四", "周五", "周六", "周天"};
	cout << Day[day % 7 + 1] << endl;

}