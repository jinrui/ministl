/*
 * Map.h
 *
 *  Created on: 2015年11月26日
 *      Author: jinrui
 */

#ifndef ASSO_MAP_H_
#define ASSO_MAP_H_
#include "Pair.h"
#include "RedBlackTree.h"
#include "../Alloc.h"
#include "../Allocator.h"
namespace MiniStl {
	template<typename K, typename V, typename alloc = Alloc>
	class Map {
		typedef RBTree<K, V, alloc> rbTree;
		rbTree rbt;
		typedef typename rbTree::valueType valueType;
		typedef typename rbTree::ref ref;
		typedef typename rbTree::pointer pointer;
		typedef typename rbTree::sizeType sizeType;
		typedef typename rbTree::iterator iterator;
		typedef typename rbTree::reverseIterator reverseIterator;
		/**
		 * 构造函数和析构函数
		 */
	public:
		Map() :
				rbt() {
		}
		~Map() {
			~rbt();
		}
	public:
		iterator begin() {
			return rbt.begin();
		}
		iterator end() {
			return rbt.end();
		}
		void insert(const valueType& x) {
			rbt.insert(x);
		}
		template<typename inputIterator>
		void insert(inputIterator first, inputIterator last) {
			for (; first != last; ++first)
				insert(*first);
		}

	};
}

#endif /* ASSO_MAP_H_ */
