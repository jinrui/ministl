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
		return alloc::deallocate(p);
	}
	template<typename T, typename alloc>
	void Allocator<T, alloc>::deallocate(pointer p, sizeType n) {
		for (sizeType i = 0; i < n; i++)
			alloc::deallocate(p + i);
	}
}

#endif /* ALLOCATOR_H_ */
