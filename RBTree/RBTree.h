#pragma once
#include<utility>
#include<assert.h>


namespace zjh
{
	using std::pair;

	enum color
	{
		RED,
		BLACK
	};

	template<class T>
	struct RBTreeNode
	{
		RBTreeNode<T>* _parent;
		RBTreeNode<T>* _left;
		RBTreeNode<T>* _right;

		T _data;
		color _col;

		RBTreeNode(const T& data)
			:_parent(nullptr)
			,_left(nullptr)
			,_right(nullptr)
			,_data(data)
			,_col(BLACK)
		{}
	};

	template<class T, class Ref, class Ptr>
	struct __RBTreeIterator
	{
		typedef RBTreeNode<T> Node;
		typedef __RBTreeIterator<T, Ref, Ptr> Self;

		Node* _node;


		Ref operator*()
		{
			return _node->_data;
		}

		Ptr operator->()
		{
			return &_node->_data;
		}

		bool operator!=(const Self& s)const
		{
			return _node->_data != s._node->_data;
		}

		bool operator==(const Self& s)const
		{
			return _node->_data == s._node->_data;
		}

		Self& operator++()
		{
			if (_node->_right)
			{
				//��һ��Ϊ������������ڵ�
				Node* left = _node->_right;

				while (left->_left)
				{
					left = left->_left;
				}

				_node = left;
			}
			else
			{
				//��һ��Ϊ���Ӳ��Ǹ��׵��ҵ�����
				Node* parent = _node->_parent;
				Node* cur = _ndoe;

				while (parent && cur == parent->_right)
				{
					cur = parent;
					parent = parent->_parent;
				}

				_node = parent;

				
			}

			return *this;

		}
	};


	template<class K, class V, class KeyOfVal>
	class RBTree
	{
		typedef RBTreeNode<V> Node; 
		
		KeyOfVal kov;

	public:
		typedef __RBTreeIterator<V, V&, V*> iterator;

		iterator begin()
		{
			Node* left = _root;

			while (left->_left)
			{
				left = left->_left;
			}


			return iterator(left);
		}

		iterator end()
		{
			 
			return iterator(nullptr);
		}

		pair<iterator, bool> Insert(const pair<K, V>& kv)
		{
			if (_root == nullptr)
			{
				_root = new Node(kv);
				_root->_col = BLACK;
				return make_pair(iterator(_root), true);
			}
			
			
			Node* cur = _root;
			Node* parent = nullptr;

			while (cur)
			{
				if (kov(cur->_data.first) > kov(kv.first))
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (kov(cur->_data.first) < kov(kv.first))
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					return make_pair(iterator(cur), false);
				}
			}

			Node* newnode = new Node(kv);
			cur = newnode;
			newnode->_col = RED;

			if (cur == parent->_left)
			{
				parent->_left = newnode;
				
			}
			else
			{
				parent->_right = newnode;
			}

			newnode->_parent = parent;

			while (parent && parent->_col == RED)
			{
				Node* grandfather = parent->_parent;
				assert(grandfather);
				assert(grandfather->_col == BLACK);

				if (parent == grandfather->_left)
				{
					Node* uncle = grandfather->_right;

					//���һ��uncle������Ϊ�죬��uncle��parent��ڣ�grandfather��죬Ȼ��������ϴ���
					if (uncle && uncle->_col == RED)
					{
						parent->_col = BLACK;
						uncle->_col = BLACK;
						grandfather->_col = RED;

						cur = grandfather;
						parent = grandfather->_parent;
					}//�������uncle�����ڻ�uncle���ڵ�Ϊ��
					else
					{
						//������parent��ͬ�ࣺparent,grandfather��ɫ+�ҵ���
						if (cur == parent->_left)
						{
							RotateR(grandfather);
							parent->_col = BLACK;
							grandfather->_col = RED;
						}
						else//������parent��ͬ�ࣺparent,grandfather��ɫ+����˫��
						{
							RotateL(parent);
							RotateR(grandfather);
							parent->_col = BLACK;
							grandfather->_col = RED;
						}

						break;
					}
				}
				else
				{
					Node* uncle = grandfather->_left;

					//���һ��
					if (uncle && uncle->_col == RED)
					{
						parent->_col = BLACK;
						uncle->_col = BLACK;
						grandfather->_col = RED;

						cur = grandfather;
						parent = grandfather->_parent;
					}
					else
					{
						//���������ɫ+����
						if (cur == parent->_right)
						{
							RotateL(grandfather);
							parent->_col = BLACK;
							grandfather->_col = RED;
						}
						else
						{
							RotateR(parent);
							RotateL(grandfather);
							parent->_col = BLACK;
							grandfather->_col = RED;
						}

						break;
					}
				}
			}

