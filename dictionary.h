////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Standard templates library. Freestanding implementation.
// Created by Carmelo J. Fernández-Agüera Tortosa, a.k.a. Technik
// On March 30th, 2012
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Dictionary

#include <iterator_tags.h>
#include <memory.h>
#include <utility.h>
#include <vector.h>

namespace rtl
{
	template<class T, unsigned NBuckets, class allocatorT = rtl::allocator<T>>
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

		typedef rtl::pair<char*, T>				slotT;
		typedef rtl::vector<slotT,allocatorT>	bucketT;

	public:
		dictionary(const allocatorT& _alloc = allocatorT());
		dictionary(const dictionary<T,NBuckets,allocatorT>&);
		dictionary& operator=(const dictionary<T,NBuckets,allocatorT>&);
		~dictionary() {}

		allocator_type get_allocator() const { return mAlloc; }

	public:
		// Size and
		size_type		size		() const		{ return mSize; }
		size_type		max_size	() const		{ return mAlloc.max_size; }
		bool			empty		() const		{ 0 == mSize; }

		T&				find		(const char * _key);
		T&				operator[]	(const char * _key);
		bool			contains	(const char * _key);

	private:
		static unsigned					hash	(const char * _key);
		static bool						keyComp	(const char * _a, const char * _b);
		static void						keyCopy	(char *& _dst, const char * _src);

	private:
		size_type	mSize;
		allocatorT	mAlloc;
		bucketT		mBuckets[NBuckets];
	};

	//------------------------------------------------------------------------------------------------------------------
	// Dictionary implementation
	//------------------------------------------------------------------------------------------------------------------
	template<class T, unsigned NB, class allocatorT>
	dictionary<T,NB,allocatorT>::dictionary(const allocatorT& _alloc)
		:mSize(0)
		,mAlloc(_alloc)
	{
	}

	//------------------------------------------------------------------------------------------------------------------
	template<class T, unsigned nb1, class allocatorT>
	dictionary<T,nb1,allocatorT>::dictionary(const dictionary<T,nb1,allocatorT>& x)
		:mSize(0)
		,mAlloc(x.mAlloc)
	{
		for(unsinged i = 0; i < nb1; ++i)
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
	template<class T, unsigned nb1, class allocatorT>
	dictionary<T,nb1,allocatorT>& dictionary<T,nb1,allocatorT>::operator=(const dictionary<T,nb1,allocatorT>& x)
		:mSize(0)
		,mAlloc(x.mAlloc)
	{
		for(unsinged i = 0; i < nb1; ++i)
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
		slotT slot(0,T());
		keyCopy(slot.first, _key);
		// Push it into the bucket
		bucket.push_back(slot);
		return slot.second;
	}

	//------------------------------------------------------------------------------------------------------------------
	template<class T, unsigned nb1, class allocatorT>
	T& dictionary<T,nb1,allocatorT>::operator[](const char * _key)
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
		slotT slot(0,T());
		keyCopy(slot.first, _key);
		// Push it into the bucket
		bucket.push_back(slot);
		return slot.second;
	}

	//------------------------------------------------------------------------------------------------------------------
	template<class T, unsigned nb1, class allocatorT>
	bool dictionary<T,nb1,allocatorT>::contains(const char * _key)
	{
		unsigned bucketId = hash(_key);
		bucketT& bucket = mBuckets[bucketId];
		for (bucketT::iterator i = 0; i != bucket.end(); ++i)
		{
			if(keyComp(iterator->first,_key))
			{
				return true;
			}
		}
		// Found nothing
		return false;
	}

	//------------------------------------------------------------------------------------------------------------------
	template<class T, unsigned nb, class allocatorT>
	unsigned dictionary<T,nb,allocatorT>::hash(const char * _key)
	{
		if(!_key)
			return 0;
		unsigned i = 0;
		unsigned lHash = 0;
		while(_key[i] != '\0')
		{
			lHash += _key[i];
			++i;
		}
		return lHash % nb;
	}

	//------------------------------------------------------------------------------------------------------------------
	template<class T, unsigned nb, class allocatorT>
	bool dictionary<T,nb,allocatorT>::keyComp(const char * _a, const char * _b)
	{
		if (!_a || !_b)
			return false;
		unsigned i = 0;
		while(_a[i] != '\0' && _b[i] != '\0')
		{
			if(_a[i] != _b[i])
				return false;
			++i;
		}
		return _a[i] == _b[i];
	}

	//------------------------------------------------------------------------------------------------------------------
	template<class T, unsigned nb, class allocatorT>
	void dictionary<T,nb,allocatorT>::keyCopy(char *& _dst, const char * _src)
	{
		for(unsigned i = 0; _src[i] != '\0'; ++i)
			;
		_dst = new char[i+1];
		_dst[i] = '\0';
		for(i = 0; _src[i] != '\0'; ++i)
		{
			_dst[i] = _src[i];
		}
	}

}	// namespace rtl
