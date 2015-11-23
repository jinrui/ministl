/*
 * Vector
 *
 *  Created on: 2015年11月6日
 *      Author: jinrui
 */

#ifndef VECTOR_H_
#define VECTOR_H_
#include "Alloc.h"
#include "Allocator.h"
#include "Construct.h"
#include "ReverseIterator.h"
#include <iostream>
#include "Uninitialized.h"
namespace MiniStl {
	template<typename T, typename Alloc = Alloc>
	class Vector {
	public:
		typedef int sizeT;
		typedef int ptrdiffT;
		typedef T* iterator;
		typedef const T* constIterator;
		typedef T valueType;
		typedef T* pointer;
		typedef const T* constPointer;
		typedef T& ref;
		typedef const T& constRef;
		typedef sizeT sizeType;
		typedef ptrdiffT differenceType;
		typedef ReverseIterator<iterator> reverseIterator;
		typedef ReverseIterator<constIterator> constReverseIterator;
		//typedef  const reverseIterator constReverseIterator;
	protected:
		//默认的空间配置器为二级配置器
		typedef Allocator<T, Alloc> dataAllocator;
		/**
		 * 空间使用标志
		 */
		iterator start;
		iterator finish;
		iterator endOfStorage;

	private:
	public:
		//几个常见的构造函数,析构函数
		Vector() :
				start(0), finish(0), endOfStorage(0) {
		}
		explicit Vector(sizeType count, const T& value = T()) {
			start = dataAllocator::allocate(count);
			finish = start + count;
			endOfStorage = finish;
			uninitializedFillN(start, count, value);
		}
		Vector(const Vector & other) {
			this->start = dataAllocator::allocate(other.capacity());
			uninitializedCopy(other.start, other.finish, this->start);
			this->finish = this->start + other.size();
			this->endOfStorage = start + other.capacity();
		}
		Vector(Vector &&other) {
			swap(other);
		}
		template<typename InputIterator>
		Vector(InputIterator first, InputIterator last) {
			auto count = last-first;
			start = dataAllocator::allocate(count);
			finish = start + count;
			endOfStorage = finish;
			uninitializedCopy(first,last,start);
		}
		~Vector() {
			destroy(start, finish);
			dataAllocator::deallocate(start, capacity());
		}
		/**
		 * 元素访问
		 */
		ref at(sizeType pos) const {
			if (pos >= size() || pos < 0) {
				std::cerr << "out of range!" << std::endl;
				exit(1);
			}
			return start[pos];
		}
		ref operator[](sizeType n) {
			return *(start + n);
		}
		ref front() {
			return *begin();
		}
		ref back() {
			return *(end() - 1);
		}
		pointer data() {
			return &front();
		}

		/**
		 * 迭代器
		 */
		iterator begin() const {
			return start;
		}
		constIterator cbegin() const {
			return start;
		}
		iterator end() const {
			return finish;
		}
		constIterator cend() const {
			return finish;
		}
		reverseIterator rbegin() const {
			return reverseIterator(end() - 1);
		}
		constReverseIterator crbegin() const {
			return constReverseIterator(cend() - 1);
		}
		reverseIterator rend() const {
			return reverseIterator(begin() - 1);
		}
		constReverseIterator crend() const {
			return constReverseIterator(cbegin() - 1);
		}

		/**
		 * 容量
		 */
		sizeType size() const {
			return static_cast<sizeType>(finish - start);
		}
		sizeType capacity() const {
			return endOfStorage - start;
		}
//		sizeType maxSize() const {
//
//		}
		void reserve(sizeType size) {

		}
		void shrinkToFit() {

		}
		bool empty() {
			return finish == start;
		}
		/**
		 * 修饰符
		 */
		void clear() {
			destory(start, finish);
			finish = start;
		}

