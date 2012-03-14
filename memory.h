////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Standard templates library. Freestanding implementation.
// Created by Carmelo J. Fernández-Agüera Tortosa, a.k.a. Technik
// On March 4th, 2012
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _RTL_MEMORY_H_
#define _RTL_MEMORY_H_

#include <cstddef>
#include <new>
#include <numeric>

namespace rtl
{
	template <class Alloc>
	struct allocator_traits
	{
		typedef Alloc								allocator_type;
		typedef typename Alloc::value_type			value_type;
		typedef typename Alloc::pointer				pointer;
		typedef typename Alloc::const_pointer		const_pointer;
		typedef typename Alloc::void_pointer		void_pointer;
		typedef typename Alloc::const_void_pointer	const_void_pointer;

		typedef typename Alloc::difference_type		difference_type;
		typedef typename Alloc::size_type			size_type;

		static pointer allocate(Alloc& a, size_type n) { return a.allocate(n); }
		static pointer allocate(Alloc& a, size_type n, const_void_pointer hint) { return a.allocate(n,hint); }

		static void deallocate(Alloc& a, pointer p, size_type n) { a.deallocate(p, n); }
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
		typedef void*		void_pointer;
		typedef const void*	const_void_pointer;

		allocator();
		allocator(const allocator&);
		~allocator();

		pointer			address		(reference x) const;
		const_pointer	address		(const_reference) const;

		pointer			allocate	(size_type, const void * hint = 0);
		void			deallocate	(pointer p, size_type n);
		size_type		max_size	() const;

		void			construct	(pointer _p, const_reference _x = T());
		void			destroy		(pointer _p );
	};

	//------------------------------------------------------------------------
	template<class T>
	allocator<T>::allocator()
	{
	}

	//------------------------------------------------------------------------
	template<class T>
	allocator<T>::allocator(const allocator<T>&)
	{
	}

	//------------------------------------------------------------------------
	template<class T>
	allocator<T>::~allocator()
	{
	}

	//------------------------------------------------------------------------
	template<class T>
	typename allocator<T>::pointer allocator<T>::address(typename allocator<T>::reference x) const
	{
		return &x; // Return the address of x
	}

	//------------------------------------------------------------------------
	template<class T>
	typename allocator<T>::const_pointer allocator<T>::address(typename allocator<T>::const_reference x) const
	{
		return &x; // Return the address of x
	}

	//------------------------------------------------------------------------
	template<class T>
	typename allocator<T>::pointer allocator<T>::allocate(typename allocator<T>::size_type size, const void * hint)
	{
		hint; // Unused variable
		return reinterpret_cast<pointer>(new char[size * sizeof(T)]);
	}

	//------------------------------------------------------------------------
	template<class T>
	void allocator<T>::deallocate(typename allocator<T>::pointer p, typename allocator<T>::size_type n)
	{
		n;	// Unused variable
		delete[] reinterpret_cast<char*>(p);
	}

	//------------------------------------------------------------------------
	template<class T>
	typename allocator<T>::size_type allocator<T>::max_size() const
	{
		return (1024 * 1024 * 1024 * 4)/sizeof(size_type); // TODO: Find a nicer way and/or implement real per-platform limits
	}

	//------------------------------------------------------------------------
	template<class T>
	void allocator<T>::construct( typename allocator<T>::pointer _pAllocatedMemory
								, typename allocator<T>::const_reference _argument)
	{
		new (_pAllocatedMemory)T(_argument); // Placement new of T
	}

	//------------------------------------------------------------------------
	template<class T>
	void allocator<T>::destroy(typename allocator<T>::pointer _object)
	{
		_object->~T(); // Call object's destructor, but do not deallocate memory
	}
}	// namespace rtl

#endif // _RTL_MEMORY_H_
