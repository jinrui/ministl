/*
 * MallocAlloc.h
 *
 *  Created on: 2015年11月4日
 *      Author: jinrui
 */
#ifndef MALLOCALLOC_H_
#define MALLOCALLOC_H_
#include <stdlib.h>
#include <iostream>

namespace MiniStl {
	//一级内存分配，包括一些异常处理
	class mallocAlloc {
		typedef int sizeT;
	private:
		//内存不足时的处理方法
		static void* oomMalloc(sizeT n) {
			void* result;
			while (1) {
				if (0 == mallocAllocOomHandler) {
					std::cerr << "out of memory" << std::endl;
					exit(1);
				}
				mallocAllocOomHandler();
				result = malloc(n);
				if (result)
					return result;
			}
		}
		static void* oomRealloc(void* p, sizeT n) {
			void* result;
			while (1) {
				if (0 == mallocAllocOomHandler) {
					std::cerr << "out of memory" << std::endl;
					exit(1);
				}
				mallocAllocOomHandler();
				result = realloc(p, n);
				if (result)
					return result;
			}
		}
		static void (*mallocAllocOomHandler)();

	public:
		static void * allocate(sizeT n) {
			void* result = malloc(n);
			if (0 == result)
				result = oomMalloc(n);
			return result;
		}
		static void deallocate(void* p, sizeT){
				free(p); //第一级直接用free
		}
		static void* reallocate(void* p, sizeT, sizeT newSz) {
			void* result = realloc(p, newSz);
			if (0 == result)
				result = oomRealloc(p, newSz);
			return result;
		}

		//通过它指定内存不足处理方法
		static void (*setMallocHandler(void (*f)()))() {
					void (*old)() = mallocAllocOomHandler;
					mallocAllocOomHandler = f;
					return old;
				}

	};
			void (*mallocAlloc::mallocAllocOomHandler)() = 0;
}

#endif /* MALLOCALLOC_H_ */
