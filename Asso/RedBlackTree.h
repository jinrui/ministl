/*
 * RedBlackTree.h
 *
 *  Created on: 2015年11月24日
 *      Author: apple
 */

#ifndef ASSO_REDBLACKTREE_H_
#define ASSO_REDBLACKTREE_H_
#include "Pair.h"
#include "../Allocator.h"
#include "../Iterator.h"
#include "../Alloc.h"
#include "../ReverseIterator.h"
namespace MiniStl {
	/**
	 * written by saturnman,modified by jinrui
	 */
	template<typename K, typename U, typename alloc = Alloc>
	class RBTree {
	public:
		typedef Pair<K, U> valueType;
		typedef Allocator<valueType, alloc> dataAlloctor;
		typedef valueType& ref;
		typedef valueType* pointer;
		typedef int sizeType;

		RBTree(const RBTree& other) :
				m_nullNode(other.m_nullNode), m_root(other.m_root), start(), finish() {
		}
		/*RBTree() :
		 m_nullNode(0), m_root(0), start(m_root,m_root), finish(0,0) {
		 }*/
	private:
		enum COLOR {
			RED, BLACK
		};
		class RBNode {
		public:
			RBNode() :
					right(0), left(0), parent(0), RB_COLOR(RED) {
			}
			COLOR RB_COLOR;
			RBNode* right;
			RBNode* left;
			RBNode* parent;
			valueType data;
		};
		/**
		 * 迭代器
		 */
		struct RBTIterator: public biDirectionalIterator<K> {
			typedef int sizeT;
			typedef int ptrdiffT;
			typedef sizeT sizeType;
			typedef RBTIterator self;
			RBNode* cur;	//最小的节点
			RBNode* root;	//根节点
			RBTIterator() :
					cur(0), root(0) {
			}
			RBTIterator(RBNode* _cur, RBNode* _root) :
					cur(_cur), root(_root) {
			}
			RBTIterator(const RBTIterator& other) :
					cur(other.cur), root(other.root) {
			}
			/**
			 * 方法很蠢，可以用线索树加速，懒得做
			 */
			RBNode* findLeft(RBNode* node) {
				while (node->left)
					node = node->left;
				return node;
			}
			RBNode* findRight(RBNode* node) {
				while (node->right)
					node = node->right;
				return node;
			}
			self& operator ++() {
				if (cur->right)
					cur = findLeft(cur->right);
				else if (cur->parent && cur == cur->parent->left)
					cur = cur->parent;
				else if (cur->parent && cur == cur->parent->right) {
					auto tmp1 = cur->parent;
					auto tmp2 = cur;
					while (tmp2 != root) {
						if (tmp1->right && tmp2 != tmp1->right) {
							cur = tmp1;
						} else {
							tmp2 = tmp1;
							if (tmp1 == root)
								break;
							tmp1 = tmp1->parent;
						}
					}
					if (tmp2 == root)
						cur = 0;
				} else
					cur = 0;
				return *this;
			}
			self operator ++(int) {
				auto tmp = this;
				++this;
				return *tmp;
			}
			self& operator --() {
				if (cur->left)
					cur = findRight(cur->right);
				else if (cur->parent && cur == cur->parent->right)
					cur = cur->parent;
				else if (cur->parent && cur == cur->parent->left) {
					auto tmp1 = cur->parent;
					auto tmp2 = cur;
					while (tmp2 != root) {
						if (tmp1->left && tmp2 != tmp1->left) {
							cur = tmp1;
						} else {
							tmp2 = tmp1;
							if (tmp1 == root)
								break;
							tmp1 = tmp1->parent;
						}
					}
					if (tmp2 == root)
						cur = 0;
				} else
					cur = 0;
				return *this;
			}
			self operator --(int) {
				auto tmp = this;
				--this;
				return *tmp;
			}
			bool operator <(const self& other) const {
				return cur->data < other.cur->data;
			}
			bool operator !=(const self& other) const {
				return !operator==(other);
			}
			bool operator ==(const RBTIterator& other) {
				return other.cur == cur;
			}
		};
	public:
		typedef RBTIterator iterator;
		typedef ReverseIterator<iterator> reverseIterator;
	public:
		RBTree() {
			this->m_nullNode = new RBNode();
			this->m_root = m_nullNode;
			this->m_nullNode->right = this->m_root;
			this->m_nullNode->left = this->m_root;
			this->m_nullNode->parent = this->m_root;
			this->m_nullNode->RB_COLOR = BLACK;
		}

