/*
 * vector
 *
 *  Created on: 2015年11月6日
 *      Author: jinrui
 */

#ifndef VECTOR_H_
#define VECTOR_H_
#include "Alloc.h"
#include "Allocator.h"
#include "uninitialized.h"
#include "Construct.h"
#include <iostream>
namespace MiniStl {
	template<typename T, typename Alloc = alloc>
	class vector {
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
		//	typedef reverseIterator<iterator> reverseIterator;

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
		vector() :
				start(0), finish(0), endOfStorage(0) {
		}
		explicit vector(sizeType count, const T& value = T()) {
			start = dataAllocator::allocate(count);
			finish = start + count;
			endOfStorage = finish;
			uninitializedFillN(start, count, value);
		}
		vector(const vector & other){
			this->start = dataAllocator::allocate(other.capacity());
			uninitializedCopy(other.start,other.finish,this->start);
			this->finish = this->start+other.finish-other.start;
			this->endOfStorage = start + other.endOfStorage-other.start;
		}
		vector(vector &&other){
			swap(other);
		}
		~vector() {
			destroy(start,finish);
			dataAllocator::deallocate(start, capacity());
		}
		/**
		 * 元素访问
		 */
		ref at(sizeType) const;
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
		iterator begin() {
			return start;
		}
		constIterator cbegin() const {
			return start;
		}
		iterator end() {
			return finish;
		}
		constIterator cend() const {
			return finish;
		}
		//TODO
//		iterator rbegin() {
//		}
//		constIterator crbegin() const {
//		}
//		iterator rend() {
//		}
//		constIterator crend() const {
//		}

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
		void insert(iterator cur, const T& val) {
			insert(static_cast<constIterator>(cur), val);
		}
		void insert(iterator first, sizeT n, const T& val) {
			for (int i = 0; i < n; i++)
				insert(first, val);
		}
		void insert(constIterator cur, const T& val);
		void insert(constIterator first, sizeT n, const T& val) {
			for (int i = 0; i < n; i++)
				insert(first, val);
		}
		template<typename inputIterator>
		void insert(iterator position, inputIterator first,
				inputIterator last) {
			for (; first < last; ++first)
				insert(position, *first);
		}
		template<typename inputIterator>
		void insert(constIterator position, inputIterator first,
				inputIterator last) {
			for (; first < last; ++first)
				insert(position, *first);
		}

		template<typename ...Args>
		iterator emplace(constIterator pos, Args ... args);

		void pop_back() {
			--finish;
			destory(finish);
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
				destory(&*cur);
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
				destory(&*cur);
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
		void swap(vector& other);

		/**
		 *运算符重载
		 */
		vector& operator =(const vector&);

		//	template<typename T, typename Alloc = alloc>
		friend bool operator ==(vector& lhs, vector& rhs);

		//template<typename T, typename Alloc = alloc>
		friend bool operator ==(const vector& lhs,
				const vector& rhs);
	};

	template<typename T, typename Alloc>
	void vector<T,Alloc>::insert(vector<T,Alloc>::constIterator cur, const T& val) {
		sizeType  nSize = size();
		sizeType cap = capacity();
		sizeType dataToCp = finish - cur;
		if(nSize < cap){
			auto tmp = finish;
			for(;tmp>cur;--tmp)
				*tmp = *(tmp-1);
			*tmp = val;
			finish++;
		}else{
			sizeType sizeToAlloc = 2*cap > 1?2*cap:1;
			auto tmp = dataAllocator::allocate(sizeToAlloc);
			auto _start = uninitializedCopy(start, cur, tmp);
			*(tmp+cur-start) = val;
			uninitializedCopy(cur, finish, tmp+cur-start+1);
			destroy(start, finish);
			dataAllocator::deallocate(start,  finish);
			start = _start;
			finish = start+nSize+1;
			endOfStorage = start + sizeToAlloc;
		}
	}

	template<typename T, typename Alloc>
		void vector<T,Alloc>::swap(vector<T,Alloc>& other) {
			std::swap(this->start,other.start);
			std::swap(this->finish,other.finish);
			std::swap(this->endOfStorage,other.endOfStorage);
		}

	template<typename T, typename Alloc>
	vector<T,Alloc>& vector<T,Alloc>::operator =(const vector<T,Alloc>& v) {
		vector tmp(v);
		swap(tmp);
		return *this;
	}

	template<typename T, typename Alloc>
	bool operator ==(vector<T,Alloc>& lhs, vector<T,Alloc>& rhs) {
		return true;
	}
	template<typename T, typename Alloc>
	bool operator ==(const vector<T>& lhs, const vector<T>& rhs) {
		return true;
	}
}

#endif /* VECTOR_H_ */
