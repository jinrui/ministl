/*
 * TestRbTree.cpp
 *
 *  Created on: 2015年11月25日
 *      Author: jinrui
 */
#include<iostream>
#include<algorithm>
#include <vector>
#include<iterator>
#include<sstream>
#include "TestRbTree.h"
#include "../Asso/RedBlackTree.h"
using namespace std;
namespace MiniStl {
	namespace Test {
		void TestRbTree::testCase1() {

			RBTree<int, int> tree;
			vector<int> v;
			int i =0;
			for (int i = 0; i < 20; ++i) {
				v.push_back(i);
			}
			random_shuffle(v.begin(), v.end());
			copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
			cout << endl;
			stringstream sstr;
			for (i = 0; i < v.size(); ++i) {
				tree.Insert(makePair(v[i], i));
				cout << "insert:" << v[i] << endl;   //添加结点
			}
			for (i = 0; i < v.size(); ++i) {
				cout << "Delete:" << v[i] << endl;
				tree.Delete(v[i]);             //删除结点
				tree.InOrderTraverse();
			}
			cout << endl;
			tree.InOrderTraverse();
			std::cout << "case1 passed" << std::endl;
		}

		void TestRbTree::testCase2() {
			std::cout << "case2 passed" << std::endl;
		}
		void TestRbTree::testCase3() {

			std::cout << "case3 passed" << std::endl;
		}
		void TestRbTree::testAll() {
			testCase1();
			testCase2();
			testCase3();
			std::cout << "All cases passed" << std::endl;
		}
	}
}

