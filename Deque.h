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
#include "Uninitialized.h"
#include "Iterator.h"
#include <stdlib.h>
#include <iostream>
namespace MiniStl {
	template<typename T, typename Alloc, int BufSize>
	class DequeIterator: public randomAccessIterator<T> {
	public:
		typedef T* pointer;
		typedef T& ref;
		typedef T** mapPointer;
		typedef int sizeType;
		typedef DequeIterator self;
		typedef Allocator<T, Alloc> dataAlloctor;
		typedef typename randomAccessIterator<T>::differenceType differenceType;
	public:
		mapPointer deMap;
		pointer first;
		pointer last;
		pointer cur;
		sizeType bufLen;
		void setMapNode(mapPointer node) {
			deMap = node;
			//if(*node == 0) *node = (int*)malloc(bufLen*sizeof(T));
			if (*node == 0)
				*node = dataAlloctor::allocate(bufLen);
			first = *node;
			last = *node + bufLen;
		}
		DequeIterator() :
				deMap(0), first(0), last(0), cur(0), bufLen(BufSize / sizeof(T)) {
		}
		DequeIterator(mapPointer _deMap, pointer _first, pointer _last,
				pointer _cur) :
				deMap(_deMap), first(_first), last(_last), cur(_cur), bufLen(
						BufSize / sizeof(T)) {
		}
		DequeIterator(const DequeIterator& other) :
				deMap(other.deMap), first(other.first), last(other.last), cur(
						other.cur), bufLen(other.bufLen) {
		}
		template<typename E>
		DequeIterator(const DequeIterator<E, Alloc, BufSize>& other) :
				deMap(const_cast<mapPointer>(other.deMap)), first(
						const_cast<pointer>(other.first)), last(
						const_cast<pointer>(other.last)), cur(
						const_cast<pointer>(other.cur)), bufLen(other.bufLen) {
		}
		ref operator *() const {
			return *cur;
		}
		self& operator ++() {
			++cur;
			if (cur == last) {
				setMapNode(deMap + 1);
				cur = first;
			}
			return *this;
		}
		self& operator --() {
			if (cur == first) {
				setMapNode(deMap - 1);
				cur = last;
			}
			cur--;
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
			if (tmp >= 0 && tmp < bufLen)
				cur += n;
			else {
				auto off = tmp > 0 ? tmp / bufLen : ((tmp + 1) / bufLen - 1);
				setMapNode(deMap + off);
				cur = first + (tmp - off * bufLen);
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
		sizeType operator -(const self& other) const {
			sizeType result = 0;
			if (deMap < other.deMap) {
				result += bufLen * (other.deMap - this->deMap - 1);
				result += this->last - this->cur;
				result += other.cur - other.first;
				result = -result;
			} else if (deMap == other.deMap) {
				return this->cur - other.cur;
			} else {
				result += bufLen * (this->deMap - other.deMap - 1);
				result += this->cur - this->first;
				result += other.last - other.cur;
			}
			return result;
		}
		ref operator [](differenceType n) {
			return *(*this + n);
		}
		bool operator ==(const self& other) const {
			return this->cur == other.cur;
		}
		bool operator !=(const self& other) const {
			return !operator==(other);
		}
	};
	template<typename T, typename Alloc = Alloc, int BufSize = 512>
	class Deque {
	public:
		//默认的空间配置器为二级配置器
		typedef Allocator<T, Alloc> dataAlloctor;
		typedef Allocator<T*, Alloc> mapAlloctor;
		typedef int sizeT;
		typedef int ptrdiffT;
		typedef DequeIterator<T, Alloc, BufSize> iterator;
		typedef DequeIterator<const T, Alloc, BufSize> constIterator;
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
	public:
		iterator start;
		iterator finish;
		mapPointer deMap;
		sizeType mapSize;	//map的长度
		sizeType bufLen;
	private:
		/**
		 * 辅助函数
		 */
		//n是节点个数
		void fillInit(sizeType n, const T&val) {
			createNodes(n);
			uninitializedFill(start, finish, val);
		}
		template<typename InputIterator>
		void fillInit(sizeType count, InputIterator first, InputIterator last) {
			createNodes(count);
			uninitializedFillNI(start, first, last);
		}
		/**
		 * 可能有bug
		 */
		void createNodes(sizeType n) {
			//auto numNodes = n % bufLen == 0 ? n / bufLen : (n / bufLen + 1);
			auto numNodes = n / bufLen + 1;
			mapSize = std::max(numNodes + 2, 8);
			deMap = mapAlloctor::allocate(mapSize);
			auto nstart = deMap + (mapSize - numNodes) / 2;
			auto nfinish = nstart + numNodes - 1;
			for (auto it = deMap; it < deMap + mapSize; ++it) {
				*it = dataAlloctor::allocate(bufLen);
				//*it = (int*)malloc(bufLen*sizeof(T));	//TODO 自己写的内存管理有bug
			}
			start.setMapNode(nstart);
			start.cur = start.first;
			finish.setMapNode(nfinish);
			//finish.cur = finish.first + n % (bufLen + 1);
			finish.cur = finish.first + n % bufLen;
		}
		void allocateMap(sizeType n, bool isFront) {
			sizeType nodesToAdd = n / bufLen + 1;
			if (mapSize == 0) {
				auto newMapSize = 8;
				auto newMap = mapAlloctor::allocate(newMapSize);
				auto newMapStart = newMap + (newMapSize - nodesToAdd) / 2
						+ (isFront ? nodesToAdd : 0);
				deMap = newMap;
				mapSize = newMapSize;
				for (auto it = deMap; it < deMap + mapSize; ++it) {
					*it = dataAlloctor::allocate(bufLen);
					//*it = (int*)malloc(bufLen*sizeof(T));	//TODO 自己写的内存管理有bug
				}
				start.setMapNode(newMapStart);
				start.cur = start.first;
				finish.setMapNode(newMapStart);
				finish.cur = finish.first;
				return;
			}
			auto oldNodes = finish.deMap - start.deMap + 1;
			auto newNodes = oldNodes + nodesToAdd;
			auto newMapSize = mapSize + std::max(mapSize, nodesToAdd) + 2;
			auto newMap = mapAlloctor::allocate(newMapSize);
			auto newMapStart = newMap + (newMapSize - newNodes) / 2
					+ (isFront ? nodesToAdd : 0);
			uninitializedCopy(start.deMap, start.deMap + oldNodes, newMapStart);
			for (auto it = newMapStart + oldNodes; it != newMapStart + newNodes;
					++it)
				*it = dataAlloctor::allocate(bufLen);
			//*it = (int*)malloc(bufLen*sizeof(T));
			mapAlloctor::deallocate(deMap, mapSize);
			deMap = newMap;
			mapSize = newMapSize;
			start.setMapNode(newMapStart);
			finish.setMapNode(newMapStart + oldNodes - 1);
		}
	public:
		/**
		 * 成员函数
		 */
		Deque() :
				start(), finish(), deMap(0), mapSize(0), bufLen(
						BufSize / sizeof(T)) {
		}
		Deque(sizeType n, const T& value = T()) :
				Deque() {
			fillInit(n, value);
		}
		Deque(const Deque& other) :
				Deque() {
			fillInit(other.finish - other.start, other.start, other.finish);
		}
		template<typename InputIterator>
		Deque(InputIterator first, InputIterator last) :
				Deque() {
			fillInit(first, last);
		}
		~Deque() {
			destroy(start, finish);
			if (deMap && *deMap) {
				for (auto it = start.deMap; it <= finish.deMap; ++it)
					dataAlloctor::deallocate(*it, bufLen);
			}
			mapAlloctor::deallocate(deMap, mapSize);
		}
		Deque& operator =(const Deque& other) {
			if (&other != this)
				swap(Deque(other));
			return *this;
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
			return reverseIterator(end() - 1);
		}
		reverseIterator rend() const {
			return reverseIterator(begin() - 1);
		}
		constReverseIterator crbegin() const {
			return constReverseIterator(cend() - 1);
		}
		constReverseIterator crend() const {
			return constReverseIterator(cbegin() - 1);
		}
		/**
		 * 容量
		 */
		bool empty() const {
			return start == finish;
		}
		sizeType size() const {
			return finish - start;
		}

		/**
		 * 修饰符
		 */
		void clear() {
			//保留一个缓冲区
			destroy(start, finish);
			//dataAlloctor::deallocate(start, size());
		}
		void insert(iterator pos, const T& val) {
			insert(pos, 1, val);
		}
		//这个函数对于start和finish处理确实有问题
		void insert(iterator pos, sizeType count, const T& val) {
			if (count == 0)
				return;
			auto left = pos - start;
			auto right = finish - pos;
			if (left < right) {
				auto tmp = start;
				auto leftLeft = (start.deMap - deMap) * bufLen
						+ (start.cur - start.first);
				if (count > leftLeft)
					allocateMap(count - leftLeft, true);
				start -= count;
				if (pos != tmp)
					uninitializedCopy(tmp, pos - 1, start);
				uninitializedFillN(start + (pos - tmp), count, val);
			} else {
				auto tmp = finish;
				auto rightLeft =
						deMap == 0 ?
								0 :
								((deMap + mapSize - 1 - finish.deMap) * bufLen
										+ (finish.last - finish.cur));
				if (count > rightLeft)
					allocateMap(count - rightLeft, false);
				if (!pos.cur)
					pos = finish;
				finish += count;
				if (tmp.deMap)
					uninitializedCopyBck(pos, tmp, pos + count);
				uninitializedFill(pos, pos + count, val);
			}
		}
		template<typename InputIterator>
		void insert(iterator pos, InputIterator first, InputIterator last) {
			if (first == last)
				return;
			auto left = pos - start;
			auto right = finish - pos;
			auto count = last - first;
			if (left < right) {
				auto tmp = start;
				auto leftLeft = (start.deMap - deMap) * bufLen
						+ (start.cur - start.first);
				if (count > leftLeft)
					allocateMap(count - leftLeft, true);
				start -= count;
				uninitializedCopy(tmp, pos - 1, start);
				uninitializedFillNI(start + (pos - tmp), first, last);
			} else {
				auto tmp = finish;
				auto rightLeft =
						deMap == 0 ?
								0 :
								((deMap + mapSize - 1 - finish.deMap) * bufLen
										+ (finish.last - finish.cur));
				if (count > rightLeft)
					allocateMap(count - rightLeft, false);
				if (!pos.cur)
					pos = finish;
				finish += count;
				if (tmp.deMap)
					uninitializedCopyBck(pos, tmp, pos + count);
				uninitializedFillNI(pos, first, last);
			}
		}
		void erase(iterator pos) {
			erase(pos, pos + 1);
		}
		void erase(iterator first, iterator last) {
			auto left = first - start;
			auto right = finish - last;
			auto count = last - first;
			if (left < right) {
				auto tmp = start;
				start += count;
				uninitializedCopyBck(tmp, first, start);
				destroy(tmp,start);
			} else {
				auto tmp = finish;
				finish -= count;
				uninitializedCopy(last, tmp, finish - right);
				destroy(finish,tmp);
			}
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
		void reSize(sizeType n) {
			if (n < size()) {
				erase(finish - (n - size()), finish);
			} else {
				insert(finish, n - size(), T());
			}
		}
		void swap(Deque& other) {
			std::swap(start, other.start);
			std::swap(finish, other.finish);
			std::swap(deMap, other.deMap);
			std::swap(bufLen, other.bufLen);
			std::swap(mapSize, other.mapSize);
		}
	};
}
#endif /* DEQUE_H_ */
