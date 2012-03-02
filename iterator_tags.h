////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Standard templates library. Freestanding implementation.
// Created by Carmelo J. Fernández-Agüera Tortosa, a.k.a. Technik
// On March 2nd, 2012
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _STL_ITERATOR_TAGS_H_
#define _STL_ITERATOR_TAGS_H_

namespace std
{
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag: public input_iterator_tag { };
	struct bidirectional_iterator_tag: public forward_iterator_tag { };
	struct random_access_iterator_tag: public bidirectional_iterator_tag { };
}	// namespace std

#endif // _STL_ITERATOR_TAGS_H_
