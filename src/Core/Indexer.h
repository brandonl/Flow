#ifndef INDEXER_H__
#define INDEXER_H__

#include "Mesh.h"
#include <vector>

namespace flow
{
	namespace indexer
	{
		typedef std::vector<unsigned short> IndexContainer;

		const IndexContainer compute( Mesh& mesh );
		void findMinMax( const IndexContainer& ix, unsigned &min, unsigned &max );
	};
};

#endif