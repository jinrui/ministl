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
		ListIterator operator -(int i) {
			auto cur = np;
			while (i--)
				cur = cur->prev;
			return ListIterator(cur);
		}
		sizeType operator -(const ListIterator& other){
			sizeType result = 0;
			for(auto node = np;node != other.np;node = node->next,++result);
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
		typedef const iterator constIterator;
		typedef const ref constRef;
		typedef T* pointer;
		typedef ReverseIterator<iterator> reverseIterator;
		typedef const reverseIterator constReverseIterator;
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
			auto tmp = tail - 1;
			auto tmp2 = tmp - 1;
			destroy(tmp, tail);
			dataAlloctor::deallocate(tmp.np);
			tmp2.np->next = tail;
			tail.np->prev = tmp2;
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
			swap(List(li));
			return *this;
		}

		friend bool operator ==(const List& lhs, const List& rhs) const;
		friend bool operator !=(const List& lhs, const List& rhs) const;

		/**
		 * 操作
		 */
		void merge(List& other){

		}
		template<typename compare>
		void merge(List& other,compare cmp){

		}
		void reverse(){

		}
		void sort(){

		}
		void unique(){

		}
		void remove(const T&val){

		}
		template<typename UnaryPredicate>
		void removeIf(UnaryPredicate p){

		}
	};

	template<typename T, typename Alloctor>
	bool operator ==(const List<T, Alloctor>& lhs,
			const List<T, Alloctor>& rhs) const {
		auto lit = lhs.begin();
		auto rit = rhs.begin();
		for (; lit != lhs.end() && rit != rhs.end() && *lit == *rit;
				++lit, ++rit)
			;
		if (lit != lhs.end() || rit != rhs.end())
			return false;
		return true;
	}
	template<typename T, typename Alloctor>
	bool operator !=(const List& lhs, const List& rhs) const {
		return !(operator ==(lhs, rhs));
	}
}

#endif /* LIST_H_ */
