/*
 * Stack.h
 *
 *  Created on: 2015年11月20日
 *      Author: jinrui
 */

#ifndef STACK_H_
#define STACK_H_
#include "../Deque.h"
namespace MiniStl {
	template<typename T, typename Sequence = Deque<T>>
	class Stack {
	public:
		typedef typename Sequence::valueType valueType;
		typedef typename Sequence::ref ref;
		typedef typename Sequence::sizeType sizeType;
	protected:
		Sequence c;  //底层容器
	public:
		bool empty()const{
			return c.empty();
		}
		sizeType size()const{
			return c.size();
		}
		ref top(){
			return c.back();
		}
		void push(const valueType& x){
			c.push_back(x);
		}
		void pop(){
			c.pop_back();
		}
	};
}

#endif /* STACK_H_ */
