#include<stdio.h>
#include<stdarg.h>


//使用的va_list是一个类型,va_start,va_arg,va_end都是宏。
float average(int n_values, ...)//省略号必须要写，声明定义分离时也要写
{
	//va_list类型的变量用于访问参数列表的未确定部分
	va_list var_arg;
	int count;
	float sum = 0;
	/*
	* 准备接收可变参数
	* 首先通过调用va_start来初始化创建的va_list类型变量。
	* 他的第一个参数是va_list变量的名字，第二个参数是省略号前最后一个有名字的参数。
	* 初始化会让va_list类型变量指向可变参数部分的第一个参数
	*/
	va_start(var_arg, n_values);

	/*
	* 访问可变参数
	* 需要使用va_arg，他接受两个参数，va_list变量和参数列表中下一个参数的类型。
	* va_arg返回这个参数的值并让va_list变量指向下一个参数
	* 这里也证明了，在计算机中的一个数据，决定他类型的不是我们怎么认为，而是怎么去使用。
	* 在计算机内部所有的数据实际上都是二进制
	*/
	for (count = 0; count < n_values; ++count)
	{
		sum += va_arg(var_arg, int);
	}

	/*
	* 当访问完最后一个可变参数后，需要调用va_end
	*/
	va_end(var_arg);

	return sum / n_values;

}


int main()
{
	float sum = average(5, 1, 2, 3, 4, 5);
	printf("%f\n", sum);
	return 0;
}