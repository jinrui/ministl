/*
 * List.h
 *
 *  Created on: 2015年11月8日
 *      Author: jinrui
 */

#ifndef LIST_H_
#define LIST_H_
#include "Alloc.h"
namespace MiniStl {

	template<typename T>
	struct Node {
		T data;
		Node* next;
		Node* prev;
		Node(const T& _data, Node* _next, Node* _prev) :
				data(_data), next(_next), prev(_prev) {
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
		typename Allocator<Node<T>, Alloctor> dataAlloctor;
	};
}

#endif /* LIST_H_ */