		void push_back(const T& value) {
			insert(end(), value);
		}
		//多种泛化
		void insert(iterator cur, const T& val);
		void insert(iterator first, sizeT n, const T& val) {
			for (int i = 0; i < n; i++)
				insert(first, val);
		}
//		void insert(constIterator cur, const T& val);
//		void insert(constIterator first, sizeT n, const T& val) {
//			for (int i = 0; i < n; i++)
//				insert(first, val);
//		}
		template<typename inputIterator>
		void insert(iterator position, inputIterator first,
				inputIterator last) {
			for (; first < last; ++first)
				insert(position, *first);
		}
//		template<typename inputIterator>
//		void insert(constIterator position, inputIterator first,
//				inputIterator last) {
//			for (; first < last; ++first)
//				insert(position, *first);
//		}

		template<typename ...Args>
		iterator emplace(constIterator pos, Args ... args);

		void pop_back() {
			--finish;
			destroy(finish);
		}
		//清楚某个位置上元素，也不简单,注意调用copy
		iterator erase(iterator position) {
			return erase(position, position + 1);
		}
		iterator erase(iterator first, iterator last) {
			sizeType dis = last - first;
			iterator cur = first + dis;
			for (; cur < finish; ++first, ++cur)
				*first = *cur;
			for (sizeType i = 0; i < dis; i++, --cur)
				destroy(cur);
			finish = finish - dis;
			return last = first;
		}
		iterator erase(constIterator position) {
			return erase(position, position + 1);
		}
		iterator erase(constIterator first, constIterator last) {
			int dis = last - first;
			auto cur = first + dis;
			for (; cur < finish; ++first, ++cur)
				*first = *cur;
			for (int i = 0; i < dis; i++, --cur)
				destroy(&*cur);
			finish = finish - dis;
			return last = first;
		}

		void resize(sizeType newSz, const T& x) {
			if (newSz < size())
				erase(begin() + newSz, end());
			else
				insert(end(), newSz - size(), x);
		}
		void resize(sizeType newSz, T value = T()) {
			resize(newSz, T());
		}
		void swap(Vector& other);

		/**
		 *运算符重载
		 */
		Vector& operator =(const Vector& vec) {
			if (&vec != this)
				swap(Vector(vec));
			return *this;
		}

		template<typename E, typename A>
		friend bool operator ==(const Vector<E, A>& lhs,
				const Vector<E, A>& rhs);

		template<typename E, typename A>
		friend bool operator !=(const Vector<E, A>& lhs,
				const Vector<E, A>& rhs);
	};

	template<typename T, typename Alloc>
	void Vector<T, Alloc>::insert(iterator cur, const T& val) {
		sizeType nSize = size();
		sizeType cap = capacity();
		sizeType dataToCp = finish - cur;
		sizeType pos = cur - start;
		if (nSize < cap) {
			auto tmp = finish;
			for (; tmp > cur; --tmp)
				*tmp = *(tmp - 1);
			*tmp = val;
			finish++;
		} else {
			sizeType sizeToAlloc = 2 * cap > 1 ? 2 * cap : 1;
			auto tmp = dataAllocator::allocate(sizeToAlloc);
			auto _start = uninitializedCopy(start, cur, tmp);
			*(tmp + pos) = val;
			uninitializedCopy(cur, finish, tmp + pos + 1);
			destroy(start, finish);
			dataAllocator::deallocate(start, cap);
			start = _start;
			finish = start + nSize + 1;
			endOfStorage = start + sizeToAlloc;
		}
	}

	template<typename T, typename Alloc>
	void Vector<T, Alloc>::swap(Vector<T, Alloc>& other) {
		Vector<T, Alloc> tmp(other);
		std::swap(this->start, tmp.start);
		std::swap(this->finish, tmp.finish);
		std::swap(this->endOfStorage, tmp.endOfStorage);
	}

	template<typename T, typename Alloc>
	bool operator ==(const Vector<T, Alloc>& lhs, const Vector<T, Alloc>& rhs) {
		if (lhs.begin() == rhs.begin() && lhs.end() == rhs.end()
				&& lhs.capacity() == rhs.capacity())
			return true;
		return false;
	}
	template<typename T, typename Alloc>
	bool operator !=(const Vector<T, Alloc>& lhs, const Vector<T, Alloc>& rhs) {
		return !operator ==(lhs, rhs);
	}
}

#endif /* VECTOR_H_ */
