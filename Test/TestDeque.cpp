/*
 * TestDeque.cpp
 *
 *  Created on: 2015年11月15日
 *      Author: jinrui
 */
#include "TestDeque.h"
#include "../Alloc.h"
#include "../Allocator.h"
#include <assert.h>
#include <iostream>
#include "../Deque.h"

namespace MiniStl {
	namespace Test {
		void TestDeque::testCase1() {
			Deque<int, Alloc> mydeq(8);
			assert(mydeq.size() == 8);
			for (int i = 0; i < 8; i++)
				mydeq[i] = i;
			mydeq.push_back(9);
			mydeq.push_back(10);
			mydeq.insert(mydeq.begin() + 8, 8);
			int i = 0;
			for (auto it = mydeq.cbegin(); it != mydeq.cend(); ++it, ++i) {
				assert(*it == i);
			}
			i--;
			for (auto it = mydeq.crbegin(); it != mydeq.crend(); ++it, --i) {
				assert(*it == i);
			}
			mydeq.erase(mydeq.end() - 3, mydeq.end());
			i = 0;
			for (Deque<int>::constIterator it = mydeq.begin();
					it != mydeq.end(); ++it, ++i) {
				assert(*it == i);
			}
			std::cout << "case1 passed" << std::endl;
		}

		void TestDeque::testCase2() {
			Deque<int> mydeq;
			Deque<int> mydeq1;
			mydeq.insert(mydeq.end(), 1);
			mydeq.insert(mydeq.end(), 2);
			mydeq.insert(mydeq.end(), 3);
			for (int i = 1; i <= 3; i++)
				assert(i == mydeq[i - 1]);
			mydeq1.swap(mydeq);
			for (int i = 1; i <= 3; i++)
				assert(i == mydeq1[i - 1]);
			Deque<int> mydeq3 = mydeq1;
			for (int i = 1; i <= 3; i++)
				assert(i == mydeq3[i - 1]);
			assert(mydeq3.front() == 1);
			assert(mydeq3.back() == 3);
			std::cout << "case2 passed" << std::endl;
		}
		void TestDeque::testCase3() {
			Deque<int, Alloc> mydeq;
			for (int i = 0; i < 100000; i++)
				mydeq.push_back(i);
			for (int i = 0; i < 100000; i++) {
				assert(i == mydeq[i]);
			}
			for (int i = 99999; i >=0; i--)
				mydeq.push_front(i);
			for (int i = 0; i < 100000; ++i) {
				assert(i == mydeq[i]);
			}
			std::cout << "case3 passed" << std::endl;
		}
		void TestDeque::testAll() {
			testCase1();
			testCase2();
			testCase3();
			std::cout << "All cases passed" << std::endl;
		}
	}
}

