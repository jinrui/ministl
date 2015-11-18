/*
 * uninitialized.h
 *
 *  Created on: 2015年11月6日
 *      Author: jinrui
 */

#ifndef UNINITIALIZED_H_
#define UNINITIALIZED_H_
#include "Construct.h"
namespace MiniStl {
	/**
	 * TODO 这里面的操作应该是commit or rollback。异常处理没有做
	 * 这里没有针对pod data进行特化。如果需要特化，就用traits技巧，也不难,主要是要用到copy函数，现在不想做
	 */
	template<typename InputIterator, typename ForwardIterator>
	inline ForwardIterator uninitializedCopy(InputIterator first,
			InputIterator last, ForwardIterator result) {
		for (int i = 0; first != last; ++first, ++i)
			construct(&*(result + i), *first);
		return result;
	}
	template<typename InputIterator, typename ForwardIterator>
	inline ForwardIterator uninitializedCopyBck(InputIterator first,
			InputIterator last, ForwardIterator result) {
		first--, last--;
		int len = last - first;
		for (int i = len-1; first != last; --last, --i)
			construct(&*(result + i), *last);
		return result;
	}

	template<typename T, typename ForwardIterator>
	inline void uninitializedFill(ForwardIterator first, ForwardIterator last,
			const T& result) {
		for (; first != last; ++first)
			construct(&*(first), result);
	}

	template<typename T, typename ForwardIterator, typename Size>
	inline ForwardIterator uninitializedFillN(ForwardIterator first, Size n,
			const T& result) {
		ForwardIterator cur = first;
		for (int i = 0; i < n; ++cur, ++i)
			construct(&*cur, result);
		return cur;
	}
	template<typename ForwardIterator, typename InputIterator>
	inline InputIterator uninitializedFillNI(InputIterator result,
			ForwardIterator first, ForwardIterator last) {
		InputIterator cur = result;
		for (auto it = first; it != last; ++it, ++cur)
			construct(&*cur, *it);
		return result;
	}
}

#endif /* UNINITIALIZED_H_ */