		bool Empty() {
			if (this->m_root == this->m_nullNode) {
				return true;
			} else {
				return false;
			}
		}
		//查找K
		RBNode* find(K key) {
			RBNode* index = m_root;
			while (index != m_nullNode) {
				if (key < index->data.first) {
					index = index->left;  //比当前的小，往左
				} else if (key > index->data.first) {
					index = index->right;  //比当前的大，往右
				} else {
					break;
				}
			}
			return index;
		}
		bool Insert(valueType data) {
			RBNode* insert_point = m_nullNode;
			RBNode* index = m_root;
			while (index != m_nullNode) {
				insert_point = index;
				if (data.first < index->data.first) {
					index = index->left;
				} else if (data.first > index->data.first) {
					index = index->right;
				} else {
					return false;
				}
			}
			RBNode* insert_node = new RBNode();
			insert_node->data = data;
			insert_node->RB_COLOR = RED;
			insert_node->right = m_nullNode;
			insert_node->left = m_nullNode;
			if (insert_point == m_nullNode) //如果插入的是一颗空树
					{
				m_root = insert_node;
				m_root->parent = m_nullNode;
				m_nullNode->left = m_root;
				m_nullNode->right = m_root;
				m_nullNode->parent = m_root;
			} else {
				if (data.first < insert_point->data.first) {
					insert_point->left = insert_node;
				} else {
					insert_point->right = insert_node;
				}
				insert_node->parent = insert_point;
			}
			InsertFixUp(insert_node);    //调用InsertFixUp修复红黑树性质。
			return true;
		}

		void InsertFixUp(RBNode* node) {
			while (node->parent->RB_COLOR == RED) {
				if (node->parent == node->parent->parent->left)   //
						{
					RBNode* uncle = node->parent->parent->right;
					if (uncle->RB_COLOR == RED)   //插入情况1，z的叔叔y是红色的。
							{
						node->parent->RB_COLOR = BLACK;
						uncle->RB_COLOR = BLACK;
						node->parent->parent->RB_COLOR = RED;
						node = node->parent->parent;
					} else if (uncle->RB_COLOR == BLACK)  //插入情况2：z的叔叔y是黑色的，。
							{
						if (node == node->parent->right) //且z是右孩子
								{
							node = node->parent;
							RotateLeft(node);
						} else                 //插入情况3：z的叔叔y是黑色的，但z是左孩子。
						{
							node->parent->RB_COLOR = BLACK;
							node->parent->parent->RB_COLOR = RED;
							RotateRight(node->parent->parent);
						}
					}
				} else {
					RBNode* uncle = node->parent->parent->left;
					if (uncle->RB_COLOR == RED) {
						node->parent->RB_COLOR = BLACK;
						uncle->RB_COLOR = BLACK;
						uncle->parent->RB_COLOR = RED;
						node = node->parent->parent;
					} else if (uncle->RB_COLOR == BLACK) {
						if (node == node->parent->left) {
							node = node->parent;
							RotateRight(node);     //与上述代码相比，左旋改为右旋
						} else {
							node->parent->RB_COLOR = BLACK;
							node->parent->parent->RB_COLOR = RED;
							RotateLeft(node->parent->parent);   //右旋改为左旋，即可。
						}
					}
				}
			}
			m_root->RB_COLOR = BLACK;
		}

		//左旋代码实现
		bool RotateLeft(RBNode* node) {
			if (node == m_nullNode || node->right == m_nullNode) {
				return false;   //can't rotate
			}
			RBNode* lower_right = node->right;
			lower_right->parent = node->parent;
			node->right = lower_right->left;
			if (lower_right->left != m_nullNode) {
				lower_right->left->parent = node;
			}
			if (node->parent == m_nullNode) //rotate node is root
					{
				m_root = lower_right;
				m_nullNode->left = m_root;
				m_nullNode->right = m_root;
			} else {
				if (node == node->parent->left) {
					node->parent->left = lower_right;
				} else {
					node->parent->right = lower_right;
				}
			}
			node->parent = lower_right;
			lower_right->left = node;
			return true;
		}

		//右旋代码实现
		bool RotateRight(RBNode* node) {
			if (node == m_nullNode || node->left == m_nullNode) {
				return false; //can't rotate
			}
			RBNode* lower_left = node->left;
			node->left = lower_left->right;
			lower_left->parent = node->parent;
			if (lower_left->right != m_nullNode) {
				lower_left->right->parent = node;
			}
			if (node->parent == m_nullNode) //node is root
					{
				m_root = lower_left;
				m_nullNode->left = m_root;
				m_nullNode->right = m_root;
			} else {
				if (node == node->parent->right) {
					node->parent->right = lower_left;
				} else {
					node->parent->left = lower_left;
				}
			}
			node->parent = lower_left;
			lower_left->right = node;
			return true;
		}

		bool Delete(K key) {
			RBNode* delete_point = find(key);
			if (delete_point == m_nullNode) {
				return false;
			}
			if (delete_point->left != m_nullNode
					&& delete_point->right != m_nullNode) {
				RBNode* successor = InOrderSuccessor(delete_point);
				delete_point->data = successor->data;
				delete_point = successor;
			}
			RBNode* delete_point_child;
			if (delete_point->right != m_nullNode) {
				delete_point_child = delete_point->right;
			} else if (delete_point->left != m_nullNode) {
				delete_point_child = delete_point->left;
			} else {
				delete_point_child = m_nullNode;
			}
			delete_point_child->parent = delete_point->parent;
			if (delete_point->parent == m_nullNode) //delete root node
					{
				m_root = delete_point_child;
				m_nullNode->parent = m_root;
				m_nullNode->left = m_root;
				m_nullNode->right = m_root;
			} else if (delete_point == delete_point->parent->right) {
				delete_point->parent->right = delete_point_child;
			} else {
				delete_point->parent->left = delete_point_child;
			}
			if (delete_point->RB_COLOR == BLACK
					&& !(delete_point_child == m_nullNode
							&& delete_point_child->parent == m_nullNode)) {
				DeleteFixUp(delete_point_child);
			}
			delete delete_point;
			return true;
		}

