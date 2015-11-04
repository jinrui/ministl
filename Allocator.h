/*
 * Allocator.h
 *
 *  Created on: 2015年11月4日
 *      Author: jinrui
 */

#ifndef ALLOCATOR_H_
#define ALLOCATOR_H_
namespace MiniStl{
template<typename T, typename alloc> class Allocator{
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
	static void construct(pointer p);
	static void construct(pointer p,constRef x);
	static void destroy(pointer p);
	static void destroy(pointer first, pointer last);
	static pointer address(ref x);
	static constPointer constAddress(constRef x);
	//static sizeType maxSize() const;
};
	template<typename T,typename alloc>
	T* Allocator<T,alloc>::allocate(){
		return static_cast<T*>(alloc::allocate(sizeof(T)));
	}
	template<typename T,typename alloc>
		T* Allocator<T,alloc>::allocate(sizeType n){
			return static_cast<T*>(alloc::allocate(sizeof(T)*n));
	}
	template<typename T,typename alloc>
		void Allocator<T,alloc>::deallocate(pointer p){
			return alloc::deallocate(p);
		}
	template<typename T,typename alloc>
			void Allocator<T,alloc>::deallocate(pointer p,sizeType n){
				for(sizeType i =0;i<n;i++)
				 alloc::deallocate(p+i);
			}

	template<typename T,typename alloc>
		void Allocator<T,alloc>::construct(pointer p){
			new(p) T();
		}
	template<typename T,typename alloc>
	void Allocator<T,alloc>::construct(pointer p, constRef x){
		new(p) T(x);
	}
	template<typename T,typename alloc>
	void Allocator<T,alloc>::destroy(pointer p){
		p->~T();
	}
	template<typename T,typename alloc>
		void Allocator<T,alloc>::destroy(pointer first, pointer last){
			for(pointer cur = first;cur < last;first++)
				cur->~T();
		}
	template<typename T,typename alloc>
	T* Allocator<T,alloc>::address(ref x){
		return static_cast<pointer>(&x);
	}
	template<typename T,typename alloc>
		const T* Allocator<T,alloc>::constAddress(constRef x){
			return static_cast<constPointer>(&x);
		}
//	template<typename T,typename alloc>
//	int Allocator<T,alloc>::maxSize()const{
//			return sizeType(UINT_MAX/sizeof(T));
//		}
}




#endif /* ALLOCATOR_H_ */
