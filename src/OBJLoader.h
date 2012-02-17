#ifndef OBJ_LOADER__
#define OBJ_LOADER__

#include <string>
#include "Core/Mesh.h"

namespace obj
{
	void import( const std::string& filename, Mesh &mesh );
};

#endif