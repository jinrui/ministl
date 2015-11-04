/*
 * TestAllocator.cpp
 *
 *  Created on: 2015年11月5日
 *      Author: jinrui
 */
#include "TestAllocator.h"
#include <vector>
#include "../alloc.h"
#include "../allocator.h"
#include <assert.h>
namespace MiniStl{
	namespace Test{
		void TestAllocator::testCase1(){
			std::vector<int, alloc> myvec;
			assert(myvec.size() == 8);
		}

		void TestAllocator::testCase2(){
					std::vector<int, alloc> myvec;
					assert(myvec.size() == 8);
				}
		void TestAllocator::testCase3(){
					std::vector<int, alloc> myvec;
					assert(myvec.size() == 8);
				}
		void TestAllocator::testAll(){
					testCase1();
					testCase2();
					testCase3();
				}
	}
}



