////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Standard templates library. Freestanding implementation.
// Created by Carmelo J. Fernández-Agüera Tortosa, a.k.a. Technik
// On March 15th, 2012
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _RTL_UTILITY_OPERATORS_H_
#define _RTL_UTILITY_OPERATORS_H_

namespace rtl
{
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
}	// namespace rtl

#endif // _RTL_UTILITY_OPERATORS_H_