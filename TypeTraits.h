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
	struct typeTraits {
		typedef falseType hasTrivialDefaultConstructor;
		typedef falseType hasTrivialCopyConstructor;
		typedef falseType hasTrivialAssignmentConstructor;
		typedef falseType hasTrivialDestructor;
		typedef falseType isPODType;
	};
//各种特化
	template<>
	struct typeTraits<bool> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialDestructor;
		typedef trueType isPODType;
	};
	template<>
	struct typeTraits<char> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialDestructor;
		typedef trueType isPODType;
	};
	template<>
	struct typeTraits<unsigned char> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialDestructor;
		typedef trueType isPODType;
	};
	template<>
	struct typeTraits<short> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialDestructor;
		typedef trueType isPODType;
	};
	template<>
	struct typeTraits<unsigned short> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialDestructor;
		typedef trueType isPODType;
	};
	template<>
	struct typeTraits<int> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialDestructor;
		typedef trueType isPODType;
	};
	template<>
	struct typeTraits<unsigned int> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialDestructor;
		typedef trueType isPODType;
	};
	template<>
	struct typeTraits<long> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialDestructor;
		typedef trueType isPODType;
	};
	template<>
	struct typeTraits<unsigned long> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialDestructor;
		typedef trueType isPODType;
	};
	template<>
	struct typeTraits<long long> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialDestructor;
		typedef trueType isPODType;
	};
	template<>
	struct typeTraits<unsigned long long> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialDestructor;
		typedef trueType isPODType;
	};
	template<>
	struct typeTraits<float> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialDestructor;
		typedef trueType isPODType;
	};
	template<>
	struct typeTraits<double> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialDestructor;
		typedef trueType isPODType;
	};
	template<>
	struct typeTraits<long double> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialDestructor;
		typedef trueType isPODType;
	};
	template<typename T>
	struct typeTraits<T*> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialDestructor;
		typedef trueType isPODType;
	};
	template<typename T>
	struct typeTraits<const T*> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialDestructor;
		typedef trueType isPODType;
	};
	template<>
	struct typeTraits<char*> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialDestructor;
		typedef trueType isPODType;
	};
	template<>
	struct typeTraits<unsigned char*> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialDestructor;
		typedef trueType isPODType;
	};
	template<>
	struct typeTraits<const char*> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialDestructor;
		typedef trueType isPODType;
	};
	template<>
	struct typeTraits<const unsigned char*> {
		typedef trueType hasTrivialDefaultConstructor;
		typedef trueType hasTrivialCopyConstructor;
		typedef trueType hasTrivialAssignmentConstructor;
		typedef trueType hasTrivialDestructor;
		typedef trueType isPODType;
	};
}

#endif /* TYPETRAITS_H_ */
