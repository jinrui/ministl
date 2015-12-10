/*
 * HashMap.h
 *
 *  Created on: 2015年12月7日
 *      Author: apple
 */

#ifndef ASSO_HASHMAP_H_
#define ASSO_HASHMAP_H_
#include "Pair.h"
#include "../Iterator.h"
#include "../Alloc.h"
#include "../Allocator.h"
#include "../Construct.h"
namespace MiniStl {
	template<typename pair>
	struct Node {
		pair data;
		Node* next;
		Node* prev;
		Node() :
				data(), next(0), prev(0) {
		}
		bool operator ==(const Node& other) {
			return data == other.data && next == other.next && other.prev = prev;
		}
		bool operator !=(const Node& other) {
			return !operator ==(other);
		}
	};
	template<typename pair>
	class MapIterator: public forwardIterator<pair> {
	public:
		typedef Node<pair> valueType;
		typedef valueType* pointer;
		typedef valuType& ref;
		typedef MapIterator self;
		typedef typename forwardIterator<pair>::differenceType differenceType;
		pointer nodePointer;
		pointer* bucket;
		MapIterator() :
				nodePointer(0), bucket(0) {
		}
		explicit MapIterator(pointer np, pointer* bu) :
				nodePointer(np), bu(bucket) {
		}
		MapIterator(const self& other) :
				nodePointer(other.nodePointer), bucket(other.bucket) {
		}
		template<typename E>
		MapIterator(const MapIterator<E>& other) :
				nodePointer(reinterpret_cast<pointer>(other.nodePointer)), bucket(
						reinterpret_cast<pointer*>(other.bucket)) {
		}
		valueType operator *() {
			return nodePointer->data;
		}
		self& operator ++() {
			if (nodePointer->next)
				nodePointer = nodePointer->next;
			else {
				++bucket;
				this->nodePointer = *bucket;
			}
			return *this;
		}
		self operator ++(int) {
			auto tmp = *this;
			++tmp;
			return tmp;
		}
	};
	template<typename K, typename V, typename Hash = std::hash<K>,
			typename alloc = Alloc>
	class HashMap {
		typedef Pair<const K, V> pair;
		typedef Allocator<Node, alloc> dataAllocator;

