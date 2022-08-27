#pragma once
#pragma warning(disable:4996)

#include<iostream>
#include<assert.h>

using std::exception;
using std::cout;
using std::endl;
using std::cin;
using std::swap; 


namespace zzh
{
	class string
	{
	public:

		typedef char* iterator;
		typedef const char* const_iterator;

		iterator begin()
		{
			return _str;
		}

		iterator end()
		{
			return _str + _size;
		}

		const_iterator begin() const
		{
			return _str;
		}

		const_iterator end() const
		{
			return _str + _size;
		}



		//string()
		//	:_str(new char[1])
		//	, _size(0)
		//	, _capcity(0)
		//{
		//	*_str = "\0";
		//}当有了全缺省的构造函数就没有必要再写一个无参的

		//不能用下面的方式构造
		//string()
		//	:_str(nullptr)
		//	,_size(0)
		//	,_capcity(0)
		//{}这样初始化的话，如果我们给了一个空str再去调用它的c_str函数程序会崩溃。
		
		//string(const char* str = "\0")
		//	//:_size(strlen(str))
		//	//,_capcity(_size)
		//	//,_str(new char[_capcity + 1])
		//	//如果string使用这种初始化列表来构造的话，会非常依赖声明的顺序，如果以后在家了一些东西的话可能会出错，所以这里不用初始化列表会更好一点。
		//{
		//		_size = strlen(str);
		//		_capcity = _size;
		//		_str = new char[_capcity + 1];
		//		strcpy(_str, str);
		//		cout << e.what() << endl;
		//}缺省值可以给\0，但是直接给空字符串看起来更好一点，并且字符串默认会带\0.

		//构造函数最优写法
		string(const char* str = "")
		{
				_size = strlen(str);
				_capcity = _size;
				_str = new char[_capcity + 1];

				strcpy(_str, str);
		}



		//拷贝构造
		//传统写法
		//string(const string& s)
		//	:_str(new char[s._capcity + 1])
		//	, _size(s._size)
		//	, _capcity(s._capcity)
		//{
		//	strcpy(_str, s._str);
		//}

		//现代写法 -- 老板思维
		string(const string& s)
			:_str(nullptr)
			, _size(0)
			, _capcity(0)
		{
			string s1(s._str);
			swap(s1);
		}

		//赋值重载
		string& operator=(const char* s)
		{
			if (strlen(s) > _capcity)
			{
				reserve(strlen(s));
			}

			strcpy(_str, s);
			_size = strlen(s);

			return *this;
		}

		//string& operator= (const string& str)
		//{
		//	if (str._size > _capcity)
		//	{
		//		reserve(str._size);
		//	}

		//	strcpy(_str, str._str);
		//	_size = str._size;

		//	return *this;
		//}
		
		//简化写法
		string& operator=(string s)
		{
			swap(s);
			return *this;
		}





		//扩容
		void reserve(size_t n = 0)
		{
			if (n > _capcity)
			{
				char* newstr = new char[n + 1];
				_capcity = n;

				strcpy(newstr, _str);
				delete[] _str;
				_str = newstr;
			}
		}


		//扩容并初始化
		void resize(size_t n = 0, char c = '\0')
		{
			//if (n > _capcity)
			//{
			//	char* newstr = new char[n + 1];
			//	_capcity = n;

			//	strcpy(newstr, _str);

			//	for (size_t i = _size; i < _capcity; i++)
			//	{
			//		newstr[i] = 'c';
			//	}
			//	delete[] _str;
			//	_str = newstr;

			//	_size = n;
			//}

			if (n > _size)
			{
				// 插入数据
				reserve(n);
				for (size_t i = _size; i < n; ++i)
				{
					_str[i] = c;
				}
				_str[n] = '\0';
				_size = n;
			}
			else
			{
				// 删除数据
				_str[n] = '\0';
				_size = n;
			}
			

		}


		//string类特定的交换函数、
		void swap(string& tmp)
		{
			::swap(_size, tmp._size);
			::swap(_capcity, tmp._capcity);
			::swap(_str, tmp._str);
		}


		//重载[]
		char& operator[](size_t n)
		{
			assert(n < _size);

			return *(_str + n);
		}

		//尾插
		void push_back(char c)
		{
			if (_size == _capcity)
			{
				reserve(_capcity == 0 ? 4: 2 * _capcity);
			}
			_str[_size] = c;
			_size++;
			_str[_size] = '\0';
		}

		//尾插字符串
		void append(const char* str)
		{
			if ((_size + strlen(str)) > _capcity)
			{
				reserve(_size + strlen(str));
			}

			strcpy(_str + _size, str);
			_size += strlen(str);
		}

		//+=重载
		string& operator+=(const char* str)
		{
			append(str);

			return *this;
		}

