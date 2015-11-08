/*
 * Alloc.h
 *
 *  Created on: 2015年11月4日
 *      Author: jinrui
 */

#ifndef ALLOC_H_
#define ALLOC_H_
/**
 * 用的是二级内存分配机制，超过128K就用一级分配器，更小的就用二级
 */
namespace MiniStl {
	class Alloc {
	private:
		typedef int sizeT;
		enum {
			ALIGN = 8
		}; //小型区块上调边界
		enum {
			MAXBYTES = 128
		}; //小型区块上限
		enum {
			NFREELISTS = MAXBYTES / ALIGN
		}; //freelist 个数

		//将bytes调至8的倍数
		static sizeT ROUNDUP(sizeT bytes) {
			return (bytes + ALIGN - 1) & ~(ALIGN - 1);
		}
		/**
		 *freelist节点构造
		 */
		union obj {
			union obj* next;
			char data[1];	//client能看见的
		};
		//默认为16个lists，分别是8，16，24，32，49...128
		static obj* volatile free_list[NFREELISTS];
		static sizeT FREELISTINDEX(sizeT bytes) {
			return ROUNDUP(bytes) / ALIGN - 1;
		}

		static void* reFill(sizeT n); //找不到空闲的则从系统取出
		static char* chunkAlloc(sizeT size, int &nobjs); //配置一大块空间，可容纳nobjs个大小为size的区块

		//chunk allocation state
		static char* startFree; //内存池起始位置
		static char* endFree; //内存池结束位置
		static sizeT heapSize;

	public:
		static void* allocate(sizeT n);
		static void deallocate(void* p, sizeT n);
		static void* reallocate(void* p, sizeT oldSz, sizeT newSz);
	};

}

#endif /* ALLOC_H_ */
