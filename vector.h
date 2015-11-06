/*
 * vector
 *
 *  Created on: 2015年11月6日
 *      Author: jinrui
 */

#ifndef VECTOR_H_
#define VECTOR_H_
namespace MiniStl {
	template<typename T, typename Alloc = alloc> class vector {
		typedef int sizeT;
		typedef int ptrdiffT;
		typedef T* iterator;
		typedef T valueType;
		typedef T* pointer;
		typedef const T* constPointer;
		typedef T& ref;
		typedef const T& constRef;
		typedef sizeT sizeType;
		typedef ptrdiffT differenceType;

	protected:
		//默认的空间配置器为二级配置器
		typedef Allocator<T, Alloc> dataAllocator;
		/**
		 * 空间使用标志
		 */
		iterator start;
		iterator finish;
		iterator endOfStorage;

	public:
		//几个常见的构造函数,析构函数
		vector() :
				start(0), finish(0), endOfStorage(0) {
		}
		/**
		 * TODO 几个其他的接口，需要construct的支持，待做
		 */
		//vector(sizeType n, constRef value){}
		~vector() {
			destory(start, finish);
			dataAllocator::deallocate();
		}
		//几个常见的接口
		iterator begin() {
			return start;
		}
		iterator end() {
			return finish;
		}
		sizeType size() {
			return static_cast<sizeType>(finish - start);
		}
		sizeType capacity() {
			return endOfStorage - start;
		}
		bool empty() {
			return finish == start;
		}
		ref operator[](sizeType n) {
			return *(start + n);
		}
		ref front() {
			return *begin();
		}
		ref back() {
			return *(end() - 1);
		}
		/**
		 * 重点方法，pushback可以调用insert
		 */
		void push_back() ;
		//多种泛化
		void insert(iterator cur, const T& val);
		void insert(iterator first,sizeT n, const T& val);
		void insert(iterator position,inputIterator first,inputIterator last);
		void pop_back() {
			--finish;
			destory(finish);
		}
		//清楚某个位置上元素，也不简单,注意调用copy
		iterator erase(iterator position) {
			return erase(position,position+1);
		}
		iterator erase(iterator first, iterator last) {
				int dis = last - first;
				auto cur = first + dis;
				for(;cur < finish;++first,++cur)
					*first = *cur;
				for(int i = 0;i<dis;i++,--cur)
					destory(&*cur);
				finish = finish - dis;
				return last = first;
		}

		void resize(sizeType newSz, const T& x) {
			if (newSz < size())
				erase(begin() + newSz, end());
			else
				insert(end(), newSz - size(), x);
		}
	};
}

#endif /* VECTOR_H_ */
