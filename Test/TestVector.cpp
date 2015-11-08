/*
 * TestAllocator.cpp
 *
 *  Created on: 2015年11月5日
 *      Author: jinrui
 */
#include "TestVector.h"
#include "../vector.h"
#include "../Alloc.h"
#include "../Allocator.h"
#include <assert.h>
namespace MiniStl {
	namespace Test {
		void TestVector::testCase1() {
			vector<int, alloc> myvec(8);
			assert(myvec.size() == 8);
			vector<int> myvec1;
			assert(myvec1.size() == 0);
		}

		void TestVector::testCase2() {
			vector<int, alloc> myvec;
			assert(myvec.size() == 0);
		}
		void TestVector::testCase3() {
			vector<int, alloc> myvec;
			assert(myvec.size() == 0);
		}
		void TestVector::testAll() {
			testCase1();
			testCase2();
			testCase3();
		}
	}
}

