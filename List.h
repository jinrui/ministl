/*
 * List.h
 *
 *  Created on: 2015年11月8日
 *      Author: jinrui
 */

#ifndef LIST_H_
#define LIST_H_
#include "Alloc.h"
#include "ReverseIterator.h"
#include "Construct.h"
namespace MiniStl {

	template<typename T>
	struct Node {
		T data;
		Node* next;
		Node* prev;
		Node(const T& _data, Node* _next, Node* _prev) :
				data(_data), next(_next), prev(_prev) {
		}
		Node() :
				data(0), next(0), prev(0) {
		}
		Node(const T& val) :
				data(val), next(0), prev(0) {
		}
		bool operator ==(const Node& other) {
			return this->data == other.data && this->next == other->next
					&& this->prev == other->prev;
		}
	};

	template<typename T>
	class ListIterator: public biDirectionalIterator<T> {
		typedef Node<T>* nodePtr;
		nodePtr np;
	public:
		explicit ListIterator(nodePtr _np) :
				np(_np) {
		}
		ListIterator() :
				np() {
		}
		np& operator ++() {
			np = np->next;
			return *this;
		}
		np operator ++(int) {
			auto tmp = this;
			np = np->next;
			return *tmp;
		}
		np& operator --() {
			np = np->prev;
			return *this;
		}
		np operator --(int) {
			auto tmp = this;
			np = np->prev;
			return *tmp;
		}
		T operator *() {
			return np->data;
		}
		T* operator ->() {
			return &(np->data);
		}
	};
	template<typename T, typename Alloctor = Alloc>
	class List {
		typedef Allocator<Node<T>, Alloctor> dataAlloctor;

		typedef int sizeT;
		typedef int ptrdiffT;
		typedef sizeT sizeType;
		typedef ptrdiffT differenceType;
		typedef T valueType;
		typedef T& ref;
		typedef ListIterator<T> iterator;
		typedef const ref constRef;
		typedef T* pointer;
		typedef ReverseIterator<iterator> reverseIterator;

		iterator head;//双向环状结构
	private:
		/**
		 * 辅助函数
		 */
		iterator newNode(constRef val = 0) {
			auto tmp = dataAlloctor::allocate();
			construct(tmp, Node(val));
			return ListIterator(tmp);
		}
	public:
		/**
		 * 构造函数和析构函数
		 */
		List() {
			head.np = newNode();
			head.np->prev = head.np;
		}
		explicit List(sizeType count, const T& value = T()) {
			for (int i = 0; i < count; i++) {
				push_back(value);
			}
		}

		/**
		 * 迭代器
		 */
		iterator end(){
			return iterator();
		}
		/**
		 * 修饰符
		 */
		void insert(iterator pos, constRef val){
			auto tmp = newNode();
			if(pos.np){
				tmp.np->prev = pos.np->prev;
				tmp.np->next = pos.np;
				pos.np->prev = tmp.np;
			}else{
				if(!head.np) head = tmp;
				else {
					tmp.np->prev = head.np->prev;
					tmp.np->next = tmp.np->prev->next;
					tmp.np->prev->next = tmp.np;
					head.np->prev = tmp.np;
				}
			}
		}

		void push_back(constRef val) {
			insert(end(), val);
		}

	};
}

#endif /* LIST_H_ */
