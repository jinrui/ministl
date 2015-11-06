/*
 * Construct.h
 *
 *  Created on: 2015年11月6日
 *      Author: jinrui
 */

#ifndef CONSTRUCT_H_
#define CONSTRUCT_H_

#include <new>
#include "typeTraits.h"
namespace MiniStl {
	template<typename T1, typename T2>
	inline void construct(T1* p, const T2& value) {
		new (p) T1(value);
	}
	//下面是几个destory
	template<typename T>
	inline void destory(T* pointer) {
		pointer->~T();
	}

	template<typename ForwardIterator, typename T>
	inline void _destory(ForwardIterator first, ForwardIterator last, T*) {
		typedef typename typeTraits<T>::hasTrivialDestructor trivalDestructor;
		_destroyAux(first, last, trivalDestructor);
	}

	template<typename ForwardIterator>
	inline void _destoryAux(ForwardIterator first, ForwardIterator last,
			falseType) {
		for (; first < last; ++first)
			destory(&(*first));
	}

	template<typename ForwardIterator>
	inline void destory(ForwardIterator first, ForwardIterator last) {
		_destory(first, last, iteratorValuetype(first));
	}

	template<typename ForwardIterator>
	inline void _destoryAux(ForwardIterator first, ForwardIterator last,
			trueType) {
	}

	//以下是destroy 迭代器特化版本
	inline void destroy(char*, char*) {
	}
	inline void destroy(wchar_t*, wchar_t*) {
	}
}
#endif /* CONSTRUCT_H_ */
