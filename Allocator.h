/*
 * Allocator.h
 *
 *  Created on: 2015年11月4日
 *      Author: jinrui
 */

#ifndef ALLOCATOR_H_
#define ALLOCATOR_H_
namespace MiniStl {
	/**
	 * 这个提供给容器使用
	 */
	template<typename T, typename alloc> class Allocator {
	public:
		/**
		 * 几种对外的类型
		 */
		typedef int ptrdiffT;
		typedef int sizeT;

		typedef T valueType;
		typedef T* pointer;
		typedef const T* constPointer;
		typedef T& ref;
		typedef const T& constRef;
		typedef sizeT sizeType;
		typedef ptrdiffT differenceType;

		/**
		 * 几种对外的接口
		 */
		static pointer allocate();
		static pointer allocate(sizeType n);
		static void deallocate(pointer p);
		static void deallocate(pointer p, sizeType n);
		static void deallocate(pointer first, pointer last);
	};
	template<typename T, typename alloc>
	T* Allocator<T, alloc>::allocate() {
		return static_cast<T*>(alloc::allocate(sizeof(T)));
	}
	template<typename T, typename alloc>
	T* Allocator<T, alloc>::allocate(sizeType n) {
		return static_cast<T*>(alloc::allocate(sizeof(T) * n));
	}
	template<typename T, typename alloc>
	void Allocator<T, alloc>::deallocate(pointer p) {
		return alloc::deallocate(p,sizeof(T));
	}
	template<typename T, typename alloc>
	void Allocator<T, alloc>::deallocate(pointer p, sizeType n) {
			alloc::deallocate(p,sizeof(T)*n);
	}
	template<typename T, typename alloc>
	void Allocator<T, alloc>::deallocate(pointer first, pointer last) {
			auto tmp = first;
			while(tmp!=last){
				auto tmp1 = tmp->next;
				deallocate(tmp);
				tmp=tmp1;
			}
	}
//	template<typename T, typename alloc>
//	void Allocator<int, alloc>::deallocate(int* first, int* last) {
//			auto tmp = first;
//			while(tmp!=last){
//				auto tmp1 = tmp+1;
//				deallocate(tmp);
//				tmp=tmp1;
//			}
//	}
}

#endif /* ALLOCATOR_H_ */
