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
			for (int i = 0; i < 8; i++)
				myvec[i] = i;
			myvec.push_back(9);
			myvec.push_back(10);
			myvec.insert(myvec.begin() + 8, 8);
			int i = 0;
			for (Vector<int>::constIterator it = myvec.begin();
					it != myvec.end(); ++it, ++i) {
				assert(*it == i);
			}
			i--;
			for (Vector<int>::constReverseIterator it = myvec.crbegin();
					it != myvec.crend(); ++it, --i) {
				assert(*it == i);
			}
			myvec.at(100);
		}

		void TestVector::testCase2() {
		}
		void TestVector::testCase3() {
		}
		void TestVector::testAll() {
			testCase1();
			testCase2();
			testCase3();
		}
	}
}

