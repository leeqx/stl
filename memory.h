////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Standard templates library. Freestanding implementation.
// Created by Carmelo J. Fernández-Agüera Tortosa, a.k.a. Technik
// On March 4th, 2012
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _STL_MEMORY_H_
#define _STL_MEMORY_H_

#include <cstddef>

namespace std
{
	template <class Alloc>
	struct allocator_traits
	{
		typedef Alloc						allocator_type;
		typedef Alloc::value_type			value_type;
		typedef Alloc::pointer				pointer;
		typedef Alloc::const_pointer		const_pointer;
		typedef Alloc::void_pointer			void_pointer;
		typedef Alloc::const_void_pointer	const_void_pointer;

		typedef Alloc::difference_type		difference_type;
		typedef Alloc::size_type			size_type;

		static pointer allocate(Alloc& a, size_type n);
		static pointer allocate(Alloc& a, size_type n, const_void_pointer hint);

		static void deallocate(Alloc& a, pointer p, size_type n);
	};
	
	// TODO: Define allocator_traits and finish its declaration

	// ---------------- Default allocator ---------------
	template < class T >
	class allocator
	{
	public:
		typedef size_t		size_type;
		typedef ptrdiff_t	difference_type;
		typedef T*			pointer;
		typedef const T*	const_pointer;
		typedef T&			reference;
		typedef const T&	const_reference;
		typedef T			value_type;

		allocator();
		allocator(const allocator&);
		~allocator();

		pointer			address		(reference x) const;
		const_pointer	address		(const_reference) const;

		pointer			allocate	(size_type, const void * hint = 0);
		size_type		max_size	() const;

		void			construct	( _T* _p, const _T& _x );
		void			destroy		( _T* _p );
	};
}	// namespace std

#endif // _STL_MEMORY_H_
