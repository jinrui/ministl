/*
 * uninitialized.h
 *
 *  Created on: 2015年11月6日
 *      Author: jinrui
 */

#ifndef UNINITIALIZED_H_
#define UNINITIALIZED_H_
namespace MiniStl {
	//这里没有针对pod data进行特化。
	template<typename InputIterator, typename ForwardIterator>
	ForwardIterator uninitializedCopy(InputIterator first, InputIterator last,
			ForwardIterator result) {
		for (int i = 0; first != last; ++first, ++i)
			construct(&*(result + i), *first);
	}
}

#endif /* UNINITIALIZED_H_ */
