#pragma once
#include"Date.h"

void Testmenu()
{
	int input = 0;
	do
	{
		printf("***************���ڼ�����*****************\n");
		printf("   1. ���ڼ�����     2.���ڼӼ�����\n");
		printf("   3. ���ڶ�Ӧ����   -1. �˳�\n");
		printf("*****************************************\n");
		printf("��ѡ��\n");
		cin >> input;
		if (input == 1)
		{
			Date d1;
			Date d2;
			cout << "���������������������ڣ�����ݣ�������֮��ʹ�ûس�����" << endl;
			cin >> d1 >> d2;
			cout << (d1 - d2) << endl;
		}
		else if (input == 2)
		{
			int day = 0;
			Date d1;
			cout << "�����������ں�������������ȥ�����Ļ������븺ֵ" << endl;
			cin >> d1 >> day;
			cout << (d1 + day) << endl;
		}
		else if (input == 3)
		{
			Date d;
			cout << "����������ת��������" << endl;
			cin >> d;
			d.ChangeDay();
		}
		else
		{
			cout << "ѡ�����������ѡ��" << endl;
		}


	}while(input);
}

int main()
{

	Testmenu();

	return 0;
}
