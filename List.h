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
		template<typename E>
		Node(const E& val) :
				data(val), next(0), prev(0) {
		}
		~Node() {

		}
		bool operator ==(const Node& other) {
			return this->data == other.data && this->next == other->next
					&& this->prev == other->prev;
		}
	};

	template<typename T>
	class ListIterator: public biDirectionalIterator<T> {
	public:
		typedef Node<T>* nodePtr;
		typedef int sizeT;
		typedef int ptrdiffT;
		typedef sizeT sizeType;
		typedef ListIterator self;
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
		template<typename E>
		ListIterator(const ListIterator<E>& other) :
				np(reinterpret_cast<nodePtr>(other.np)) {
		}
		ListIterator& operator =(const ListIterator& other) {
			ListIterator tmp(other);
			std::swap(tmp.np, np);
			return *this;
		}
		self& operator ++() {
			np = np->next;
			return *this;
		}
		self operator ++(int) {
			auto tmp = this;
			np = np->next;
			return *tmp;
		}
		self& operator --() {
			np = np->prev;
			return *this;
		}
		self operator --(int) {
			auto tmp = this;
			np = np->prev;
			return *tmp;
		}
		T& operator *() {
			return np->data;
		}
		T* operator ->() {
			return &(np->data);
		}
		self operator +(int i) const {
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
			return !operator==(other);
		}
		ListIterator operator -(int i) const {
			auto cur = np;
			while (i--)
				cur = cur->prev;
			return ListIterator(cur);
		}
		sizeType operator -(const ListIterator& other) {
			sizeType result = 0;
			for (auto node = np; node != other.np; node = node->prev, ++result)
				;
			return result;
		}
	};
	template<typename T, typename Alloctor = Alloc>
	class List {
	public:
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
		typedef ReverseIterator<constIterator> constReverseIterator;
		iterator head;
		iterator tail; //双向环状结构,head,tail不指向实际数据,都是哨兵
	private:
		/**
		 * 辅助函数
		 */
		iterator newNode(const T& val = 0) {
			auto tmp = dataAlloctor::allocate();
			construct(tmp, val);
			return iterator(tmp);
		}
		void sort(iterator start, iterator end) {
			if (start == end)
				return;
			auto tmp = *start;
			auto pos = start;
			for (auto cur = start; cur != end; ++cur) {
				if (*cur < tmp) {
					pos = cur;
					tmp = *cur;
				}
			}
			std::swap(*pos, *start);
			sort(++start, end);
		}
		template<typename Compare>
		void sort(iterator start, iterator end, Compare cmp) {
			if (start == end)
				return;
			auto tmp = *start;
			auto pos = start;
			for (auto cur = start; cur != end; ++cur) {
				if (cmp(*cur, tmp) < 0) {
					pos = cur;
					tmp = *cur;
				}
			}
			std::swap(*pos, *start);
			sort(++start, end);
		}
	public:
		/**
		 * 构造函数和析构函数
		 */
		List() {
			head = newNode();
			tail = newNode();
			head.np->next = tail.np;
			tail.np->prev = head.np;
		}
		explicit List(sizeType count, const T& value = T()) :
				List() {
			for (int i = 0; i < count; i++) {
				push_back(value);
			}
		}
		List(const List& other) :
				List() {
			insert(end(), other.begin(), other.end());
		}
		template<typename InputIterator>
		explicit List(InputIterator first, InputIterator last) :
				List() {
			for (auto it = first; it != last; ++it) {
				push_back(*first);
			}
		}
		~List() {
			destroy(head, tail);
			dataAlloctor::deallocate(head.np, tail.np->next);
		}

		/**
		 * 元素的访问
		 */
		valueType front() {
			return *(head + 1);
		}
		valueType back() {
			return *(tail - 1);
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
		reverseIterator rbegin() const {
			return reverseIterator(end() - 1);
		}
		iterator end() const {
			return tail;
		}
		constIterator cend() const {
			return tail;
		}
		constReverseIterator crbegin() const {
			return constReverseIterator(cend() - 1);
		}
		reverseIterator rend() const {
			return reverseIterator(head);
		}
		constReverseIterator crend() const {
			return constReverseIterator(cbegin());
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
		void insert(iterator pos, const T& val) {
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

		void push_back(const T& val) {
			insert(end(), val);
		}
		void pop_back() {
			erase(end() - 1);
		}
		void erase(iterator pos) {
			auto bef = pos.np->prev;
			auto last = pos.np->next;
			bef->next = last;
			last->prev = bef;
			destroy(pos,pos+1);
			dataAlloctor::deallocate(pos.np);
		}
		void erase(iterator first, iterator last) {
			auto bef = first.np->prev;
			bef->next = last.np;
			last.np->prev = bef;
			destroy(first, last);
			dataAlloctor::deallocate(first.np, last.np);
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
		ref operator [](sizeType n) {
			return *(begin() + n);
		}

		/**
		 * 操作
		 */
		void headToTail() {
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
//				if (cur1 != begin() && *cur1 > *(cur1 - 1))
//					break;
				if (*cur1 < *cur2) {
					cur.np->next = cur1.np;
					cur1.np->prev = cur.np;
					cur = cur1;
					++cur1;
				} else {
					cur.np->next = cur2.np;
					cur2.np->prev = cur.np;
					cur = cur2;
					++cur2;
				}
			}
			if (cur2 == other.end())
				return;
			cur.np->next = cur2.np;
			cur2.np->prev = cur.np->prev;
			tail = other.tail;
		}
		template<typename compare>
		void merge(List& other, compare cmp) {
			iterator cur1 = begin();
			iterator cur2 = other.begin();
			iterator cur = head;
			while (cur1 != end() && cur2 != other.end()) {
//				if (cur1 != begin() && *cur1 > *(cur1 - 1))
//					break;
				if (cmp(*cur1, *cur2) < 0) {
					cur.np->next = cur1.np;
					cur1.np->prev = cur.np;
					cur = cur1;
					++cur1;
				} else {
					cur.np->next = cur2.np;
					cur2.np->prev = cur.np;
					cur = cur2;
					++cur2;
				}
			}
			if (cur2 == other.end())
				return;
			cur.np->next = cur2.np;
			cur2.np->prev = cur.np->prev;
			tail = other.tail;
		}
		void reverse() {
			auto fst = head;
			auto snd = fst + 1;
			while (true) {
				auto tmp = fst.np->prev;
				fst.np->prev = fst.np->next;
				fst.np->next = tmp;
				if(fst == tail) break;
				fst = snd;
				++snd;
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
					++num;
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
			for (auto it = begin(); it != end();) {
				if (*it == val) {
					auto tmp = it + 1;
					erase(it);
					it = tmp;
				} else
					++it;
			}
		}
		template<typename UnaryPredicate>
		void removeIf(UnaryPredicate p) {
			for (auto it = begin(); it != end();) {
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
