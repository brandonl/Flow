#ifndef LEXICAL_CAST_H__
#define LEXICAL_CAST_H__

#include <sstream>
#include "Debug.h"

template <class Tar, class Src>
Tar lexicalCast( Src arg )
{
	std::stringstream interpreter;
	Tar res;
	if( !(interpreter << arg) || !(interpreter >> res) || !(interpreter >> std::ws).eof() )
		debug() << "Throw Bad Cast Exception\n";
	return res;
}

#endif