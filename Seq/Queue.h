/*
 * Queue.h
 *
 *  Created on: 2015年11月20日
 *      Author: jinrui
 */

#ifndef QUEUE_H_
#define QUEUE_H_
namespace MiniStl {
	template<typename T, typename Sequence = Deque<T>>
	class Queue {
	public:
		typedef typename Sequence::valueType valueType;
		typedef typename Sequence::ref ref;
		typedef typename Sequence::sizeType sizeType;
	protected:
		Sequence c;  //底层容器
	public:
		bool empty() const {
			return c.empty();
		}
		sizeType size() const {
			return c.size();
		}
		ref front(){
			return c.front();
		}
		ref back() {
			return c.back();
		}
		void push(const valueType& x) {
			c.push_back(x);
		}
		void pop() {
			c.pop_front();
		}
	};
}

#endif /* QUEUE_H_ */
