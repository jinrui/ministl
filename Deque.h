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
namespace MiniStl {
	template<typename T, int BufSize>
	class DequeIterator: public randomAccessIterator<T> {
	public:
		void setMapNode(mapPointer node) {
			demap = node;
			first = *node;
			last = *node + bufLen;
		}
	public:
		typedef pointer* mapPointer;
		typedef int sizeType;
		typedef DequeIterator self;
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
			if (tmp >= 0 && tmp < bufLen)
				cur += n;
			else {
				auto off = tmp >= 0 ? tmp / bufLen : (tmp + 1) / bufLen - 1;
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
		sizeType bufLen;
	};
	template<typename T, typename Alloc = Alloc, int BufSize = 512>
	class Deque {
	public:
		//默认的空间配置器为二级配置器
		typedef Allocator<T, Alloc> dataAlloctor;
		typedef Allocator<T*, Alloc> mapAlloctor;
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
	public:
		iterator start;
		iterator finish;
		mapPointer demap;
		sizeType mapSize;	//map的长度
		sizeType bufLen;
	private:
		/**
		 * 辅助函数
		 */
		//n是节点个数
		void fillInit(sizeType n, const T&val) {
			createNodes(n);
		}
		template<typename InputIterator>
		void fillInit(sizeType n, InputIterator first, InputIterator last) {
			createNodes(n);
		}
		void createNodes(sizeType n) {

		}
		void allocateBuf(sizeType nodesToAdd) {
			allocateMap(nodesToAdd);
			for (int i = 1; i <= nodesToAdd; i++) {
				auto newBuf = dataAlloctor::allocate(BufSize);
				*(start.demap - i) = newBuf;
			}
		}
		void allocateMap(sizeType nodesToAdd) {
			auto oldNodes = finish.demap - start.demap + 1;
			auto newNodes = oldNodes + nodesToAdd;
			auto newMapSize = mapSize + std::max(mapSize, nodesToAdd) + 2;
			auto newMap = mapAlloctor::allocate(newMapSize);
			auto newMapStart = newMap + (newMapSize - newNodes) / 2
					+ nodesToAdd;
			uninitializedCopy(start.demap, start.demap + oldNodes, newMapStart);
			mapAlloctor::deallocate(demap, mapSize);
			demap = newMap;
			mapSize = newMapSize;
			start.setMapNode(newMapStart);
			start.cur = start.first;
			finish.setMapNode(newMapStart + oldNodes - 1);
			finish.cur = finish.last + 1;
		}
	public:
		/**
		 * 成员函数
		 */
		Deque() :
				start(), finish(), demap(0), mapSize(0), bufLen(
						BufSize / sizeof(T)) {
		}
		Deque(sizeType n, const ref value = T()) :
				bufLen(BufSize / sizeof(T)) {
			fillInit(n, value);
		}
		Deque(const Deque& other) :
				bufLen(BufSize / sizeof(T)) {
			fillInit(other.size(), other.start, other.finish);
		}
		template<typename InputIterator>
		Deque(InputIterator first, InputIterator last) :
				bufLen(BufSize / sizeof(T)) {
			fillInit((last - first), first, last);
		}
		~Deque() {
			destroy(start, finish);
			dataAlloctor::deallocate(start, size());
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
		sizeType size() const{
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
		void insert(iterator pos, sizeType count, const T& val) {
			if (count == 0)
				return;
			auto left = pos - start;
			auto right = finish - pos;
			if (left < right) {
				auto tmp = start;
				if (count > start.cur - *demap)
					allocateBuf((count - (start.cur - *demap)) / bufLen + 1);
				start -= count;
				uninitializedCopy(tmp, pos - 1, start);
				for (auto it = start + pos - tmp; it != pos + 1; ++it)
					*it = val;
			} else {
				auto tmp = finish;
				if (finish.cur + count > *(demap + mapSize - 1) + bufLen)
					allocateBuf(
							(count + finish.cur
									- (*(demap + mapSize - 1) + bufLen))
									/ bufLen = 1);
				finish += count;
				uninitializedCopyBck(pos, tmp, pos + 1);
				for (auto it = pos; it != pos + count; ++it)
					*it = val;
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
				if (count > start.cur - *demap)
					allocateBuf((count - (start.cur - *demap)) / bufLen + 1);
				start -= count;
				uninitializedCopy(tmp, pos - 1, start);
				for (auto tmp1 = start + pos - tmp; first != last;
						++first, ++tmp1)
					*tmp1 = *first;
			} else {
				auto tmp = finish;
				if (finish.cur + count > *(demap + mapSize - 1) + bufLen)
					allocateBuf(
							(count + finish.cur
									- (*(demap + mapSize - 1) + bufLen))
									/ bufLen = 1);
				finish += count;
				uninitializedCopyBck(pos, tmp, pos + count);
				for (auto tmp1 = pos; first != last; ++first, ++tmp1)
					*tmp1 = *first;
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
			} else {
				auto tmp = finish;
				finish -= count;
				uninitializedCopy(last, tmp, finish - right);
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
		void swap(const Deque& other) {
			std::swap(start, other.start);
			std::swap(finish, other.finish);
			std::swap(demap, other.demap);
			std::swap(bufLen, other.bufLen);
			std::swap(mapSize, other.mapSize);
		}
	};
}
#endif /* DEQUE_H_ */