			_root->_col = BLACK;
			return make_pair(iterator(cur), true);
			
		}

		void InOrder()
		{
			_InOrder(_root);
			std::cout << std::endl;
		}

		bool IsBalance()
		{
			if (_root == nullptr)
			{
				return true;
			}

			if (_root->_col == RED)
			{
				std::cout << "���ڵ㲻�Ǻ�ɫ" << std::endl;
				return false;
			}

			// ��ɫ�ڵ�������׼ֵ
			int benchmark = 0;
			Node* cur = _root;
			while (cur)
			{
			if (cur->_col == BLACK)
			++benchmark;

			cur = cur->_left;
			}

			return PrevCheck(_root, 0, benchmark);
		}

		RBTree()
			:_root(nullptr)
		{}

	private:
		void RotateL(Node* parent)
		{
			Node* subR = parent->_right;
			Node* subRL = subR->_left;

			parent->_right = subRL;
			if (subRL)
				subRL->_parent = parent;

			Node* ppNode = parent->_parent;

			subR->_left = parent;
			parent->_parent = subR;

			if (_root == parent)
			{
				_root = subR;
				subR->_parent = nullptr;
			}
			else
			{
				if (ppNode->_left == parent)
				{
					ppNode->_left = subR;
				}
				else
				{
					ppNode->_right = subR;
				}

				subR->_parent = ppNode;
			}

		}

		void RotateR(Node* parent)
		{
			Node* subL = parent->_left;
			Node* subLR = subL->_right;

			parent->_left = subLR;
			if (subLR)
			{
				subLR->_parent = parent;
			}

			Node* ppNode = parent->_parent;

			subL->_right = parent;
			parent->_parent = subL;

			if (_root == parent)
			{
				_root = subL;
				subL->_parent = nullptr;
			}
			else
			{
				if (ppNode->_left == parent)
				{
					ppNode->_left = subL;
				}
				else
				{
					ppNode->_right = subL;
				}

				subL->_parent = ppNode;
			}

		}

		void RotateLR(Node* parent)
		{
			Node* subL = parent->_left;
			Node* subLR = subL->_right;

			RotateL(parent->_left);
			RotateR(parent);

		}

		void _InOrder(Node* root)
		{
			if (root == nullptr)
			{
				return;
			}

			_InOrder(root->_left);
			std::cout << root->_data.second << " ";
			_InOrder(root->_right);
		}

		bool PrevCheck(Node* root, size_t k, size_t benchmark)
		{
			if (root == nullptr)
			{
				if (k != benchmark)
				{
					std::cout << "�ڽڵ���Ŀ����" << std::endl;
					return false;
				}
				else
				{
					return true;
				}
			}

			if (root->_col == BLACK) { k++; }

			if (root->_col == RED && root->_parent->_col == RED)
			{
				std::cout << "��������ڵ�" << std::endl;
				return false;
			}

			return PrevCheck(root->_left, k, benchmark)
				&& PrevCheck(root->_right, k, benchmark);
		}

		Node* _root;
	};
}