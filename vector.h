////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Standard templates library. Freestanding implementation.
// Created by Carmelo J. Fernández-Agüera Tortosa, a.k.a. Technik
// On March 7th, 2012
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _RTL_VECTOR_H_
#define _RTL_VECTOR_H_

#include <iterator_tags.h>
#include <memory.h>
#include <utility.h>

namespace rtl
{
	template < class T, class allocatorT = rtl::allocator<T> >
	class vector
	{
	public:
		// Public types
		typedef T				value_type;
		typedef T&				reference;
		typedef const T&		const_reference;
		typedef T*				pointer;
		typedef const T*		const_pointer;
		typedef	allocatorT		allocator_type;

		typedef	typename rtl::allocator_traits<allocatorT>::size_type		size_type;
		typedef typename rtl::allocator_traits<allocatorT>::difference_type	difference_type;
		
		class const_iterator;
		class iterator;

	public:
		// Construction, destruction and copy
		explicit	vector	(const allocatorT& = allocatorT());	// Default constructor
		explicit	vector	(size_type n);
		vector	(size_type n, const T& x, const allocatorT& alloc = allocatorT());
		vector	(const vector<T,allocatorT>& x);	// Copy constructor
		~vector	();	// Destructor
		vector<T,allocatorT>& operator=(const vector<T,allocatorT>& x);

		allocator_type get_allocator() const;

	public:
		// Iterators
		iterator		begin	();
		const_iterator	begin	() const;
		iterator		end		();
		const_iterator	end		() const;

		// Capacity
		size_type		size	() const;
		size_type		max_size() const;
		void			resize	(size_type n);
		void			resize	(size_type n, const T& x);
		size_type		capacity() const;
		bool			empty	() const;
		void			reserve	(size_type n);
		void			shrink_to_fit();

		// Element access
		reference		operator[]	(size_type n);
		const_reference operator[]	(size_type n) const;
		const_reference at			(size_type n) const;
		reference		at			(size_type n);
		reference		front		();
		const_reference	front		() const;
		reference		back		();
		const_reference	back		() const;

		// Data access
		T*				data		();
		const T*		data		() const;

		// Modifiers
		void			push_back	(const T&);
		void			pop_back	();
		iterator		insert		(const_iterator position, const T& x);
		iterator		insert		(const_iterator position, size_type n, const T& x);
		template<class InputIterator>
		iterator		insert		(const_iterator position,
									InputIterator first, InputIterator last);
		iterator		erase		(const_iterator position);
		iterator		erase		(const iterator first, const iterator last);
		void			swap		(vector<T,allocatorT>&);
		void			clear		();

		// Operators
		bool			operator==	(const vector<T,allocatorT>&) const;
		bool			operator<	(const vector<T,allocatorT>&) const;

	public:
		// ---- Nested classes ----
		class const_iterator
		{
		public:
			// Types
			typedef T			value_type;
			typedef const T*	pointer;
			typedef const T&	reference;
			typedef typename rtl::allocator_traits<allocatorT>::difference_type	difference_type;
			typedef random_access_iterator_tag	iterator_category;

			// Construction, copy and destruction
			const_iterator				();	// default constructor
			const_iterator				(const const_iterator&);	// Copy constructor
			const_iterator& operator=	(const const_iterator&);	// Assignment operator
			~const_iterator				();

			// Basic iterator requirements
			reference		operator*	() const;
			const_iterator&	operator++	();

			// Input iterator requirements
			bool			operator==	(const const_iterator&) const;	// Equality comparison
			pointer			operator->	() const;
			const_iterator	operator++	(int);

			// bidirectional iterator requirements
			const_iterator&	operator--	();
			const_iterator	operator--	(int);

			// Random access iterator requirements
			const_iterator& operator+=	(difference_type n);
			const_iterator& operator-=	(difference_type n);
			const_iterator	operator+	(difference_type n);
			const_iterator	operator-	(difference_type n);

			reference		operator[]	(difference_type n);

			bool			operator<	(const const_iterator& );
		};

		class iterator : public const_iterator
		{
		public:
			// Types
			typedef T			value_type;
			typedef T*	pointer;
			typedef T&	reference;
			typedef typename rtl::allocator_traits<allocatorT>::difference_type	difference_type;
			typedef random_access_iterator_tag	iterator_category;

			// Basic iterator requirements
			iterator&	operator++	();
			
			// Input iterator requirements
			iterator	operator++	(int);
			
			// Output iterator requirements
			reference	operator*	() const;
			pointer		operator->	() const;

			// bidirectional iterator requirements
			iterator&	operator--	();
			iterator	operator--	(int);

			// Random access iterator requirements
			iterator&	operator+=	(difference_type n);
			iterator&	operator-=	(difference_type n);
			iterator	operator+	(difference_type n);
			iterator	operator-	(difference_type n);

			reference	operator[]	(difference_type n);

			bool		operator<	(const iterator& );
		};
	};

	// Specialized algorithms
	template<class T, class allocatorT>
	void swap(vector<T,allocatorT>& a, vector<T,allocatorT>& b)
	{
		a.swap(b);
	}
}	// namespace rtl

#endif // _RTL_VECTOR_H_