		string& operator+=(const string& s)
		{
			append(s._str);

			return *this;
		}

		string& operator+=(char ch)
		{
			push_back(ch);

			return *this;
		}

		//随机位置插入
		string& insert(size_t pos, char ch)
		{
			assert(pos < _size);

			//如果空间不够就先扩容
			if (_size + 1 > _capcity)
			{
				reserve(_capcity == 0 ? 4 : _capcity * 2);
			}

			//移动数据
			for (size_t i = _size + 1; i > pos; i--)
			{
				_str[i] = _str[i - 1];
			}

			_str[pos] = ch;
			++_size;

			return *this;
		}

		string& insert(size_t pos, const char* str)
		{
			//如果空间不够就先扩容
			size_t len = strlen(str);
			if (_size + len > _capcity)
			{
				reserve(_size + len);
			}

			//挪动数据
			size_t end = _size + len;
			while (end > pos + len)
			{
				_str[end] = _str[end - len];
				--end;
			}

			strncpy(_str + _size, str, len);
			_size += len;

		}

		//清除数据
		void erase(size_t pos = 0, size_t len = npos)
		{
			assert(pos < _size);
			assert(pos >= 0);

			if (len == pos || (pos + len) >= _size)
			{
				_str[pos] = '\0';
				_size = 0;
			}
			else
			{
				strcpy(_str + pos, _str + pos + len);
				_size -= len;
			}
		}

		//以C语言字符串的形式返回
		const char* c_str() const
		{
			return _str;
		}

		//返回string有效字符长度
		size_t size()
		{
			return _size;
		}

		//在string中最大长度是固定的
		size_t max_size()
		{
			return npos;
		}

		//容量
		size_t capcity()
		{
			return _capcity;
		}

		//判断string是否为空
		bool empty()
		{
			return _size == 0;
		}

		void clear()
		{
			_str[0] = '\0';
			_size = 0;
		}

		size_t find(char ch, size_t pos = 0) const
		{
			assert(pos < _size);
			for (size_t i = pos; i < _size; i++)
			{
				if (_str[i] == ch)
				{
					return i;
				}
			}
			return npos;

		}
		size_t find(const char* sub, size_t pos = 0) const
		{
			assert(sub);
			assert(pos < _size);

			char* ret = strstr(_str + pos, sub);
			if (ret == nullptr)
			{
				return npos;
			}
			else
			{
				return ret - _str;
			}
		}



		bool operator>(const string& s) const
		{
			return strcmp(_str, s._str) > 0;
		}

		bool operator==(const string& s) const
		{
			return strcmp(_str, s._str) == 0;
		}

		bool operator>=(const string& s) const
		{
			return *this > s || *this == s;
		}

		bool operator<=(const string& s) const
		{
			return !(*this > s);
		}

		bool operator<(const string& s) const
		{
			return !(*this >= s);
		}

		bool operator!=(const string& s) const
		{
			return !(*this == s);
		}


	private:
		size_t _size;
		size_t _capcity;
		char* _str;


	public:

		//c++的一个语法特性是静态成员变量当加了const之后可以直接在生命的地方初始化
		static const size_t npos = -1;
		
	};


	void Teststring1()
	{
		string s1("hello");
		string s2(s1);
	}

	void Teststring2()
	{
		string s1("hello");

		string s2("world");

		s1 = "kimoyideisi";
		s2 = s1;

		s1.push_back('1');
		s1.push_back('2');
		s1.push_back('3');

		const char* a = s1.c_str();
		cout << a << endl;

		s2.append("heiheihei");
	}

	std::ostream& operator<<(std::ostream& out, string& s)
	{
		for (int i = 0; i < s.size(); ++i)
		{
			out << s[i];
		}
		return out;
	}

	std::istream& operator>>(std::istream& in, string& s)
	{
		s.clear();

		//因为输入的字符串可能带有空格，所以使用get函数解决
		char ch;
		ch = in.get();

		const size_t N = 32;
		char buff[N];
		size_t i = 0;

		while (ch != ' ' && ch != '\n')
		{
			buff[i++] = ch;
			if (i == N - 1)
			{
				buff[i] = '\0';
				s += buff;
				i = 0;
			}

			ch = in.get();
		}

		buff[i] = '\0';
		s += buff;

		return in;
	}

	void Teststring3()
	{
		string s1("hello");
		string s2(s1);

		s1 += "world";
		s1 += '!';
		s2 += s1;

	}

	void Teststring4()
	{
		string s1("hello");
		std::string s2("kemoji");


		s1.resize(20, 'd');
		s1.resize(40, 'c');
	}

	void Teststring5()
	{
		string s1("hello");
		string s2(s1);

		s1.insert(3, 'x');
	}

	
}


