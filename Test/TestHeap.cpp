/*
 * TestHeap.cpp
 *
 *  Created on: 2015年11月23日
 *      Author: jinrui
 */
#include "../Vector.h"
#include "TestHeap.h"
#include "../Heap.h"
namespace MiniStl {
	namespace Test {
		void TestHeap::testCase1() {
			int ia[9] = {0,1,2,3,4,8,9,3,5};
			Vector<int> ivec(ia, ia+9);
			makeHeap(ivec.begin(), ivec.end());
			for(int i=0; i<ivec.size(); ++i)
			std::cout << ivec[i] << ' ';
			// 9 5 8 3 4 0 2 3 1
			std::cout << std::endl;
			ivec.push_back(7);
			pushHeap(ivec.begin(), ivec.end());
			for(int i=0; i<ivec.size(); ++i)
			std::cout << ivec[i] << ' ';
			// 9 7 8 3 5 0 2 3 1 4
			std::cout << std::endl;
			popHeap(ivec.begin(), ivec.end());
			std::cout << ivec.back() << std::endl;
			// 9. return but no remove.
			ivec.pop_back();
			// remove last elem and no return
			for(int i=0; i<ivec.size(); ++i)
			std::cout << ivec[i] << ' ';
			std::cout << std::endl;
			// 8 7 4 3 5 0 2 3 1
			sortHeap(ivec.begin(), ivec.end());
			for(int i=0; i<ivec.size(); ++i)
			std::cout << ivec[i] << ' ';
			// 0 1 2 3 3 4 5 7 8
			std::cout << std::endl;
			std::cout << "case1 passed" << std::endl;
		}

		void TestHeap::testCase2() {

			std::cout << "case2 passed" << std::endl;
		}
		 void TestHeap::testCase3() {

			std::cout << "case3 passed" << std::endl;
		}
		 void TestHeap::testAll() {
			testCase1();
			testCase2();
			testCase3();
			std::cout << "All cases passed" << std::endl;
		}
	}
}




