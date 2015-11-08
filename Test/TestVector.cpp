/*
 * TestAllocator.cpp
 *
 *  Created on: 2015年11月5日
 *      Author: jinrui
 */
#include "TestVector.h"
#include "../Alloc.h"
#include "../Allocator.h"
#include <assert.h>
#include <iostream>

#include "../Vector.h"
namespace MiniStl {
	namespace Test {
		void TestVector::testCase1() {
			Vector<int, Alloc> myvec(8);
			assert(myvec.size() == 8);
			Vector<int> myvec1;
			myvec1.push_back(123);
			myvec1.push_back(4);
			myvec1.push_back(5);
			assert(myvec1.capacity() == 4);
			myvec1.insert(myvec1.begin(),88);
			myvec1.insert(myvec1.begin()+1,8998);
			myvec1.insert(myvec1.begin()+1,86788);
			myvec1.erase(myvec1.begin());
			assert(myvec1[0] == 86788);
			for(auto it = myvec1.begin();it != myvec1.end();++it)
							std::cout<<*it<<" ";
		}

		void TestVector::testCase2() {
			Vector<int, Alloc> myvec;
			assert(myvec.size() == 0);
		}
		void TestVector::testCase3() {
			Vector<int, Alloc> myvec;
			assert(myvec.size() == 0);
		}
		void TestVector::testAll() {
			testCase1();
			testCase2();
			testCase3();
		}
	}
}

