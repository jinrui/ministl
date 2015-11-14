/*
 * TestList.cpp
 *
 *  Created on: 2015年11月11日
 *      Author: jinrui
 */
#include "TestList.h"
#include "../Alloc.h"
#include "../Allocator.h"
#include <assert.h>
#include <iostream>

#include "../List.h"
namespace MiniStl {
	namespace Test {
		void TestList::testCase1() {
			List<int, Alloc> mylist(8);
			assert(mylist.size() == 8);//size函数有bug,对于list应该用依哥常量比较好
			for (int i = 0; i < 8; i++)
				mylist[i] = i;
			mylist.push_back(9);
			mylist.push_back(10);
			mylist.insert(mylist.begin() + 8, 8);
			int i = 0;
			for (List<int>::constIterator it = mylist.begin();
					it != mylist.end(); ++it, ++i) {
				assert(*it == i);
			}
			i--;
			for (List<int>::constReverseIterator it = mylist.crbegin();
					it != mylist.crend(); ++it, --i) {
				assert(*it == i);
			}
			mylist.erase(mylist.end() - 3, mylist.end());//erase有bug
			i = 0;
			for (List<int>::constIterator it = mylist.begin();
					it != mylist.end(); ++it, ++i) {
				assert(*it == i);
			}
			std::cout << "case1 passed" << std::endl;
		}

		void TestList::testCase2() {
			List<int> mylist;
			List<int> mylist1;
			mylist.insert(mylist.end(), 1);
			mylist.insert(mylist.end(), 2);
			mylist.insert(mylist.end(), 3);
			mylist1.swap(mylist);
			for (int i = 1; i <= 3; i++)
				assert(i == mylist1[i - 1]);
			List<int> mylist3 = mylist1;
			for (int i = 1; i <= 3; i++)
				assert(i == mylist3[i - 1]);
			assert(mylist3.front() == 1);
			assert(mylist3.back() == 3);
			std::cout << "case2 passed" << std::endl;
		}
		void TestList::testCase3() {
		}
		void TestList::testAll() {
			testCase1();
			testCase2();
			testCase3();
			std::cout << "All cases passed" << std::endl;
		}
	}
}

