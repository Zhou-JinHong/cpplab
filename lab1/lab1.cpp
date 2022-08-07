#include<iostream>
#include"lab1.h"
using namespace std;


typedef int STDataType;
class Stack
{
public:
	Stack(int capcity = 4)
	{
		STDataType* na = (STDataType*)malloc(sizeof(STDataType) * capcity);
		if (na == nullptr)
		{
			printf("malloc fail!");
			exit(-1);
		}

		_a = na;
		_capcity = capcity;
		_top = 0;
	}


private:
	STDataType* _a;
	int _capcity;
	int _top;
};


class Queue
{

private:
	Stack _st1;
	Stack _st2;
};



class Date
{
public:
	//Date(int year = 1, int month = 1, int day = 1)
	//{
	//	_year = year;
	//	_month = month;
	//	_day = day;
	//}

	Date(int year, int month, int day)
	{
		_year = year;
		_month = month;
		_day = day;
	}
private:
	int _year;
	int _month;
	int _day;

	//int _year = 1;
	//int _month = 1;
	//int _day = 1;

};



void Person::Init(char* name, char* gen, int high, int weigh)
{
	_name = name;
	_gen = gen;
	_high = high;
	_weigh = weigh;
}

int main()
{
	Stack st1;
	Queue q1;
	//Date d1;
	Date d1(1, 1, 1);
	Person p1;
	p1.Init((char*)"zhangsan", (char*)"nan", 180, 120);
	Person* p2 = nullptr;
	p2->print();

	return 0;
}
