////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Standard templates library. Freestanding implementation.
// Created by Carmelo J. Fernández-Agüera Tortosa, a.k.a. Technik
// On March 30th, 2012
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Dictionary

#include <iterator_tags.h>
#include <memory.h>
#include <utility.h>

namespace rtl
{
	template<class T, unsigned NBuckets,class allocatorT = rtl::allocator<T>>
	class dictionary
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

		typedef rtl::pair<const char*, T>		slotT;
		typedef rtl::vector<slotT,allocatorT>	bucketT;

	public:
		dictionary(const allocatorT& _alloc = allocator<T>());
		template<unsigned nb>
		dictionary(const dictionary<T,nb,Allocator>&);
		template<unsigned nb>
		dictionary& operator=(const dictionary<T,nb,Allocator>&);
		~dictionary() {}

		allocator_type get_allocator() const { return mAlloc; }

	public:
		// Size and
		size_type		size		() const		{ return mSize; }
		size_type		max_size	() const		{ return mAlloc.max_size; }
		bool			empty		() const		{ 0 == mSize; }

		T&				find		(const char * _key);
		T&				operator	(const char * _key);
		bool			contains	(const char * _key);

	private:
		static unsigned					hash	(const char * _key);
		static bool						keycomp	(const char * _a, const char * _b);

	private:
		size_type			mSize;
		allocatorT			mAlloc;
		bucketT[NBuckets]	mBuckets;
	};

	//------------------------------------------------------------------------------------------------------------------
	// Dictionary implementation
	//------------------------------------------------------------------------------------------------------------------
	template<class T, unsigned NB, class allocatoTr>
	dictionary<T,NB,allocatorT>::dictionary(const allocatorT& _alloc)
		:mSize(0)
		,mAlloc(_alloc)
	{
	}

	//------------------------------------------------------------------------------------------------------------------
	template<class T, unsigned nb1, class allocator, unsigned nb2>
	dictionary<T,nb1,allocatorT>::dictionary(const dictionary<T,nb2,allocatorT>& x)
		:mSize(0)
		,mAlloc(x.mAlloc)
	{
		for(unsinged i = 0; i < nb2; ++i)
		{
			unsigned bucketSize = x.mBuckets[i].size();
			for(unsigned j = 0; j < bucketSize; ++j)
			{
				pair<const char*,T>& slot = x.mBuckets[i][j];
				operator[](slot.first) = slot.second;
			}
		}
	}

	//------------------------------------------------------------------------------------------------------------------
	template<class T, unsigned nb1, class allocatorT, unsigned nb2>
	dictionary<T,nb1,allocatorT>& dictionary<T,nb1,allocatorT>::operator=(const dictionary<T,nb2,allocatorT>& x)
		:mSize(0)
		,mAlloc(x.mAlloc)
	{
		for(unsinged i = 0; i < nb2; ++i)
		{
			unsigned bucketSize = x.mBuckets[i].size();
			for(unsigned j = 0; j < bucketSize; ++j)
			{
				pair<const char*,T>& slot = x.mBuckets[i][j];
				operator[](slot.first) = slot.second;
			}
		}
		return *this;
	}

	//------------------------------------------------------------------------------------------------------------------
	template<class T, unsigned nb1, class allocatorT>
	T& dictionary<T,nb1,allocatorT>::find(const char * _key)
	{
		unsigned bucketId = hash(_key);
		bucketT& bucket = mBuckets[bucketId];
		for (bucketT::iterator i = 0; i != bucket.end(); ++i)
		{
			if(keyComp(iterator->first,_key))
			{
				return iterator->second;
			}
		}
		// Found nothing, create a new entry
		// Create a new slot
		// Push it into the bucket
	}
}	// namespace rtl