		void DeleteFixUp(RBNode* node) {
			while (node != m_root && node->RB_COLOR == BLACK) {
				if (node == node->parent->left) {
					RBNode* brother = node->parent->right;
					if (brother->RB_COLOR == RED)   //情况1：x的兄弟w是红色的。
							{
						brother->RB_COLOR = BLACK;
						node->parent->RB_COLOR = RED;
						RotateLeft(node->parent);
					} else     //情况2：x的兄弟w是黑色的，
					{
						if (brother->left->RB_COLOR == BLACK
								&& brother->right->RB_COLOR == BLACK)
								//且w的俩个孩子都是黑色的。
										{
							brother->RB_COLOR = RED;
							node = node->parent;
						} else if (brother->right->RB_COLOR == BLACK)
						//情况3：x的兄弟w是黑色的，w的右孩子是黑色（w的左孩子是红色）。
								{
							brother->RB_COLOR = RED;
							brother->left->RB_COLOR = BLACK;
							RotateRight(brother);
						} else if (brother->right->RB_COLOR == RED) {
							brother->RB_COLOR = node->parent->RB_COLOR;
							node->parent->RB_COLOR = BLACK;
							brother->right->RB_COLOR = BLACK;
							RotateLeft(node->parent);
							node = m_root;
						}
					}
				} else {
					RBNode* brother = node->parent->left;
					if (brother->RB_COLOR == RED) {
						brother->RB_COLOR = BLACK;
						node->parent->RB_COLOR = RED;
						RotateRight(node->parent);
					} else {
						if (brother->left->RB_COLOR == BLACK
								&& brother->right->RB_COLOR == BLACK) {
							brother->RB_COLOR = RED;
							node = node->parent;
						} else if (brother->left->RB_COLOR == BLACK) {
							brother->RB_COLOR = RED;
							brother->right->RB_COLOR = BLACK;
							RotateLeft(brother);
						} else if (brother->left->RB_COLOR == RED) {
							brother->RB_COLOR = node->parent->RB_COLOR;
							node->parent->RB_COLOR = BLACK;
							brother->left->RB_COLOR = BLACK;
							RotateRight(node->parent);
							node = m_root;
						}
					}
				}
			}
			m_nullNode->parent = m_root;   //最后将node置为根结点，
			node->RB_COLOR = BLACK;    //并改为黑色。
		}

		//
		inline RBNode* InOrderPredecessor(RBNode* node) {
			if (node == m_nullNode)       //null node has no predecessor
					{
				return m_nullNode;
			}
			RBNode* result = node->left;     //get node's left child
			while (result != m_nullNode) //try to find node's left subtree's right most node
			{
				if (result->right != m_nullNode) {
					result = result->right;
				} else {
					break;
				}
			}    //after while loop result==null or result's right child is null
			if (result == m_nullNode) {
				RBNode* index = node->parent;
				result = node;
				while (index != m_nullNode && result == index->left) {
					result = index;
					index = index->parent;
				}
				result = index;         // first right parent or null
			}
			return result;
		}

		inline RBNode* InOrderSuccessor(RBNode* node) {
			if (node == m_nullNode)       //null node has no successor
					{
				return m_nullNode;
			}
			RBNode* result = node->right;   //get node's right node
			while (result != m_nullNode) //try to find node's right subtree's left most node
			{
				if (result->left != m_nullNode) {
					result = result->left;
				} else {
					break;
				}
			}     //after while loop result==null or result's left child is null
			if (result == m_nullNode) {
				RBNode* index = node->parent;
				result = node;
				while (index != m_nullNode && result == index->right) {
					result = index;
					index = index->parent;
				}
				result = index;         //first parent's left or null
			}
			return result;
		}

		void InOrderTraverse() {
			InOrderTraverse(m_root);
		}

		void InOrderTraverse(RBNode* node) {
			if (node == m_nullNode) {
				return;
			} else {
				InOrderTraverse(node->left);
				InOrderTraverse(node->right);
			}
		}
		~RBTree() {
			clear(m_root);
			delete m_nullNode;
		}
	private:
		// utility function for destructor to destruct object;
		void clear(RBNode* node) {
			if (node == m_nullNode) {
				return;
			} else {
				clear(node->left);
				clear(node->right);
				delete node;
			}
		}
	private:
		RBNode *m_nullNode;
		RBNode *m_root;
		RBTIterator start, finish;
	public:
		RBTIterator& begin() {
			return start;
		}
		RBTIterator& end() {
			return finish;
		}
	};
}

#endif /* ASSO_REDBLACKTREE_H_ */
