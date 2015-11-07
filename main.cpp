/*
 * main.cpp
 *
 *  Created on: 2015年11月5日
 *      Author: jinrui
 */
#include <iostream>
#include "Test/TestAllocator.h"
using namespace MiniStl;
int main(){
	MiniStl::Test::TestAllocator::testAll();
	std::cout<<"nihao";
	return 0;
}


