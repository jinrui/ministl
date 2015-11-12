/*
 * Iterator.h
 *
 *  Created on: 2015年11月3日
 *      Author: jinrui
 */

#ifndef ITERATOR_H_
#define ITERATOR_H_
namespace MiniStl {

	typedef int ptrdiffT;

	/**
	 * 迭代器类型*
	 */

	//read only
	struct inputIteratorTag {
	};

	//write only
	struct outputIteratorTag {
	};

	//前向迭代器，input所有功能和output大部分功能
	struct forwardIteratorTag: public inputIteratorTag {
	};

	//双向迭代器，支持向后遍历
	struct biDirectionalIteratorTag: public forwardIteratorTag {
	};

	//随机存取，支持距离相关操作，一半在string，vector等中
	struct randomAccessIteratorTag: public biDirectionalIteratorTag {
	};

	/**
	 *几种迭代器,提供了几种类型
	 */
	//分别是迭代器类型，值类型，前后节点间隔单位(一般为int)，指针，引用
	//input型iterator
	template<typename T, typename Distance>
	struct inputIterator {
		typedef inputIteratorTag iteratorCategory;
		typedef T valueType;
		typedef Distance differenceType;
		typedef T* pointer;
		typedef T& ref;
	};

	//output型iterator
	struct outputIterator {
		typedef inputIteratorTag iteratorCategory;
		typedef void valueType;
		typedef void differenceType;
		typedef void pointer;
		typedef void ref;
	};

	//forward型iterator
	template<typename T, typename Distance>
	struct forwardIterator {
		typedef forwardIteratorTag iteratorCategory;
		typedef T valueType;
		typedef Distance differenceType;
		typedef T* pointer;
		typedef T& ref;
	};

	//biDirectional型iterator
	template<typename T, typename Distance = int>
	struct biDirectionalIterator {
		typedef biDirectionalIteratorTag iteratorCategory;
		typedef T valueType;
		typedef Distance differenceType;
		typedef T* pointer;
		typedef T& ref;
	};

	//randomAccess型iterator
	template<typename T, typename Distance>
	struct randomAccessIterator {
		typedef randomAccessIteratorTag iteratorCategory;
		typedef T valueType;
		typedef Distance differenceType;
		typedef T* pointer;
		typedef T& ref;
	};

	/**
	 * iteratorTraits，这是iterator和容器算法的粘合剂，保证了兼容性.使用traits主要
	 * 是因为有时需要使用iterator里的类型。使用偏特化主要是为了将class和原生指针兼容
	 */
	template<typename iterator>
	struct iteratorTraits {
		typedef typename iterator::iteratorCategory iteratorCategory;
		typedef typename iterator::valueType valueType;
		typedef typename iterator::differenceType differenceType;
		typedef typename iterator::pointer pointer;
		typedef typename iterator::ref ref;
	};

	//偏特化,原生指针
	template<typename T>
	struct iteratorTraits<T*> {
		typedef randomAccessIteratorTag iteratorCategory;
		typedef T valueType;
		typedef ptrdiffT differenceType;
		typedef T* pointer;
		typedef T& ref;
	};

	//偏特化,const原生指针
	template<typename T>
	struct iteratorTraits<const T*> {
		typedef randomAccessIteratorTag iteratorCategory;
		typedef T valueType;
		typedef ptrdiffT differenceType;
		typedef const T* pointer;
		typedef const T& ref;
	};
	/**
	 * 几个获取iteratorTraits类型的函数
	 */
	//获取category
	template<typename iterator>
	inline typename iteratorTraits<iterator>::iteratorCategory iteratorCategory(
			const iterator&) {
		typedef typename iteratorTraits<iterator>::iteratorCategory categry;
		return categry();
	}

	//获取valuetype
	template<typename iterator>
	inline typename iteratorTraits<iterator>::valueType*
	iteratorValuetype(const iterator&) {
		typedef typename iteratorTraits<iterator>::valueType type;
		return static_cast<type*>(0);
	}

	//获取difftype
	template<typename iterator>
	inline typename iteratorTraits<iterator>::differenceType*
	iteratordifferenceType(const iterator&) {
		typedef typename iteratorTraits<iterator>::differenceType type;
		return static_cast<type*>(0);
	}
}

#endif /* ITERATOR_H_ */
