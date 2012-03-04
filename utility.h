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
	bool operator != (const T& a, const T& b)
	{
		return ! (a == b);
	}
	// -------- Inequality comparison -----------
	template<class T>
	bool operator > ( const T& a, const T& b)
	{
		return b < a;
	}
	// TODO: General utilities
	// Swap
	template <class T>
	void swap(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	}

	// ----- Pair -------------
	template < class T1, class T2 >
	struct pair
	{
		typedef T1	first_type;
		typedef T2	second_type;

		T1 first;
		T2 second;

		constexpr pair();
		pair(const T1&, const T2&);

		pair& operator=(const pair& x);

		void swap(pair& p);
	}
}	// namespace std

#endif // _STL_UTILITY_H_