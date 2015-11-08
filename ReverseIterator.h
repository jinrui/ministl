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
		iterator base;
		iterator cur;

	public:
		ReverseIterator() :
				base(0), cur(0) {
		}
		explicit ReverseIterator(const iterator& it) :
				base(it), cur(it - 1) {
		}
		explicit ReverseIterator(const ReverseIterator& rit) :
				base(rit.Base()), cur(base - 1) {

		}
		iterator Base() const {
			return base;
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
			--base;
			--cur;
			return *this;
		}
		ReverseIterator operator ++(int) {
			auto tmp = this;
			++this;
			return *tmp;
		}
		ReverseIterator& operator --() {
			++base;
			++cur;
			return *this;
		}
		ReverseIterator operator --(int) {
			auto tmp = this;
			--this;
			return *tmp;
		}
		friend ReverseIterator operator ==(const ReverseIterator lhs,
				const ReverseIterator rhs) {
			return lhs.Base() == rhs.Base();
		}
		friend ReverseIterator operator !=(const ReverseIterator lhs,
				const ReverseIterator rhs) {
			return !(operator ==(lhs, rhs));
		}
	};
}

#endif /* REVERSEITERATOR_H_ */
