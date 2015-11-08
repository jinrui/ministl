/*
 * Alloc.cpp
 *
 *  Created on: 2015年11月4日
 *      Author: jinrui
 */
#include "Alloc.h"
#include "MallocAlloc.h"

namespace MiniStl {
	alloc::obj* volatile alloc::free_list[NFREELISTS] = { 0 };
	char* alloc::startFree = 0; //内存池起始位置
	char* alloc::endFree = 0; //内存池结束位置
	alloc::sizeT alloc::heapSize = 0;
	void* alloc::allocate(sizeT n) {
		obj* volatile * myFreeList;
		obj* result;
		//>128则调用一级配置器
		if(n == 0) return 0;
		if (n > MAXBYTES)
			return mallocAlloc::allocate(n);
		myFreeList = free_list + FREELISTINDEX(n);
		result = *myFreeList;
		if (0 == result) {
			void* r = reFill(n);
			return r;
		}
		//调整freelist
		*myFreeList = result->next;
		return result;
	}

	void alloc::deallocate(void* p, sizeT n) {
		obj* volatile * myFreeList;
		if(n == 0) return;
		//>128则调用一级配置器
		if (n > MAXBYTES)
			return mallocAlloc::deallocate(p, n);
		myFreeList = free_list + FREELISTINDEX(n);
		((obj*) p)->next = *myFreeList;	//这里又除错
		*myFreeList = (obj*) p;
	}

	void* alloc::reallocate(void* p, sizeT oldSz, sizeT newSz) {
		obj* volatile * myFreeList;
		obj* result;
		//>128则调用一级配置器
		if (newSz > MAXBYTES)
			return mallocAlloc::reallocate(p, oldSz, newSz);
		myFreeList = free_list + FREELISTINDEX(newSz);
		result = *myFreeList;
		if (0 == result) {
			void* r = reFill(newSz);
			return r;
		}
		//调整freelist
		*myFreeList = result->next;
		return result;
	}

	/**
	 * 这是一个大的内存区，用来提供给reFill方法，在这里面移动startFreehe endFree
	 * 如果不够分配，那么先是从heap中malloc，如果还是不够，那么从freelist中找，放回内存池
	 */
	char* alloc::chunkAlloc(sizeT n, int& nobjs) {
		sizeT left = endFree - startFree;
		sizeT totalBytes = n * nobjs;
		char* result;
		nobjs = std::min(nobjs, left / n);
		if (nobjs >= 1) {
			result = startFree;
			startFree += nobjs * n;
			return result;
		}
		sizeT bytesToGet = (totalBytes << 1) + (ROUNDUP(heapSize) >> 4);
		if (left > 0) {
			auto myFreeList = free_list + FREELISTINDEX(left);
			((obj*) startFree)->next = *myFreeList;	//这一句执行错误
			*myFreeList = (obj*) startFree;
		}
		//配置heap空间，用来补充内存池
		startFree = (char*) malloc(bytesToGet);
		if (0 == startFree) {
			//heap空间不足
			obj* volatile *myFreeList;

			// 从freelist中找出第一个大于它且合适的
			for (int i = n; i <= MAXBYTES; i += ALIGN) {
				myFreeList = free_list + FREELISTINDEX(i);
				if (0 != *myFreeList) {
					auto tmp = *myFreeList;
					*myFreeList = tmp->next;
					startFree = (char*) tmp;
					endFree = startFree + i;
					nobjs = 20;
					return chunkAlloc(n, nobjs);
				}
			}
			endFree = 0;
			startFree = (char*) mallocAlloc::allocate(bytesToGet);
		}
		heapSize += bytesToGet;
		endFree = startFree + bytesToGet;
		nobjs = 20;
		return chunkAlloc(n, nobjs);
	}

	/**
	 * 用的是每次添加到头部的方法,大概和stl里不一样，233
	 */
	void* alloc::reFill(sizeT n) {
		int nobjs = 20;
		char* chunk = chunkAlloc(n, nobjs);
		if (1 == nobjs)
			return chunk;
		obj* volatile * myFreeList;
		obj* result;
		obj* cur, *next;
		myFreeList = free_list + FREELISTINDEX(n);
		result = (obj*) chunk;
		*myFreeList = next = (obj*) (chunk + n);
		for (int i = 1; i < nobjs; i++) {
			cur = next;
			next = (obj*) (reinterpret_cast<char*>(next) + n);
			cur->next = *myFreeList;
			*myFreeList = cur;
		}
		return result;
	}
}

