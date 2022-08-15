#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

class Date
{
	friend  ostream& operator<<(ostream& out, const Date& d);
	friend  istream& operator>>(istream& in, Date& d);

public:
	//���캯��
	//���캯�����ñȽ�Ƶ�������Է����������������������
	Date(int year = 2022, int month = 8, int day = 14)
		:_year(year)
		, _month(month)
		, _day(day)
	{
		assert(CheckDate());
	}

	//��������
	//����������û����Ҫ����ģ����Բ���ʾд��
	//~Date


	//�������캯��
	Date(const Date& d);

	//��ֵ����
	// d2 = d3 -> d2.operator=(d3) -> d2.operator=(&d2, d3)
	Date& operator=(const Date& d);

	//ȡ��ַ����
	Date* operator&();

	const Date* operator&() const;
	
	// ��ȡĳ��ĳ�µ�����
	int GetMonthDay(int year, int month);

	//��������Ƿ���Ϲ���
	bool CheckDate();

	// ����+=����

	Date& operator+=(int day);

	// ����+����

	Date operator+(int day);

	// ����-=����

	Date& operator-=(int day);

	// ����-����

	Date operator-(int day);

	//����
	bool operator>(const Date& d);

	//С��
	bool operator<(const Date& d);

	//����
	bool operator==(const Date& d);

	//���ڵ���
	bool operator>=(const Date& d);

	//С�ڵ���
	bool operator<=(const Date& d);

	//������
	bool operator!=(const Date& d);

	//ǰ��++
	Date& operator++();

	//����++
	Date operator++(int);

	//ǰ��--
	Date& operator--();

	//����--
	Date operator--(int);

	// ����-���� ��������
	int operator-(const Date& d) const;

	//������תΪ����
	void ChangeDay();

private:
	int _year;
	int _month;
	int _day;
};

//���������������
inline ostream& operator<<(ostream& out, const Date& d)
{
	out << d._year << "��" << d._month << "��" << d._day << "��";
	return out;
}

//����ȡ���������
inline istream& operator>>(istream& in, Date& d)
{
	in >> d._year >> d._month >> d._day;

	assert(d.CheckDate());

	return in;
}



