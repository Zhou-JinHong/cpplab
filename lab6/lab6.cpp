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

//���μ̳�
//���μ̳лᵼ����������Ͷ�����
//��������һ��ʹ����������̳��������������
//��������̳о���Ϊ��Ӽ̳е���ͬ�Ļ��൥�����ٿռ䣬ֻ��һ�ݡ�
//��ֱ�Ӽ̳е����������ת�����һ��ָ�룬ָ��ָ��һ�ű�
//�������������ָ����������ָ�롣
//������д����ƫ������ֱ�Ӽ̳е����������ͨ��������ҵ���������
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


//��ӡ���
//vs�»������������һ����ָ�룬��������������һ��
//����Ϊ����ֲ�Խϸ���Ҫ�����ӡ���麯����������
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

