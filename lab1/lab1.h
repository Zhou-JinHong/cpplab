#pragma once
#include<iostream>
using namespace std;


class Person
{
public:
	void Init(char* name, char* gen, int high, int weigh);
	void print()
	{
		cout << "Person-->print" << endl;
	}
private:
	char* _name;
	char* _gen;
	int _high;
	int _weigh;
};