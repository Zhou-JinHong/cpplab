#pragma once
#include"Date.h"

void Testmenu()
{
	int input = 0;
	do
	{
		printf("***************日期计算器*****************\n");
		printf("   1. 日期减日期     2.日期加减天数\n");
		printf("   3. 日期对应星期   -1. 退出\n");
		printf("*****************************************\n");
		printf("请选择：\n");
		cin >> input;
		if (input == 1)
		{
			Date d1;
			Date d2;
			cout << "请输入你想计算的两个日期（带年份），日期之间使用回车隔开" << endl;
			cin >> d1 >> d2;
			cout << (d1 - d2) << endl;
		}
		else if (input == 2)
		{
			int day = 0;
			Date d1;
			cout << "依次输入日期和天数，如果想减去天数的话就输入负值" << endl;
			cin >> d1 >> day;
			cout << (d1 + day) << endl;
		}
		else if (input == 3)
		{
			Date d;
			cout << "请输入你想转换的日期" << endl;
			cin >> d;
			d.ChangeDay();
		}
		else
		{
			cout << "选择错误，请重新选择！" << endl;
		}


	}while(input);
}

int main()
{

	Testmenu();

	return 0;
}
