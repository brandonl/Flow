#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <string>
#include <iostream>

namespace Debug
{
	inline std::ostream& debug()
	{
		return std::cout;
	}
};

using namespace Debug;

#endif