		typedef HashMap self;
		typedef MapIterator<pair> iterator;
		typedef MapIterator<const pair> constIterator;
		typedef typename iterator::valueType valueType;
		typedef valueType& ref;
		typedef valueType* pointer;
		typedef int sizeType;
		typedef float loadType;
		typedef const valueType& constRef;
		typedef Allocator<pointer, alloc> mapAllocator;
		Hash hash;
		iterator start;
		iterator finish;
		sizeType bucketSize;
		pointer* bucket;
		loadType loadCap;
		sizeType dataSize = 0;
		const sizeType INILCAP = 1 << 4;
		/**
		 * Member functions
		 */
		HashMap() :
				bucketSize(INILCAP), loadCap(0.75) {
			bucket = dataAllocator::allocate(INILCAP + 1);
			start = iterator(0, bucket);
			finish = iterator(0, bucket + bucketSize);
		}
		HashMap(sizeType bucketCount, const Hash& _hash = Hash(),
				loadType _loadCap = 0.75) :
				hash(_hash), bucketSize(bucketCount), loadCap(_loadCap) {
			bucket = dataAllocator::allocate(bucketCount + 1);
			start = iterator(0, bucket);
			finish = iterator(0, bucket + bucketCount);
		}
		HashMap(const HashMap& other) :
				hash(other.hash), start(other.start), finish(other.finish), bucketSize(
						bucketSize), bucket(other.bucket), loadCap(
						other.loadCap) {
		}
		~HashMap() {
			clear();
		}
		/**
		 *iterators
		 */
		iterator begin() {
			return start;
		}
		iterator end() {
			return finish;
		}
		constIterator cbegin() const {
			return start;
		}
		constIterator cend() const {
			return finish;
		}
		/**
		 * capacity
		 */
		bool empty() {
			return dataSize == 0;
		}
		sizeType size() {
			return dataSize;
		}
		/**
		 * modifiers
		 */
		void clear() {
			destroy(start, finish);
			for (int i = 0; i < bucketSize; ++i) {
				auto p = bucket[i];
				dataAllocator::deallocate(p, 0);
			}
			mapAllocator::deallocate(bucket, bucketSize);
		}
		bool insert(const pair p) {
			auto k = hash(p.first);
			auto index = k % bucketSize;
			auto it = *(bucket + index);
			while (it) {
				if (it->data->first == p.first)
					return false;
				it = it->next;
			}
			auto newNode = dataAllocator::allocate();
			construct(newNode, p);
			newNode->next = *(bucket + index);
			bucket[index]->prev = newNode;
			bucket[index] = newNode;
			++dataSize;
			if (dataSize >= bucketSize * loadCap)
				reHash(bucketSize * 2 + 1);
			return true;
		}
		bool insert(iterator first, iterator last) {
			for (; first != last; ++first) {
				if (!insert(*first))
					return false;
			}
			return true;
		}
		bool erase(const K& key) {
			auto it = find(key);
			if (it == finish)
				return false;
			auto bf = it->prev;
			auto af = it->next;
			bf->next = af;
			if (af)
				af->prev = bf;
			destroy(&*it);
			dataAllocator::deallocate(&*it);
			--dataSize;
			return true;
		}
		void swap(const self& other) {
			std::swap(other.bucket, bucket);
			std::swap(other.bucketSize, bucketSize);
			std::swap(other.dataSize, dataSize);
			std::swap(other.start, start);
			std::swap(other.finish, finish);
			std::swap(other.hash, hash);
			std::swap(other.loadCap, loadCap);
		}
		/**
		 * lookup
		 */
		V& at(const K& key) {
			auto k = hash(key);
			auto index = k % bucketSize;
			auto it = *(bucket + index);
			while (it) {
				if (it->data->first == key)
					return it->data->second;
				it = it->next;
			}
			std::cerr << "key unfind!" << std::endl;
			exit(1);
		}
		V& operator [](const K& key) {
			auto k = hash(key);
			auto index = k % bucketSize;
			auto it = *(bucket + index);
			while (it) {
				if (it->data->first == key)
					return it->data->second;
				it = it->next;
			}
			auto newNode = dataAllocator::allocate();
			construct(newNode, pair(key, 0));
			newNode->next = *(bucket + index);
			*(bucket + index) = newNode;
			return newNode->data->second;
		}
		sizeType count(const K& key) {
			return find(key) == finish ? 0 : 1;
		}
		iterator find(const K& key) {
			auto k = hash(key);
			auto index = k % bucketSize;
			auto it = *(bucket + index);
			while (it) {
				if (it->data->first == key)
					return iterator(it);
				it = it->next;
			}
			return finish;
		}
		constIterator find(const K& key) const {
			auto k = hash(key);
			auto index = k % bucketSize;
			auto it = *(bucket + index);
			while (it) {
				if (it->data->first == key)
					return iterator(it);
				it = it->next;
			}
			return finish;
		}
		/**
		 * hash policy
		 */
		void reHash(sizeType count) {
			auto newBucket = mapAllocator::allocate(count);
			auto start = begin();
			auto en = end();
			auto tmp = bucket;
			auto oldSize = bucketSize;
			bucketSize = count;
			bucket = newBucket;
			insert(begin(), end());
			mapAllocator::deallocate(tmp, oldSize);
		}
		/**
		 * 操作符重载
		 */
		bool operator ==(const self& other) {
			return start == other.start && finish == other.finish;
		}
		bool operator !=(const self& other) {
			return !operator ==(other);
		}
		void operator =(const self& other) {
			swap(self(other));
		}
	};
}

#endif /* ASSO_HASHMAP_H_ */
