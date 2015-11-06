/*
 * TypeTraits.h
 *
 *  Created on: 2015年11月6日
 *      Author: jinrui
 */

#ifndef TYPETRAITS_H_
#define TYPETRAITS_H_
namespace MiniStl {
	/**
	 * traits技巧，包括对不同的类型做定义
	 */
	struct trueType {
	};
	struct falseType {
	};
	template<typename T>
	class typeTraits {
		typedef falseType hasTrivialDefaultConstructor;
		typedef falseType hasTrivialCopyConstructor;
		typedef falseType hasTrivialAssignmentConstructor;
		typedef falseType hasTrivialConstructor;
		typedef falseType isPODType;
	};
//各种特化
	template<>
	class typeTraits<bool> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialConstructor;
		typedef trueType isPODType;
	};
	template<>
	class typeTraits<char> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialConstructor;
		typedef trueType isPODType;
	};
	template<>
	class typeTraits<unsigned char> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialConstructor;
		typedef trueType isPODType;
	};
	template<>
	class typeTraits<short> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialConstructor;
		typedef trueType isPODType;
	};
	template<>
	class typeTraits<unsigned short> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialConstructor;
		typedef trueType isPODType;
	};
	template<>
	class typeTraits<int> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialConstructor;
		typedef trueType isPODType;
	};
	template<>
	class typeTraits<unsigned int> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialConstructor;
		typedef trueType isPODType;
	};
	template<>
	class typeTraits<int> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialConstructor;
		typedef trueType isPODType;
	};
	template<>
	class typeTraits<long> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialConstructor;
		typedef trueType isPODType;
	};
	template<>
	class typeTraits<unsigned long> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialConstructor;
		typedef trueType isPODType;
	};
	template<>
	class typeTraits<long long> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialConstructor;
		typedef trueType isPODType;
	};
	template<>
	class typeTraits<unsigned long long> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialConstructor;
		typedef trueType isPODType;
	};
	template<>
	class typeTraits<float> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialConstructor;
		typedef trueType isPODType;
	};
	template<>
	class typeTraits<double> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialConstructor;
		typedef trueType isPODType;
	};
	template<>
	class typeTraits<long double> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialConstructor;
		typedef trueType isPODType;
	};
	template<typename T>
	class typeTraits<T*> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialConstructor;
		typedef trueType isPODType;
	};
	template<typename T>
	class typeTraits<const T*> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialConstructor;
		typedef trueType isPODType;
	};
	template<>
	class typeTraits<char*> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialConstructor;
		typedef trueType isPODType;
	};
	template<>
	class typeTraits<unsigned char*> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialConstructor;
		typedef trueType isPODType;
	};
	template<>
	class typeTraits<const char*> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialConstructor;
		typedef trueType isPODType;
	};
	template<>
	class typeTraits<const unsigned char*> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialConstructor;
		typedef trueType isPODType;
	};
}

#endif /* TYPETRAITS_H_ */
