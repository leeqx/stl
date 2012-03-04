////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Standard templates library. Freestanding implementation.
// Created by Carmelo J. Fernández-Agüera Tortosa, a.k.a. Technik
// On March 3rd, 2012
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _STL_UTILITY_H_
#define _STL_UTILITY_H_

namespace std
{
	// TODO: Operators
	// Inequality operator
	template<class T>
	inline bool operator != (const T& a, const T& b)
	{
		return ! (a == b);
	}
	// bigger than comparison
	template<class T>
	inline bool operator > ( const T& a, const T& b)
	{
		return b < a;
	}
	// lessOrEqualThan comparison
	template<class T>
	inline bool operator <= (const T& a, const T& b)
	{
		return ! (b < a);
	}
	// moreOrEqualThan comparison
	template<class T>
	inline bool operator >= (const T& a, const T& b)
	{
		return !(a < b);
	}
	// TODO: General utilities
	// Swap
	template <class T>
	inline void swap(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	}

	// ----- Pair declaration -------------
	template < class T1, class T2 >
	struct pair
	{
		typedef T1	first_type;
		typedef T2	second_type;

		T1 first;
		T2 second;

		pair(const T1&, const T2&);

		pair& operator=(const pair&);

		void swap(pair&);
	}

	// ----- Pair implementation ------------
	template < class T1, class T2 >
	inline pair<T1, T2>::pair(const T1& a, const T2& b)
		:first(a)
		,second(b)
	{}

	template < class T1, class T2 >
	pair<T1,T2>::operator=(const pair<T1,T2>& p)
	{
		first = p.first;
		second = p.second;
	}

	template < class T1, class T2 >
	void pair<T1,T2>::swap(pair& p)
	{
		swap(first, p.first);
		swap(second, p.second);
	}

	// ----------- specialized algorithms -------------
	template < class T1, class T2 >
	bool operator == (const pair<T1,T2>& a, const pair<T1,T2>& b)
	{
		return a.first == b.first && a.second == b.second;
	}

	template < class T1, class T2 >
	bool operator < (const pair<T1,T2>& a, const pair<T1,T2>& b)
	{
		return a.first < b.first && a.second < b.second;
	}

	template < class T1, class T2 >
	void swap ( pair<T1,T2>& a, pair<T1,T2>& b )
	{
		a.swap(b);
	}
}	// namespace std

#endif // _STL_UTILITY_H_