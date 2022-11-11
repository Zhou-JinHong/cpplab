#include<iostream>

using namespace std;

typedef void((*VFPTR))();

class Person
{
public:
	Person()
	{
		cout << "Person()" << endl;
	}

	virtual void fun1()
	{
		cout << "Person::fun1()" << endl;
	}
	virtual void fun2()
	{
		cout << "Person::fun2()" << endl;
	}

	~Person()
	{
		cout << "~Person()" << endl;
	}
protected:
	int id = 0;
};

class Student : public virtual Person
{
public:
	Student()
	{
		cout << "Student()" << endl;
	}

	virtual void fun1()
	{
		cout << "Student::fun1()" << endl;
	}

	virtual void fun3()
	{
		cout << "Student::fun3()" << endl;
	}

	~Student()
	{
		cout << "~Student()" << endl;
	}
protected:
	int s_id = 0;
};

class Teacher : public virtual Person
{
public:
	Teacher()
	{
		cout << "Teacher()" << endl;
	}

	~Teacher()
	{
		cout << "~Teacher()" << endl;
	}
protected:
	int t_id = 0;
};

//菱形继承
//菱形继承会导致数组冗余和二义性
//所以我们一般使用菱形虚拟继承来解决他的问题
//菱形虚拟继承就是为间接继承的相同的基类单独开辟空间，只存一份。
//而直接继承的两个基类会转而存放一个指针，指针指向一张表。
//这个表叫做虚基表，指针叫做虚基表指针。
//虚基表中存的是偏移量，直接继承的两个类可以通过虚基表找到公共基类
class Jeson : public Student, public Teacher
{
public:
	Jeson()
	{
		cout << "Jeson()" << endl;
		name[0] = 'w';
	}


	~Jeson()
	{
		cout << "~Jeson()" << endl;
	}
protected:
	char name[8];
};


//打印虚表
//vs下会在虚表的最后会放一个空指针，但其他编译器不一定
//所以为了移植性较高需要把想打印的虚函数个数传入
void print_vfptr(VFPTR* vr, size_t size)
{
	VFPTR* cur = vr;
	for (int i = 0; i < size; i++)
	{
		cout << "vfptr[" << i << ']' << "  ";
		cout << vr[i] << "-->";
		vr[i]();
	}
}


int main()
{
	//Student sd;
	//Person man;
	//print_vfptr((VFPTR*)*(int*)&man, 2);
	//print_vfptr((VFPTR*)*(int*)&sd, 3);

	Jeson Washington;
	return 0;
}

