#include<iostream>
#include<math.h>
using namespace std;


/*
* class Date

{

public:

// 获取某年某月的天数

int GetMonthDay(int year, int month);



  // 全缺省的构造函数

Date(int year = 1900, int month = 1, int day = 1);



  // 拷贝构造函数

// d2(d1)

Date(const Date& d);

   

  // 赋值运算符重载

// d2 = d3 -> d2.operator=(&d2, d3)

Date& operator=(const Date& d);



  // 析构函数

~Date();



  // 日期+=天数

Date& operator+=(int day);



  // 日期+天数

Date operator+(int day);



  // 日期-天数

Date operator-(int day);



   // 日期-=天数

Date& operator-=(int day);



  // 前置++

Date& operator++();



  // 后置++

Date operator++(int);



  // 后置--

Date operator--(int);



  // 前置--

Date& operator--();



  // >运算符重载

bool operator>(const Date& d);



  // ==运算符重载

bool operator==(const Date& d);



  // >=运算符重载

bool operator >= (const Date& d);

   

  // <运算符重载

bool operator < (const Date& d);



   // <=运算符重载

bool operator <= (const Date& d);



  // !=运算符重载

bool operator != (const Date& d);



  // 日期-日期 返回天数

int operator-(const Date& d);

private:

int _year;

int _month;

int _day;

};
*/



class Date
{
public:
	// 获取某年某月的天数
	int GetMonthDay(int year, int month)
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
	// 全缺省的构造函数
	Date(int year = 2022, int month = 8, int day = 8)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	//Date类没有需要清理的，所以不需要写析构函数
	//~Date()

	//拷贝构造函数
	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	// 赋值运算符重载

	// d2 = d3 -> d2.operator=(d3) -> d2.operator=(&d2, d3)

	Date& operator=(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;

		return *this;
	}



	// 日期+=天数

	Date& operator+=(int day)
	{
		_day += day;
		while(_day > GetMonthDay(_year, _month))
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

	Date operator+(int day)
	{
		//_day += day;
		Date d = *this;
		//while (d._day > GetMonthDay(d._year, d._month))
		//{
		//	d._month++;
		//	d._day -= GetMonthDay(d._year, d._month);
		//	if (d._month > 12)
		//	{
		//		d._month = 1;
		//		d._year++;
		//	}
		//}
		d += day;
		return d;
	}

	// 日期-=天数

	Date& operator-=(int day)
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

	Date operator-(int day)
	{
		Date d = *this;
		//d._day -= day;
		//while (d._day < 0)
		//{
		//	d._month--;
		//	d._day += GetMonthDay(d._year, d._month);
		//	if (d._month < 1)
		//	{
//		d._year--;
//		d._month = 12;
//	}
//}
		d -= day;
		return d;
	}

	// 前置++

	Date& operator++()
	{
		*this += 1;
		return *this;
	}

	// 后置++

	Date operator++(int)
	{
		Date d = *this;
		*this += 1;
		return d;
	}

	// 前置--

	Date& operator--()
	{
		return *this -= 1;
	}

	// 后置--

	Date operator--(int)
	{
		Date d = *this;
		*this -= 1;
		return d;
	}

	// >运算符重载

	bool operator>(const Date& d)
	{
		return (_year > d._year)
			|| (_month > d._month)
			|| (_year == d._year && _month == d._month && _day > d._day);
	}

	// ==运算符重载

	bool operator==(const Date& d)
	{
		return (_year == d._year)
			&& (_month == d._month)
			&& (_day == d._day);
	}

	// >=运算符重载

	bool operator >= (const Date& d)
	{
		return (*this > d) || (*this == d);
	}

	// <运算符重载

	bool operator < (const Date& d)
	{
		return (_year < d._year)
			|| (_month < d._month)
			|| (_year == d._year && _month == d._month && _day < d._day);
	}

	// <=运算符重载

	bool operator <= (const Date& d)
	{
		return (*this < d) || (*this == d);
	}

	// !=运算符重载

	bool operator != (const Date& d)
	{
		return !(*this == d);
	}



	// 日期-日期 返回天数

	int operator-(const Date& d) const
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
			min++;
			n++;
		}

		return flag * n;

	}

private:
	//int _year = 1;
	//int _month = 1;
	//int _day = 1;

	int _year;
	int _month;
	int _day;
};

int main()
{
	Date d1;
	Date d2(2022, 8, 9);
	Date d3(2000, 9, 10);
	//Date d3 = d2;
	//Date d4;
	//d4 = d4 + 35;
	//++d4;
	//d3 = d4++;
	cout << (d3 - d2) << endl;
	return 0;
}