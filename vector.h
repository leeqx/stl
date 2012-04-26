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

		allocator_type get_allocator() const { return mAlloc; }

	public:
		// Iterators
		iterator		begin	();
		const_iterator	begin	() const;
		iterator		end		();
		const_iterator	end		() const;

		// Size and capacity
		size_type		size	() const		{ return mSize; }
		size_type		max_size() const		{ return mAlloc.max_size; }
		void			resize	(size_type n);
		void			resize	(size_type n, const T& x);
		size_type		capacity() const		{return mCapacity; }
		bool			empty	() const		{ return 0 == mSize; }
		void			reserve	(size_type n)	{ if(n>mCapacity) reallocate(n); }
		void			shrink_to_fit()			{ if(mSize != mCapacity) reallocate(mSize); }

		// Element access
		reference		operator[]	(size_type n)		{ return mData[n]; }
		const_reference operator[]	(size_type n) const { return mData[n]; }
		const_reference at			(size_type n) const { return mData[n]; }
		reference		at			(size_type n)		{ return mData[n]; }
		reference		front		()			{ return *mData; }
		const_reference	front		() const	{ return *mData; }
		reference		back		()			{ return mData[mSize-1]; }
		const_reference	back		() const	{ return mData[mSize-1]; }

		// Data access
		T*				data		()			{ return mData; }
		const T*		data		() const	{ return mData; }

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
			const_iterator				()	// default constructor
				: mData(0) {}
			const_iterator				(pointer x)
				: mData(const_cast<T*>(x)) {}
			const_iterator				(const const_iterator& x)	// Copy constructor
				:mData(x.mData) {}
			const_iterator& operator=	(const const_iterator& x)	// Assignment operator
			{ mData = x.mData; }
			~const_iterator				() {}

			// Basic iterator requirements
			reference		operator*	() const { return *mData; }
			const_iterator&	operator++	()		 { mData++; return *this; }

			// Input iterator requirements
			bool			operator==	(const const_iterator& x) const	// Equality comparison
				 { return mData == x.mData;}
			pointer			operator->	() const { return mData;  }
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

		protected:
			T* mData;
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
			
			// Construction, copy and destruction
			iterator				()	// default constructor
				: typename const_iterator(0) {}
			iterator				(pointer x)
				: typename const_iterator(x) {}
			iterator				(const iterator& x)	// Copy constructor
				: typename const_iterator(x) {}
			iterator& operator=		(const iterator& x)	// Assignment operator
			{	mData = x.mData; }
			~iterator				() {}

			// Basic iterator requirements
			iterator&	operator++	() { ++mData; return *this; }
			
			// Input iterator requirements
			iterator	operator++	(int) { ++mData; return *this; }
			
			// Output iterator requirements
			reference	operator*	() const { return *mData; }
			pointer		operator->	() const { return mData;  }

			// bidirectional iterator requirements
			iterator&	operator--	() { --mData; return *this; }
			iterator	operator--	(int) { +--Data; return *this; }

			// Random access iterator requirements
			iterator&	operator+=	(difference_type n);
			iterator&	operator-=	(difference_type n);
			iterator	operator+	(difference_type n);
			iterator	operator-	(difference_type n);

			reference	operator[]	(difference_type n);

			bool		operator<	(const iterator& );
		};

		private:
			size_type	mSize;
			size_type	mCapacity;
			T*			mData;
			allocatorT	mAlloc;

	private:
		void reallocate( size_type n );
	};

	// Specialized algorithms
	template<class T, class allocatorT>
	void swap(vector<T,allocatorT>& a, vector<T,allocatorT>& b)
	{
		a.swap(b);
	}

	// ---- Vector definition ----------------------------------------------------------------------------------------
	template<class T, class allocatorT>
	vector<T,allocatorT>::vector(const allocatorT& _alloc)
		:mSize(0)
		,mCapacity(0)
		,mData(0)
		,mAlloc(_alloc)
	{
	}

	//-----------------------------------------------------------------------
	template<class T, class allocatorT>
	vector<T,allocatorT>::vector(typename vector<T,allocatorT>::size_type n)
		:mSize(0)
		,mCapacity(0)
		,mData(0)
	{
		resize(n);
	}

	//-----------------------------------------------------------------------
	template<class T, class allocatorT>
	vector<T, allocatorT>::vector(typename vector<T,allocatorT>::size_type n,
		const T& x, const allocatorT& alloc)
		:mSize(0)
		,mCapacity(0)
		,mData(0)
		,mAlloc(alloc)
	{
		resize(n, x);
	}

	//-----------------------------------------------------------------------
	template<class T, class allocatorT>
	vector<T, allocatorT>::vector(const vector<T,allocatorT>& _x)
		:mSize(0)
		,mCapacity(0)
		,mData(0)
		,mAlloc(_x.mAlloc)
	{
		reserve(_x.mSize);
		for(unsigned i = 0; i < mCapacity; ++i)
			push_back(_x[i]);
	}

	//-----------------------------------------------------------------------
	template<class T, class allocatorT>
	vector<T,allocatorT>& vector<T,allocatorT>::operator=(const vector<T,allocatorT>& x)
	{
		clear();	// Delete previous content
		if(x.mSize > mCapacity)
			reallocate(x.mSize);
		mSize = x.mSize;
		for(size_type i = 0; i < mSize; ++i)
		{
			mAlloc.construct(&mData[i], x[i]);
		}
		return *this;
	}

	//-----------------------------------------------------------------------
	template<class T, class allocatorT>
	vector<T, allocatorT>::~vector()
	{
		resize(0);
		allocator_traits<allocatorT>::deallocate(mAlloc, mData, mCapacity);
	}

	//-----------------------------------------------------------------------
	template<class T, class allocatorT>
	typename vector<T, allocatorT>::iterator vector<T,allocatorT>::begin()
	{
		return iterator(mData);
	}

	//-----------------------------------------------------------------------
	template<class T, class allocatorT>
	typename vector<T, allocatorT>::const_iterator vector<T,allocatorT>::begin() const
	{
		return const_iterator(mData);
	}

	//-----------------------------------------------------------------------
	template<class T, class allocatorT>
	typename vector<T, allocatorT>::iterator vector<T,allocatorT>::end()
	{
		return iterator(mData?&mData[mSize]:0);
	}

	//-----------------------------------------------------------------------
	template<class T, class allocatorT>
	typename vector<T, allocatorT>::const_iterator vector<T,allocatorT>::end() const
	{
		return const_iterator(mData?&mData[mSize]:0);
	}

	//-----------------------------------------------------------------------
	template<class T, class allocatorT>
	void vector<T, allocatorT>::resize(typename vector<T,allocatorT>::size_type n)
	{
		if(n > mCapacity)
		{
			reallocate(n);
		}
		while(n > mSize)
			mAlloc.construct(&mData[mSize++]);
		while(n < mSize)
			mAlloc.destroy(&mData[--mSize]);
	}

	//-----------------------------------------------------------------------
	template<class T, class allocatorT>
	void vector<T, allocatorT>::resize(typename vector<T,allocatorT>::size_type n, const T& x)
	{
		if(n > mCapacity)
		{
			reallocate(n);
		}
		while(n > mSize)
			mAlloc.construct(&mData[mSize++], x);
		while(n < mSize)
			mAlloc.destroy(&mData[--mSize]);
	}

	//-----------------------------------------------------------------------
	template<class T, class allocatorT>
	void vector<T, allocatorT>::reallocate(size_type n)
	{
		T* temp_buffer = allocator_traits<allocatorT>::allocate(mAlloc, n);
		for(size_type i = 0; i < n, i < mSize; ++i)
		{
			mAlloc.construct(&temp_buffer[i], mData[i]);
		}
		if(0 != mCapacity)
			allocator_traits<allocatorT>::deallocate(mAlloc, mData, mCapacity);
		mData = temp_buffer;
		mCapacity = n;
		mSize = n<mSize?n:mSize;
	}

	//-----------------------------------------------------------------------
	template<class T, class allocatorT>
	void vector<T, allocatorT>::clear()
	{
		resize(0);
	}

	//-----------------------------------------------------------------------
	template<class T, class allocatorT>
	void vector<T, allocatorT>::push_back(const T& x)
	{
		if(mSize == mCapacity)
		{
			if(0 == mCapacity)
				reallocate(2);
			else
				reallocate(mCapacity*2);
		}
		mAlloc.construct(&mData[mSize++], x);
	}

	//-----------------------------------------------------------------------
	template<class T, class allocatorT>
	void vector<T, allocatorT>::pop_back()
	{
		mAlloc.destroy(&mData[--mSize]);
	}

	//-----------------------------------------------------------------------
	template<class T, class allocatorT>
	typename vector<T,allocatorT>::iterator vector<T, allocatorT>::erase(typename vector<T,allocatorT>::const_iterator x)
	{
		T* aux = const_cast<T*>(&*x);
		while(aux < &mData[mSize-1])
		{
			*aux = *(aux+1);
			++aux;
		}
		mAlloc.destroy(&mData[--mSize]); // Destroy last element and decrease size
		return iterator(const_cast<T*>(&*x));
	}

}	// namespace rtl

#endif // _RTL_VECTOR_H_