/*
 * Deque.h
 *
 *  Created on: 2015年11月11日
 *      Author: jinrui
 */

#ifndef DEQUE_H_
#define DEQUE_H_
#include "Construct.h"
#include "ReverseIterator.h"
#include "Allocator.h"
#include "Alloc.h"
namespace MiniStl {
	template<typename T, int BufSize>
	class DequeIterator: public randomAccessIterator<T> {
	private:
		void setMapNode(mapPointer node) {
			demap = node;
			first = *mapPointer;
			last = *mapPointer + mapSize;
		}
	public:
		typedef pointer* mapPointer;
		typedef int sizeType;
		typedef DequeIterator self;
		DequeIterator() :
				deMap(0), first(0), last(0), cur(0), mapSize(BufSize) {
		}
		DequeIterator(mapPointer _deMap, pointer _first, pointer _last,
				pointer _cur) :
				deMap(_deMap), first(_first), last(_last), cur(_cur), mapSize(
						BufSize) {
		}
		DequeIterator(const DequeIterator& other) :
				deMap(other.deMap), first(other.first), last(other.last), cur(
						other.cur), mapSize(other.mapSize) {
		}
		ref operator *() const {
			return *cur;
		}
		self& operator ++() {
			++cur;
			if (cur == last)
				setMapNode(demap + 1);
			return *this;
		}
		self& operator --() {
			if (cur == first) {
				setMapNode(demap - 1);
				cur = last;
			}
			--cur;
			return *this;
		}
		self operator ++(int) {
			auto tmp = *this;
			++*this;
			return tmp;
		}
		self operator --(int) {
			auto tmp = *this;
			--*this;
			return tmp;
		}
		pointer operator->() const {
			return &(operator*());
		}
		self& operator +=(differenceType n) {
			auto tmp = cur - first + n;
			if (tmp >= 0 && tmp < mapSize)
				cur += n;
			else {
				auto off = tmp >= 0 ? tmp / mapSize : (tmp + 1) / mapSize - 1;
				setMapNode(deMap + off);
				cur = first + (tmp - off * mapSize);
			}
			return *this;
		}
		self& operator -=(differenceType n) {
			return operator +=(-n);
		}
		self operator +(differenceType n) {
			auto tmp = *this;
			return tmp += n;
		}
		self operator -(differenceType n) {
			auto tmp = *this;
			return tmp -= n;
		}
		ref operator [](differenceType n) {
			return *(*this + n);
		}
		bool operator ==(const self other) {
			return this->cur == other.cur;
		}
		bool operator !=(const self other) {
			return !operator==(other);
		}
	public:
		mapPointer deMap;
		pointer first;
		pointer last;
		pointer cur;
		sizeType mapSize;
	};
	template<typename T, typename Alloc = Alloc, int BufSize = 512>
	class Deque {
	public:
		//默认的空间配置器为二级配置器
		typedef Allocator<T, Alloc> dataAlloctor;

		typedef int sizeT;
		typedef int ptrdiffT;
		typedef DequeIterator<T, BufSize> iterator;
		typedef DequeIterator<const T, BufSize> constIterator;
		typedef T valueType;
		typedef T* pointer;
		typedef pointer* mapPointer;
		typedef const T* constPointer;
		typedef T& ref;
		typedef const T& constRef;
		typedef sizeT sizeType;
		typedef ptrdiffT differenceType;
		typedef ReverseIterator<iterator> reverseIterator;
		typedef ReverseIterator<constIterator> constReverseIterator;
	protected:
		iterator start;
		iterator finish;
		mapPointer demap;
		sizeType mapSize;

	public:
		/**
		 * 成员函数
		 */
		Deque() :
				start(), finish(), demap(0), mapSize(BufSize) {
		}
		Deque(const Deque& other) {

		}
		~Deque() {
			destroy(start, finish);
			dataAlloctor::deallocate(start, size());
		}
		Deque& operator =(const Deque& other) {

		}
		/**
		 * 元素的访问
		 */
		ref at(sizeType n) {
			if (n < 0 || n > size()) {
				std::cerr << "out of range!" << std::endl;
				exit(1);
			}
			return start[n];
		}
		ref operator [](sizeType n) {
			return start[n];
		}
		valueType front() {
			return *start;
		}
		valueType back() {
			auto tmp = finish;
			return *(--tmp);
		}
		/**
		 * 迭代器
		 */
		iterator begin() const {
			return start;
		}
		iterator end() const {
			return finish;
		}
		constIterator cbegin() const {
			return start;
		}
		constIterator cend() const {
			return finish;
		}
		reverseIterator rbegin() const {
			return reverseIterator(start);
		}
		constReverseIterator rend() const {
			return reverseIterator(finish);
		}
		constReverseIterator crbegin() const {
			return reverseIterator(start);
		}
		reverseIterator crend() const {
			return reverseIterator(finish);
		}
		/**
		 * 容量
		 */
		bool empty() const {
			return start == finish;
		}
		sizeType size() {
			return finish - start;
		}

		/**
		 * 修饰符
		 */
		void clear() {
			destroy(start, finish);
			//dataAlloctor::deallocate(start, size());
		}
		void insert(iterator pos, const T& val) {

		}
		void insert(iterator pos, sizeType count, const T& val) {

		}
		template<typename InputIterator>
		void insert(iterator pos, InputIterator first, InputIterator last) {

		}
		void erase(iterator pos) {

		}
		void erase(iterator first, iterator last) {

		}
		void push_back(constRef val) {
			insert(end(), val);
		}
		void pop_back() {
			erase(end() - 1);
		}
		void push_front(constRef val) {
			insert(begin(), val);
		}
		void pop_front() {
			erase(begin());
		}
		void reSize() {

		}
		void swap(const Deque& other) {

		}
	};
}
#endif /* DEQUE_H_ */
