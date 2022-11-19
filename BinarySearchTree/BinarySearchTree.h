#pragma once
#include<iostream>
#include<assert.h>

using namespace std;

namespace zjh
{
	template<class K>
	struct BSTreeNode
	{

		BSTreeNode<K>* _left;
		BSTreeNode<K>* _right;
		K _key;

		BSTreeNode(const K& key)
			:_left(nullptr)
			,_right(nullptr)
			,_key(key)
		{}

	};

	template<class K>
	class BSTree
	{
		typedef BSTreeNode<K> Node;
	public:

		// C++���÷���ǿ�Ʊ���������Ĭ�ϵĹ���
		BSTree() = default;


		BSTree(const BSTree<K>& t)
		{
			_root = _Copy(t._root);
		}

		BSTree<K>* operator=(BSTree<K>* t)
		{
			swap(_root, t._root);
			return *this;
		}

		//������ȷ����1������ʧ�ܻ��������ظ�����0
		bool Insert(const K& key)
		{
			if (_root == nullptr)
			{
				_root = new Node(key);
				return true;
			}

			Node* parent = nullptr;
			Node* cur = _root;

			while (cur)
			{
				if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if(cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					return false;
				}
			}

			cur = new Node(key);

			if (parent->_key < key)
			{
				parent->_right = cur;
			}
			else
			{
				parent->_left = cur;
			}
			return true;
		}

		bool Find(const K& key)
		{
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key > key)
				{	
					cur = cur->_left;
				}
				else if (cur->_key < key)
				{
					cur = cur->_right;
				}
				else
				{
					return true;
				}
			}
			return false;
		}

		bool Erase(const K& key)
		{
			Node* cur = _root;
			Node* parent = cur;



			while (cur)
			{
				if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					//��ʼɾ��
					//��ڵ�Ϊ��
					if (cur->_left == nullptr)
					{
						if (cur == _root)
						{
							_root = cur->_right;
						}
						else
						{
							if (cur == parent->_left)
							{
								parent->_left = cur->_right;
							}
							else
							{
								parent->_right = cur->_right;
							}
						}
						delete cur;
						cur = nullptr;
					}
					//�ҽڵ�Ϊ��
					else if (cur->_right == nullptr)
					{
						if (cur == _root)
						{
							_root = cur->_right;
						}
						else
						{
							if (cur == parent->_left)
							{
								parent->_left = cur->_left;
							}
							else
							{
								parent->_right = cur->_left;
							}
						}
						delete cur;
						cur = nullptr;
					}
					//���Ҷ���Ϊ��
					else
					{
						Node* Min = cur->_right;
						Node* Minparent = cur;
						while (Min->_left)
						{
							Minparent = Min;
							Min = Min->_left;
						}

						swap(cur->_key, Min->_key);
						if (Minparent->_left == Min)
						{
							Minparent->_left = Min->_right;
						}
						else
						{
							Minparent->_right = Min->_right;
						}

						delete Min;
						return true;
					}
				}
			}

			return false;
		}

		//�������
		void InOrder()
		{
			_InOrder(_root);
			cout << endl;
		}

		///////////////////////////////////////
		//�ݹ�汾


		bool FindR(const K& key)
		{
			return _FindR(_root, key);
		}


		bool InsertR(const K& key)
		{
			return _InsertR(_root, key);
		}

		bool EraseR(const K& key)
		{
			return _EraseR(_root, key);
		}

		~BSTree()
		{
			_Destory(_root);
			
		}

	private:

		void _InOrder(Node* root)
		{
			if (root == nullptr)
			{
				return;
			}
			_InOrder(root->_left);
			cout << root->_key << " ";
			_InOrder(root->_right);
		}

		bool _FindR(Node* root, const K& key)
		{
			if (root == nullptr)
			{
				return false;
			}

			if (root->_key == key)
			{
				return true;
			}
			else if (root->_key > key)
			{
				return _FindR(root->_left, key);
			}
			else
			{
				return _FindR(root->_right, key);
			}

		}

		bool _InsertR(Node*& root, const K& key)
		{

			if (root == nullptr)
			{
				root = new Node(key);
				return true;
			}

			if (root->_key > key)
			{
				return _InsertR(root->_left, key);
			}
			else if(root->_key < key)
			{
				return _InsertR(root->_right, key);
			}
			else
			{
				return false;
			}
		}


		bool _EraseR(Node*& root, const K& key)
		{
			if (root == nullptr)
			{
				return false;
			}

			if (root->_key > key)
			{
				return _EraseR(root->_left, key);
			}
			else if (root->_key < key)
			{
				return _EraseR(root->_right, key);
			}
			else
			{
				Node* del = root;
				//ֻ��һ���ڵ��û�нڵ�ʱ
				if (root->_left == nullptr)
				{
					root = root->_right;
				}
				else if (root->_right == nullptr)
				{
					root = root->_left;
				}
				//�������ڵ�ʱ
				else
				{
					//�ҵ���������С�ڵ��滻ɾ��
					Node* Min = root->_right;
					while (Min->_left)
					{
						Min = Min->_left;
					}
					swap(root->_key, Min->_key);

					return _EraseR(root->_right, key);
				}

				delete del;
				return true;
			}
		}

		Node* _Copy(const Node* root)
		{
			if (root == nullptr)
			{
				return nullptr;
			}

			Node* copynode = new Node(root->key);
			copynode->_left = _Copy(root->_left);
			copynode->_right = _Copy(root->_right);
			return copynode;
		}

		void _Destory(Node* root)
		{
			if (root == nullptr)
			{
				return;
			}

			_Destory(root->_left);
			_Destory(root->_right);

			delete root;
			root = nullptr;
		}

		////////////////////////////////////////////////////////////
		//��Ա
		Node* _root = nullptr;


	};


	//ѭ����ʽ����ɾ�Ĳ���
	void TestBSTree1()
	{
		BSTree<int> b1;
		int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13, 4, 3, 4 };
		for (auto e : a)
		{
			b1.Insert(e);
		}

		// ����+ȥ��
		b1.InOrder();


		b1.Erase(3);
		b1.InOrder();

		b1.Erase(8);
		b1.InOrder();

		for (auto e : a)
		{
			b1.Erase(e);
			b1.InOrder();
		}
	}


	//�ݹ���ʽ����ɾ�Ĳ���
	void TestBSTree2()
	{
		BSTree<int> b1;
		int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13, 4, 3, 4 };
		for (auto e : a)
		{
			b1.InsertR(e);
		}

		// ����+ȥ��
		b1.InOrder();


		b1.EraseR(3);
		b1.InOrder();

		b1.EraseR(8);
		b1.InOrder();

		for (auto e : a)
		{
			b1.EraseR(e);
			b1.InOrder();
		}
	}

}