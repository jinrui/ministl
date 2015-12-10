/*
 * Algorithm.h
 *
 *  Created on: 2015年12月10日
 *      Author: apple
 */

#ifndef ALGORITHM_ALGORITHM_H_
#define ALGORITHM_ALGORITHM_H_
namespace MiniStl{
/**
 * 不修改内容的操作
 */
template<typename InputIterator,typename Fun>
bool allOf(InputIterator start,InputIterator end,Fun fun){
	for(;start!=end;++start)
		if(!fun(*start)) return false;
	return true;
}
template<typename InputIterator,typename Fun>
bool forEach(InputIterator start,InputIterator end,Fun fun){
	for(;start!=end;++start)
		fun(*start);
	return true;
}
/**
 * 千篇一律。。懒得实现了。。
 */
}




#endif /* ALGORITHM_ALGORITHM_H_ */
