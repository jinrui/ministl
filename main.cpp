/*
 * main.cpp
 *
 *  Created on: 2015年11月5日
 *      Author: jinrui
 */
#include <iostream>
#include "Test/TestVector.h"
#include "Test/TestList.h"
#include "Test/TestDeque.h"
#include "Test/TestAlloc.h"
using namespace MiniStl;
int main(){
	//MiniStl::Test::TestVector::testAll();
	//MiniStl::Test::TestList::testAll();
	MiniStl::Test::TestDeque::testAll();
	//MiniStl::Test::TestAlloc::testAll();
	return 0;
}


