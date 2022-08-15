#pragma once
#include"Date.h"


//��������
//����������û����Ҫ����ģ����Բ���ʾд��
//~Date


//�������캯��
Date::Date(const Date& d)
{
	_year = d._year;
	_month = d._month;
	_day = d._day;
}

//��ֵ����
// d2 = d3 -> d2.operator=(d3) -> d2.operator=(&d2, d3)
Date& Date::operator=(const Date& d)
{
	_year = d._year;
	_month = d._month;
	_day = d._day;

	return *this;
}

//ȡ��ַ����
Date* Date::operator&()
{
	return this;
}

const Date* Date::operator&() const
{
	return this;
}

// ��ȡĳ��ĳ�µ�����
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

//��������Ƿ���Ϲ���
bool Date::CheckDate()
{
	if ((*this)._day > GetMonthDay((*this)._year, (*this)._month))
	{
		return false;
	}
	return true;
}

// ����+=����

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

// ����+����

Date Date::operator+(int day)
{

	Date d = *this;
	d += day;
	return d;
}

// ����-=����

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

// ����-����

Date Date::operator-(int day)
{
	Date d = *this;
	d -= day;
	return d;
}

//�߼����������
//����
bool Date::operator>(const Date& d)
{
	return (_year > d._year)
		|| (_year == d._year && _month > d._month)
		|| (_year == d._year && _month == d._month && _day > d._day);
}

//С��
bool Date::operator<(const Date& d)
{
	return (_year < d._year)
		|| (_year == d._year && _month < d._month)
		|| (_year == d._year && _month == d._month && _day < d._day);
}

//����
bool Date::operator==(const Date& d)
{
	return (_year == d._year)
		&& (_month == d._month)
		&& (_day == d._day);
}

//���ڵ���
bool Date::operator>=(const Date& d)
{
	return !(*this < d);
}

//С�ڵ���
bool Date::operator<=(const Date& d)
{
	return !(*this > d);
}

//ǰ��++
Date& Date::operator++()
{
	return *this += 1;
}

//����++
Date Date::operator++(int)
{
	Date d = *this;
	*this += 1;
	return d;
}

//ǰ��--
Date& Date::operator--()
{
	return *this -= 1;
}

//����--
Date Date::operator--(int)
{
	Date d = *this;
	*this -= 1;
	return d;
}

//������
bool Date::operator!=(const Date& d)
{
	return !(*this == d);
}


// ����-���� ��������
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

//������תΪ����
void Date::ChangeDay()
{
	Date d1(1, 1, 1);
	int day = *this - d1;
	const char* Day[] = { 0, "��һ", "�ܶ�", "����", "����", "����", "����", "����"};
	cout << Day[day % 7 + 1] << endl;

}