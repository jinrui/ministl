/*
 * TestAllocator.cpp
 *
 *  Created on: 2015年11月5日
 *      Author: jinrui
 */
#include "TestAllocator.h"
#include "../vector.h"
#include "../Alloc.h"
#include "../Allocator.h"
#include <assert.h>
namespace MiniStl {
	namespace Test {
		void TestAllocator::testCase1() {
			vector<int, alloc> myvec(8);
			assert(myvec.size() == 0);
		}

		void TestAllocator::testCase2() {
			vector<int, alloc> myvec;
			assert(myvec.size() == 0);
		}
		void TestAllocator::testCase3() {
			vector<int, alloc> myvec;
			assert(myvec.size() == 8);
		}
		void TestAllocator::testAll() {
			testCase1();
			testCase2();
			testCase3();
		}
	}
}

