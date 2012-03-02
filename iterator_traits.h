////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Standard templates library. Freestanding implementation.
// Created by Carmelo J. Fernández-Agüera Tortosa, a.k.a. Technik
// On March 2nd, 2012
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _STL_ITERATOR_TRAITS_H_
#define _STL_ITERATOR_TRAITS_H_

#include <cstddef>

#include <iterator_tags.h>

namespace std
{	
	template< class _t >
	struct iterator_traits
	{
		typedef typename _t::value_type			value_type;
		typedef typename _t::difference_type	difference_type;
		typedef typename _t::pointer			pointer;
		typedef typename _t::reference			reference;
		typedef typename _t::iterator_category	iterator_category;
	};

	// iterator_traits specialization for pointers
	template< class _t >
	struct iterator_traits<_t*>
	{
		typedef _t							value_type;
		typedef ptrdiff_t					difference_type;
		typedef _t*							pointer;
		typedef _t&							reference;
		typedef bidirectional_iterator_tag	iterator_category;
	};
}	// namespace std

#endif // _STL_ITERATOR_TRAITS_H_
