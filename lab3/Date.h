#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

class Date
{
	friend  ostream& operator<<(ostream& out, const Date& d);
	friend  istream& operator>>(istream& in, Date& d);

public:
	//构造函数
	//构造函数调用比较频繁，所以放在类中让它变成内联函数
	Date(int year = 2022, int month = 8, int day = 14)
		:_year(year)
		, _month(month)
		, _day(day)
	{
		assert(CheckDate());
	}

	//析构函数
	//对于日期类没有需要清理的，可以不显示写出
	//~Date


	//拷贝构造函数
	Date(const Date& d);

	//赋值重载
	// d2 = d3 -> d2.operator=(d3) -> d2.operator=(&d2, d3)
	Date& operator=(const Date& d);

	//取地址重载
	Date* operator&();

	const Date* operator&() const;
	
	// 获取某年某月的天数
	int GetMonthDay(int year, int month);

	//检查日期是否符合规则
	bool CheckDate();

	// 日期+=天数

	Date& operator+=(int day);

	// 日期+天数

	Date operator+(int day);

	// 日期-=天数

	Date& operator-=(int day);

	// 日期-天数

	Date operator-(int day);

	//大于
	bool operator>(const Date& d);

	//小于
	bool operator<(const Date& d);

	//等于
	bool operator==(const Date& d);

	//大于等于
	bool operator>=(const Date& d);

	//小于等于
	bool operator<=(const Date& d);

	//不等于
	bool operator!=(const Date& d);

	//前置++
	Date& operator++();

	//后置++
	Date operator++(int);

	//前置--
	Date& operator--();

	//后置--
	Date operator--(int);

	// 日期-日期 返回天数
	int operator-(const Date& d) const;

	//将日期转为星期
	void ChangeDay();

private:
	int _year;
	int _month;
	int _day;
};

//流插入运算符重载
inline ostream& operator<<(ostream& out, const Date& d)
{
	out << d._year << "年" << d._month << "月" << d._day << "日";
	return out;
}

//流提取运算符重载
inline istream& operator>>(istream& in, Date& d)
{
	in >> d._year >> d._month >> d._day;

	assert(d.CheckDate());

	return in;
}



