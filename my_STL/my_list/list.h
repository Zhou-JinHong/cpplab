#pragma once
#include<iostream>
#include<list>
#include<assert.h>
using namespace std;


namespace zjh
{
	template <class T>
	struct __list_node
	{
		typedef __list_node Node;

		Node* _prev;
		Node* _next;
		T _data;

		__list_node(const T& x = T())
			:_data(x)
			,_prev(nullptr)
			,_next(nullptr)
		{}

		Node& operator=(Node& node)
		{
			this = new Node;
			this->_data = node->_data;
			this->_next = node->_next;
			this->_prev = node->_prev;
		}
	};

	template<class T, class Ref, class Ptr>
	struct __list_iterator
	{
		typedef __list_node<T> Node;
		typedef __list_iterator<T, Ref, Ptr> iterator;

		typedef bidirectional_iterator_tag iterator_category;
		typedef T value_type;
		typedef Ptr pointer;
		typedef Ref reference;
		typedef ptrdiff_t difference_type;

		Node* _node;


		__list_iterator(Node* node)
			:_node(node)
		{}

		iterator& operator=(iterator& it)
		{
			_node = it._node;
			return *this;
		}

		bool operator==(const iterator& it)
		{
			return _node == it._node;
		}

		bool operator!=(const iterator& it)
		{
			return _node != it._node;
		}

		//T& operator*()
		Ref operator*()
		{
			return _node->_data;
		}

		
		//T* operator->()
		Ptr operator->()
		{
			return &(operator*());
		}

		iterator& operator++()
		{
			_node = _node->_next;
			return *this;
		}

		iterator& operator++(int)
		{
			Node* tmp(*this);
			_node = _node->_next;
			return tmp;
		}

		iterator& operator--()
		{
			_node = _node->_prev;
			return *this;
		}

		iterator& operator--(int)
		{
			Node* tmp(*this);
			_node = _node->_prev;
			return tmp;
		}


	};

	template <class T>
	class list
	{
		typedef __list_node<T> Node;
		

	public:
		typedef __list_iterator<T, T&, T*> iterator;


		list()
		{
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
		}
		
		~list()
		{
			delete _head;
			_head = nullptr;
		}

		iterator begin()
		{
			return iterator(_head->_next);
		}

		iterator end()
		{
			return iterator(_head);
		}



		void push_back(const T& x)
		{
			//Node* tail = _head->_prev;
			//Node* newnode = new Node(x);

			////head   tail  newnode
			//tail->_next = newnode;
			//newnode->_prev = tail;
			//newnode->_next = _head;
			//_head->_prev = newndoe;

			insert(end(), x);
		}

		void push_front(const T& x)
		{
			insert(begin() + 1, x);
		}

		void pop_back()
		{
			//Node* tail = _head->_next;
			//(tail->_prev)->_next = _head;
			//_head->_next = (tail->_prev);
			//delete tail;

			erase(--end());
		}

		void pop_front()
		{
			erase(begin());
		}

		//任意位置前插入节点
		//防止迭代器失效所以返回新插入节点位置的迭代器
		iterator insert(iterator pos, const T& x)
		{

			Node* newnode = new Node(x);
			Node* prev = pos._node->_prev;

			//prev newnode  pos._node 
			pos._node->_prev = newnode;
			newnode->_prev = prev;
			newnode->_next = pos._node;
			prev->_next = newnode;

			return iterator(newnode);
		}

		//删除任意位置指针
		//防止迭代器失效所以返回删除位置前一个位置的迭代器，
		//但是很多编译器会直接不允许在删除后再次使用原迭代器
		iterator erase(iterator& pos)
		{
			assert(pos != end());

			Node* prev = pos._node->_prev;
			Node* next = pos._node->_next;

			delete pos._node;

			prev->_next = next;
			next->_prev = prev;

			return iterator(next);
		}

		

	private:
		Node* _head;
	};



	void test_list1()
	{
		list<int> lt1;

		lt1.push_back(1);
		lt1.push_back(2);
		lt1.push_back(3);
		lt1.push_back(4);
		lt1.push_back(5);
		lt1.push_back(6);

		list<int>::iterator it = lt1.begin();

		for (auto e : lt1)
		{
			cout << e << ' ';
		}
		cout << endl;

		lt1.pop_back();
		lt1.pop_back();
		lt1.pop_back();

		for (auto e : lt1)
		{
			cout << e << ' ';
		}
		cout << endl;

		cout << *it << endl;

	}
}