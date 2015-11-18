/*
 * TestVector.cpp
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
			myvec.erase(myvec.end() - 3, myvec.end());
			i = 0;
			for (Vector<int>::constIterator it = myvec.begin();
					it != myvec.end(); ++it, ++i) {
				assert(*it == i);
			}
			std::cout << "case1 passed" << std::endl;
		}

		void TestVector::testCase2() {
			Vector<int> myvec;
			Vector<int> myvec1;
			myvec.insert(myvec.end(), 1);
			myvec.insert(myvec.end(), 2);
			myvec.insert(myvec.end(), 3);
			myvec1.swap(myvec);
			for (int i = 1; i <= 3; i++)
				assert(i == myvec1[i - 1]);
			Vector<int> myvec3 = myvec1;
			for (int i = 1; i <= 3; i++)
				assert(i == myvec3[i - 1]);
			assert(myvec3.front() == 1);
			assert(myvec3.back() == 3);
			std::cout << "case2 passed" << std::endl;
		}
		void TestVector::testCase3() {
			Vector<long long> myvec;
			for (int i = 0; i < 1000000; i++)
				myvec.push_back(i);
			for (int i = 0; i < 1000000; i++) {
				assert(i == myvec[i]);
			}
			std::cout << "case3 passed" << std::endl;
		}
		void TestVector::testAll() {
			testCase1();
			testCase2();
			testCase3();
			std::cout << "All cases passed" << std::endl;
		}
	}
}

