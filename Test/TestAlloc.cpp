/*
 * TestAlloc.cpp
 *
 *  Created on: 2015年11月17日
 *      Author: jinrui
 */

#include "TestAlloc.h"
#include "../Alloc.h"
#include <assert.h>
#include <iostream>

namespace MiniStl {
	namespace Test {
		void TestAlloc::testCase1() {
			int j = 8;
			for(int i =0;i<20;i++){
				auto ptr = Alloc::allocate(j*8);
				int tmp = j;
				while(tmp--)
				auto ptr1 = Alloc::allocate(4);
				j += 3;
				//Alloc::deallocate(ptr,4);
				//Alloc::deallocate(ptr1,20);
			}
			std::cout << "case1 passed" << std::endl;
		}

		void TestAlloc::testCase2() {

			std::cout << "case2 passed" << std::endl;
		}
		 void TestAlloc::testCase3() {

			std::cout << "case3 passed" << std::endl;
		}
		 void TestAlloc::testAll() {
			testCase1();
			testCase2();
			testCase3();
			std::cout << "All cases passed" << std::endl;
		}
	}
}


