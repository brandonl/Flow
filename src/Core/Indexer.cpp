#include "Indexer.h"
#include <algorithm>

namespace flow
{
	namespace indexer
	{
		const IndexContainer compute( Mesh& mesh )
		{
			const Mesh::VertexContainer inVerts = mesh.vertices();
			mesh.reset();

			Mesh::VertexContainer outVerts;
			IndexContainer outIndexes;
			// Reserve for the worst case we will shrink to fit at the end....
			outIndexes.reserve( inVerts.size() );
			outVerts.reserve( inVerts.size() );

			for( auto pit = inVerts.cbegin(); pit != inVerts.cend(); ++pit )
			{
				size_t match = 0;
				for( match = 0; match < outVerts.size(); ++match )
				{
					if( outVerts[match] == *pit )
					{
						outIndexes.push_back( match );
						break;
					}
				}

				if( match == outVerts.size() )
				{
					outVerts.push_back( *pit );
					outIndexes.push_back( match );
				}
			}
			// Shrink to fit.
			IndexContainer( outIndexes ).swap( outIndexes );
			Mesh::VertexContainer( outVerts ).swap( outVerts );

			mesh.vertices( outVerts );
			return outIndexes;
		}

		void findMinMax( const IndexContainer& ix, unsigned &min, unsigned &max )
		{
			min = *std::min_element( ix.cbegin(), ix.cend() );
			max = *std::max_element( ix.cbegin(), ix.cend() );
		}
	};
};