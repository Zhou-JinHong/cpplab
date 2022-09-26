#include<stdio.h>
#include<stdarg.h>


//ʹ�õ�va_list��һ������,va_start,va_arg,va_end���Ǻꡣ
float average(int n_values, ...)//ʡ�Ժű���Ҫд�������������ʱҲҪд
{
	//va_list���͵ı������ڷ��ʲ����б��δȷ������
	va_list var_arg;
	int count;
	float sum = 0;
	/*
	* ׼�����տɱ����
	* ����ͨ������va_start����ʼ��������va_list���ͱ�����
	* ���ĵ�һ��������va_list���������֣��ڶ���������ʡ�Ժ�ǰ���һ�������ֵĲ�����
	* ��ʼ������va_list���ͱ���ָ��ɱ�������ֵĵ�һ������
	*/
	va_start(var_arg, n_values);

	/*
	* ���ʿɱ����
	* ��Ҫʹ��va_arg������������������va_list�����Ͳ����б�����һ�����������͡�
	* va_arg�������������ֵ����va_list����ָ����һ������
	* ����Ҳ֤���ˣ��ڼ�����е�һ�����ݣ����������͵Ĳ���������ô��Ϊ��������ôȥʹ�á�
	* �ڼ�����ڲ����е�����ʵ���϶��Ƕ�����
	*/
	for (count = 0; count < n_values; ++count)
	{
		sum += va_arg(var_arg, int);
	}

	/*
	* �����������һ���ɱ��������Ҫ����va_end
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