////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Standard templates library. Freestanding implementation.
// Created by Carmelo J. Fernández-Agüera Tortosa, a.k.a. Technik
// On March 2nd, 2012
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _STL_ITERATOR_H_
#define _STL_ITERATOR_H_

#include <cstddef>

namespace std
{
	// Generic iterator template class
	template < class Category
		, class T
		, class Distance = ptrdiff_t
		, class Pointer = T*
		, class Reference = T& >
		struct iterator
	{
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

}	// namespace std

#endif // _STL_ITERATOR_H_
