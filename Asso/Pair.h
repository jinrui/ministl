/*
 * Pair.h
 *
 *  Created on: 2015年11月26日
 *      Author: jinrui
 */

#ifndef ASSO_PAIR_H_
#define ASSO_PAIR_H_
template<typename T1,typename T2>
struct Pair{
	T1 first;
	T2 second;
	Pair():first(T1()),second(T2()){}
	Pair(const T1& a,const T2& b):first(a),second(b){}
	Pair (const Pair& other):first(other.first),second(other.second){}
	inline bool operator == (const Pair& rhs){
		return first == rhs.first && second == rhs.second;
	}
	inline bool operator <(const Pair& rhs){
		return first < rhs.first || (first == rhs.first && second < rhs.second);
	}
	Pair& operator = (const Pair& other){
		swap(Pair(other));
		return *this;
	}
	void swap(const Pair& other){
		std::swap(other.first,first);
		std::swap(other.second,second);
	}
};
template<typename T1,typename T2>
inline  Pair<T1,T2> makePair(const T1& x, const T2& y){
	return Pair<T1,T2>(x,y);
}

#endif /* ASSO_PAIR_H_ */
