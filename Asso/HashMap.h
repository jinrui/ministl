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
		Node() :
				data(), next(0) {
		}
		bool operator ==(const Node& other) {
			return data == other.data && next == other.next;
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
				nodePointer(const_cast<pointer>(other.nodePointer)), bucket(
						other.bucket) {
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
		/**
		 * Member functions
		 */
		HashMap() :
				bucketSize(0), bucket(0), loadCap(0.75) {

		}
		HashMap(sizeType bucketCount, const Hash& _hash = Hash(),
				loadType _loadCap = 0.75) :
				hash(_hash), bucketSize(0), bucket(0), loadCap(_loadCap) {

		}
		HashMap(const HashMap& other) :
				hash(other.hash), start(other.start), finish(other.finish), bucketSize(
						bucketSize), bucket(0), loadCap(other.loadCap) {

		}
		~HashMap() {

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
			return begin();
		}
		constIterator cend() const {
			return end();
		}
		/**
		 * capacity
		 */
		bool empty() {
			return start == finish;
		}
		sizeType size() {
			return 0;
		}
		/**
		 * modifiers
		 */
		void clear() {

		}
		void insert(const pair p) {
			auto k = hash(p.first);
			auto index = k % bucketSize;
			auto it = *(bucket + index);
		}
		void insert(iterator first, iterator last) {

		}
		void erase() {

		}
		void erase(iterator first, iterator last) {

		}
		void swap(const self& other) {

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
			return 0;
		}
		sizeType count(const K& key) {

		}
		iterator find(const K& key) {

		}
		constIterator find(const K& key) const {

		}
		/**
		 * hash policy
		 */
		void reHash(sizeType count) {

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
	};
}

#endif /* ASSO_HASHMAP_H_ */
