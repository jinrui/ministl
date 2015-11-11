/*
 * ReverseIterator.h
 *
 *  Created on: 2015年11月7日
 *      Author: jinrui
 */

#ifndef REVERSEITERATOR_H_
#define REVERSEITERATOR_H_
#include "Iterator.h"
namespace MiniStl {
	template<typename iterator>
	class ReverseIterator {
	public:
		typedef typename iteratorTraits<iterator>::iteratorCategory caterory;
		typedef typename iteratorTraits<iterator>::differenceType differenceType;
		typedef typename iteratorTraits<iterator>::pointer pointer;
		typedef typename iteratorTraits<iterator>::ref ref;
		typedef typename iteratorTraits<iterator>::valueType valueType;
		typedef const pointer constPointer;
		typedef const ref constRef;
	private:
		iterator cur;

	public:
		ReverseIterator() :
				cur(0) {
		}
		explicit ReverseIterator(const iterator& it) :
				cur(it) {
		}
		iterator Cur() const {
			return cur;
		}

		ref operator *() {
			return *cur;
		}
		constRef operator *() const {
			return *cur;
		}
		pointer operator ->() {
			return &(operator *());
		}
		constPointer operator ->() const {
			return &(operator *());
		}
		ReverseIterator& operator ++() {
			--cur;
			return *this;
		}
		ReverseIterator operator ++(int) {
			auto tmp = this;
			++this;
			return *tmp;
		}
		ReverseIterator& operator --() {
			++cur;
			return *this;
		}
		ReverseIterator operator --(int) {
			auto tmp = this;
			--this;
			return *tmp;
		}
		friend bool operator ==(const ReverseIterator& lhs,
				const ReverseIterator& rhs) {
			return lhs.Cur() == rhs.Cur();
		}
		friend bool operator !=(const ReverseIterator& lhs,
				const ReverseIterator& rhs) {
			return !(operator ==(lhs, rhs));
		}
	};
}

#endif /* REVERSEITERATOR_H_ */
