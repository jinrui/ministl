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
		typedef int sizeT;
		typedef int ptrdiffT;
		typedef sizeT sizeType;
		nodePtr np;
	public:
		explicit ListIterator(nodePtr _np) :
				np(_np) {
		}
		ListIterator() :
				np(0) {
		}
		ListIterator(const ListIterator& other) :
				np(other.np) {
		}
		ListIterator& operator =(const ListIterator& other) {
			ListIterator tmp(other);
			std::swap(tmp.np, np);
			return *this;
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
		ListIterator operator +(int i) {
			auto cur = np;
			while (i--)
				cur = cur->next;
			return ListIterator(cur);
		}
		bool operator <(const ListIterator& other) const {
			return *this < *other;
		}
		bool operator ==(const ListIterator& other) const {
			return np == other.np;
		}
		bool operator !=(const ListIterator& other) const {
			return !operator();
		}
		ListIterator operator -(int i) {
			auto cur = np;
			while (i--)
				cur = cur->prev;
			return ListIterator(cur);
		}
		sizeType operator -(const ListIterator& other) {
			sizeType result = 0;
			for (auto node = np; node != other.np; node = node->next, ++result)
				;
			return result;
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
		typedef ListIterator<const T> constIterator;
		typedef const ref constRef;
		typedef T* pointer;
		typedef ReverseIterator<iterator> reverseIterator;
		typedef  ReverseIterator<constIterator> constReverseIterator;
		iterator head;
		iterator tail; //双向环状结构,head,tail不指向实际数据,都是哨兵
	private:
		/**
		 * 辅助函数
		 */
		iterator newNode(constRef val = 0) {
			auto tmp = dataAlloctor::allocate();
			construct(tmp, Node(val));
			return ListIterator(tmp);
		}
		void sort(iterator start, iterator end) {
			if (start == end)
				return;
			iterator cur = start;

			for (cur = start; cur != end; ++cur) {
				if (cur > start)
					cur = start;
			}
			std::swap(*cur, *start);
			sort(++start, end);
		}
		template<typename Compare>
		void sort(iterator start, iterator end, Compare cmp) {
			if (start == end)
				return;
			iterator cur = start;

			for (cur = start; cur != end; ++cur) {
				if (cmp(cur, start) == 1)
					cur = start;
			}
			std::swap(*cur, *start);
			sort(++start, end);
		}
	public:
		/**
		 * 构造函数和析构函数
		 */
		List() {
			head = newNode();
			tail = newNode();
			head.np->next = tail;
			tail.np->prev = head;
		}
		explicit List(sizeType count, const T& value = T()) {
			for (int i = 0; i < count; i++) {
				push_back(value);
			}
		}
		List(const List& other) {
			insert(end(), other.begin(), other.end());
		}
		template<typename InputIterator>
		explicit List(InputIterator first, InputIterator last) {
			for (auto it = first; it != last; ++it) {
				push_back(*first);
			}
		}
		~List() {
			destroy(head.np, tail);
			dataAlloctor::deallocate(head.np, size() + 2);
		}

		/**
		 * 元素的访问
		 */
		valueType front() {
			return *(head + 1);
		}
		valueType back() {
			return *(tail.np - 1);
		}
		/**
		 * 迭代器
		 */
		iterator begin() const {
			return head + 1;
		}
		constIterator cbegin() const {
			return head + 1;
		}
		ReverseIterator<iterator> rbegin() const {
			return ReverseIterator(tail - 1);
		}
		iterator end() const {
			return tail;
		}
		constIterator cend() const {
			return tail;
		}
		constReverseIterator crbegin() const {
			return ReverseIterator(tail - 1);
		}
		reverseIterator rend() const {
			return reverseIterator(head);
		}
		constReverseIterator crend() const {
			return reverseIterator(head);
		}
		/**
		 * 容量
		 */
		bool empty() {
			return head + 1 == tail;
		}
		sizeType size() {
			return tail - head - 1;
		}
		/**
		 * 修饰符
		 */
		void insert(iterator pos, constRef val) {
			auto tmp = newNode(val);
			auto bef = pos.np->prev;
			bef->next = tmp.np;
			tmp.np->prev = bef;
			tmp.np->next = pos.np;
			pos.np->prev = tmp.np;
		}
		template<typename InputIterator>
		void insert(iterator pos, InputIterator first, InputIterator last) {
			for (auto it = first; it != last; ++it)
				insert(pos, *it);
		}

		void push_back(constRef val) {
			insert(end(), val);
		}
		void pop_back() {
			erase(end()-1);
		}
		void erase(iterator pos) {
			auto bef = pos.np->prev;
			auto last = pos.np->next;
			bef->next = last;
			last->prev = bef;
			destroy(pos);
			dataAlloctor::deallocate(pos.np);
		}
		void erase(iterator first, iterator last) {
			auto bef = first.np->prev;
			bef->next = last;
			last->prev = bef;
			destroy(first, last);
			dataAlloctor::deallocate(first, last - first);
		}
		void clear() {
			erase(begin(), end());
		}
		void swap(List& other) {
			std::swap(head, other.head);
			std::swap(tail, other.tail);
		}

		/**
		 * 运算符重载
		 */
		List& operator =(const List& li) {
			if (&li != this)
				swap(List(li));
			return *this;
		}

		friend bool operator ==(const List& lhs, const List& rhs) {
			auto lit = lhs.begin();
			auto rit = rhs.begin();
			for (; lit != lhs.end() && rit != rhs.end() && *lit == *rit;
					++lit, ++rit)
				;
			if (lit != lhs.end() || rit != rhs.end())
				return false;
			return true;
		}
		friend bool operator !=(const List& lhs, const List& rhs) {
			return !(operator ==(lhs, rhs));
		}

		/**
		 * 操作
		 */
		void headToTail(){
			head = tail;
		}
		void splice(iterator pos, List& other) {
			splice(pos, other, other.begin(), other.end());
		}
		void splice(iterator pos, List& other, iterator first, iterator last) {
			this->insert(pos, first, last);
			other.headToTail();
		}
		void merge(List& other) {
			iterator cur1 = begin();
			iterator cur2 = other.begin();
			iterator cur = head;
			while (cur1 != end() && cur2 != other.end()) {
				if (cur1 != begin() && *cur1 > *(cur1 - 1))
					break;
				if (*cur1 < *cur2) {
					cur.nb->next = cur1.nb;
					cur1.nb.prev = cur.nb.prev;
					cur = cur1;
					++cur1;
				} else {
					cur.nb->next = cur2.nb;
					cur2.nb.prev = cur.nb.prev;
					cur = cur2;
					++cur2;
				}
			}
			if (cur2 == other.end())
				return;
			cur.nb->next = cur2.nb;
			cur2.nb.prev = cur.nb.prev;
			tail = other.tail;
		}
		template<typename compare>
		void merge(List& other, compare cmp) {
			iterator cur1 = begin();
			iterator cur2 = other.begin();
			iterator cur = head;
			while (cur1 != end() && cur2 != other.end()) {
				if (cur1 != begin() && *cur1 > *(cur1 - 1))
					break;
				if (cmp(*cur1, *cur2) < 0) {
					cur.nb->next = cur1.nb;
					cur1.nb.prev = cur.nb.prev;
					cur = cur1;
					++cur1;
				} else {
					cur.nb->next = cur2.nb;
					cur2.nb.prev = cur.nb.prev;
					cur = cur2;
					++cur2;
				}
			}
			if (cur2 == other.end())
				return;
			cur.nb->next = cur2.nb;
			cur2.nb.prev = cur.nb.prev;
			tail = other.tail;
		}
		void reverse() {
			auto fst = begin();
			auto snd = fst + 1;
			while (fst != end() && snd != end()) {
				auto tmp = fst.np->prev;
				fst.np->prev = fst.np->next;
				fst.np->next = tmp;
				fst = snd;
				snd = fst + 1;
			}
			auto tmp = head;
			head = tail;
			tail = tmp;
		}
		void sort() {
			sort(begin(), end());
		}
		template<typename Compare>
		void sort(Compare comp) {
			sort(begin(), end(), comp);
		}
		void unique() {
			int num = 0;
			iterator first = begin();
			for (auto it = begin(); it != end();) {
				if (num == 0) {
					first = it;
					++it;
				} else {
					if (*it != *first) {
						erase(first + 1, it);
						num = 0;
					} else {
						++it;
						++num;
					}
				}
			}
		}
		void remove(const T&val) {
			for (auto& it = begin(); it != end();) {
				if (*it == val) {
					auto tmp = it + 1;
					erase(it);
				} else
					++it;
			}
		}
		template<typename UnaryPredicate>
		void removeIf(UnaryPredicate p) {
			for (auto& it = begin(); it != end();) {
				if (p(*it)) {
					auto tmp = it + 1;
					erase(it);
				} else
					++it;
			}
		}
	};
}

#endif /* LIST_H_ */
