////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Standard templates library. Freestanding implementation.
// Created by Carmelo J. Fernández-Agüera Tortosa, a.k.a. Technik
// On March 2nd, 2012
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _RTL_ITERATOR_H_
#define _RTL_ITERATOR_H_

#include <cassert>
#include <crtldef>

#include <iterator_tags.h>
#include <iterator_traits.h>

namespace rtl
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

	// ----- Operations on iterators ------
	// Advance
	template< class InputIterator, class Distance>
		void advance ( InputIterator& i, Distance n )
		{
			if(typename iterator_traits<InputIterator>::iterator_category == random_access_iterator_tag)
			{
				i = i+n;
			}
			else
			{
				if(typename iterator_traits<InputIterator>::iterator_category != bidirectional_iterator_tag)
				{
					assert(n >= 0);
					for(Distance d = 0; d < n; ++d)
						++i;
				}
				else
				{
					if(n >= 0)
					{
						for(Distance d = 0; d < n; ++d)
							++i;
					}
					else
					{
						for(Distance d = 0; d > n; --d)
							--i;
					}
				}
			}
		}

	// Distance
	template< class InputIterator >
	typename iterator_traits<InputIterator>::difference_type
		distance( InputIterator& first, InputIterator& last )
	{
		if(typename rtl::iterator_traits<InputIterator>::iterator_category == rtl::random_access_iterator_tag)
		{
			return last - first;
		}
		else
		{
			typename rtl::iterator_traits<InputIterator>::difference_type d = 0;
			InputIterator i = first;
			while(i != last)
			{
				++d;
				++i;
			}
			return d;
		}
	}

	// Next
	template < class ForwardIterator >
	ForwardIterator next ( ForwardIterator& i,
		typename rtl::iterator_traits<ForwardIterator>::difference_type n )
	{
		advance( i , n );
		return i;
	}

	// Prev
	template < class BidirectionalIterator >
	BidirectionalIterator prev ( BidirectionalIterator& i,
		typename rtl::iterator_traits<BidirectionalIterator>::difference_type n )
	{
		advance( i, -n );
		return i;
	}

	// ----- Iterator adaptators -----
	// TODO: Reverse iterator
	// TODO: Insert iterator
	// TODO: Move iterator

	// ----- Iterator streams -----
	// TODO: all


}	// namespace rtl

#endif // _RTL_ITERATOR_H_
