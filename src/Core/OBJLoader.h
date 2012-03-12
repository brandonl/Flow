#ifndef OBJ_LOADER__
#define OBJ_LOADER__

#include <string>
#include "Mesh.h"

namespace flow
{
	namespace obj
	{
		void import( const std::string& filename, Mesh &mesh );
	};
};

#endif