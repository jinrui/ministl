/*
 * Heap.h
 *
 *  Created on: 2015年11月20日
 *      Author: jinrui
 */

#ifndef HEAP_H_
#define HEAP_H_
/**
 * 最大堆
 */
template<typename RandomAccessIterator>
inline void heapAdjust(RandomAccessIterator first, int pos, int len) {
	int left = pos * 2 + 1;
	int right = left + 1;
	int largest = pos;
	if (left < len && first[left] > first[pos]) {
		largest = left;
	}
	if (right < len && first[largest] < first[right]) {
		largest = right;
	}
	if (largest != pos) {
		std::swap(first[largest], first[pos]); //较大的节点值将交换到其所在节点的父节点
		heapAdjust(first, largest, len); //递归遍历
	}
}
template<typename RandomAccessIterator>
inline void makeHeap(RandomAccessIterator first, RandomAccessIterator last) {
	int len = last - first;
	for (int i = len / 2 - 1; i >= 0; i--)
		heapAdjust(first, i, len);
}
/**
 * 确保插入值已经再容器最后，才能调用此方法
 */
template<typename RandomAccessIterator>
inline void pushHeap(RandomAccessIterator first, RandomAccessIterator last) {
	auto len = last - first;
	auto i = len - 1;
	for (auto j = (i - 1) / 2; j >= 0 && i != 0 && first[j] < first[i];
			i = j, j = (j - 1) / 2)
		std::swap(first[i], first[j]);
}
template<typename RandomAccessIterator>
inline void popHeap(RandomAccessIterator first, RandomAccessIterator last) {
	std::swap(*first,*(last-1));
	heapAdjust(first,0,last-first-1);
}
template<typename RandomAccessIterator>
inline void sortHeap(RandomAccessIterator first, RandomAccessIterator last) {
	auto len = last-first;
	while(len){
		popHeap(first,first+len);
		--len;
	}
}

#endif /* HEAP_H_ */
