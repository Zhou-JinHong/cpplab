#pragma once
#include<iostream>
#include<assert.h>
#include<string.h>

namespace zzh
{

	template<class T>
	class vector
	{
	public:
		typedef T value_type;
		typedef value_type* iterator;
		typedef const value_type* const_iterator;


		iterator* begin()
		{
			return _start;
		}

		iterator* end()
		{
			return _finish;
		}

		//iterator* rbegin()
		//{
		//	return _finish - 1;
		//}

		//iterator* rend()
		//{
		//	return _start - 1;
		//}

		const_iterator* cbegin() const
		{
			return _start;
		}

		const_iterator* cend() const
		{
			return _finish;
		}


		vector()
			:_start(nullptr)
			,_finish(nullptr)
			,_end_of_storage(nullptr)
		{}

		//v2(v1)拷贝构造
		//老式写法
		//vector(const vector<T>& v)
		//{
		//	_start = new T[v.size()];//或者也可以用capcity
		//	//memcpy(_start, v._start, sizeof(T)*v.size());
		//	for (size_t i = 0; i < v.size(); ++i)
		//	{
		//		_start[i] = v._start[i];
		//	}
		//	_finish = v._finish;
		//	_end_of_storage = v.end_of_storage;
		//}

		//现代写法
		vector(const vector<T>& v)
			:_start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			reverse(v.size());
			for (auto e : v)
			{
				push_back(e);
			}
		}
		vector(const vector<T>& v)
			:_start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			vector<T> tmp(v.cbegin(), v.cend());
			swap(*this, tmp);

		}

		vector(size_t n, const T& val = T())
			:_start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			reserve(n);
			for (size_t i = 0; i < n; ++i)
			{
				push_back(val);
			}
		}

		template <class InputIterator>
		vector(InputIterator first, InputIterator last)
			:_start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}


		~vector()
		{
			delete[] _start;
			_start = _finish = _end_of_storage = nullptr;
		}


		size_t size() const
		{
			return _finish - _start;
		}

		size_t capcity() const
		{
			return _end_of_storage - _start;
		}

		void reverse(size_t n)
		{
			if (n > capcity())
			{
				size_t sz = size();
				T* tmp = new T[n];
				if (_start)
				{
					
					for (size_t i = 0; i < size(); ++i)
					{
						tmp[i] = _start[i];
					}

					delete[] _start;
				}
				_start = tmp;
				_finish = _start + sz;
				_end_of_storage = _start + n;
			}
		}

		void resize(size_t n, const T& val = T())
		{
			if (n > capcity())
			{
				reverse(n);
			}

			if (n > size())
			{
				while (_finish < _start + n)
				{
					*_finish = val;
					++_finish;
				}
			}

			else
			{
				_finish = _start + n;
			}
		}

		vector<T>& operator=(const vector<T> v)
		{
			swap(*this, v);

			return *this;
			
		}


		void swap(vector<T>& v)
		{
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_end_of_storage, v._end_of_storage);
		}

		void push_back(T& x)
		{
			//if (_finish == _end_of_storage)
			//{
			//	reserve(capcity() == 0 ? 4 : 2 * capcity());
			//}

			//*_start = x;
			//_finish++;

			insert(end(), x);

		}

		void pop_back()
		{
			assert(_finish > _start);
			--_finish;
		}

		iterator insert(iterator position, const T& x)
		{
			assert(position >= _start);
			assert(position <= _finish);

			if (_finish == _end_of_storage)
			{
				size_t len = position - _start;
				reserve(capcity() == 0 ? 4 : 2 * capcity());
				position = _start + len;
			}

			//挪动数据
			iterator end = this - 1;
			while (end >= pos)
			{
				*end + 1 = *end;
			}

			*pos = x;
			++_finish;

			return pos;
		}

		void insert(iterator position, size_type n, const value_type& val)
		{
			assert(position >= _start);
			assert(position <= _finish);

			if (_finish == _end_of_storage)
			{
				size_t len = position - _start;
				reserve(capcity() == 0 ? n : capcity() + n);
				position = _start + len;
			}

			//挪动数据
			iterator end = this - 1;
			while (end >= pos)
			{
				*end + n = *end;
			}

			for (int i = 0; i < n; ++i)
			{
				position[i] = val;
			}
			_finish += n;

		}


		// stl 规定erase返回删除位置下一个位置迭代器
		iterator erase(iterator pos)
		{
			assert(pos >= _start);
			assert(pos < _finish)

			iterator end = pos + 1;
			while (end < _finish)
			{
				*(end - 1) = *end;
				++end;
			}
			--_finish;


			return pos;
		}

		T& front()
		{
			assert(size() > 0);

			return *_start;
		}

		T& back()
		{
			assert(size() > 0);

			return *(_finish - 1);
		}



	private:
		iterator* _start;
		iterator* _finish;
		iterator* _end_of_storage;




	};
}