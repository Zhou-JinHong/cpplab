#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

template<class T>
class A
{
	T a;
	int b;
};

template<typename T>
void Swap(T& x, T& y)
{
	T tmp;
	tmp = x;
	x = y;
	y = tmp;
}


int main()
{
	A<int> a;
	int x = 0, y = 0;
	Swap(x, y);

	vector<int> v1;
	vector<int> v2;


	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	v1.push_back(5);
	
	v2.push_back(1);
	v2.push_back(2);
	v2.push_back(3);
	v2.push_back(4);
	v2.push_back(5);

	//��������1
	for (size_t i = 0; i < v1.size(); ++i)
	{
		cout << v1[i] << " ";
	}
	cout << endl;

	auto pos = find(v1.begin(), v1.end(), 3);
	v1.insert(pos, 20);


	//��������2
	auto start = v1.begin();
	while (start != v1.end())
	{
		cout << *start << " ";
		++start;
	}
	cout << endl;

	auto p = find(v1.begin(), v1.end(), 3);
	v1.erase(p);
	
	//��Χfor�����Ͼ��ǵ�����
	for (auto e : v1)
	{
		cout << e << " ";
	}
	cout << endl;


	auto cp = v2.rbegin();
	while (cp != v2.rend())
	{
		cout << *cp << " ";
		++cp;
	}
	cout << endl;

	v1.resize(20);
	v1.reserve(40);

}