#include "mesh.h"
#include "debug.h"
#include <string>
#include <fstream>
#include <algorithm>
#include <iterator>

Mesh::Mesh( Mesh_Type mtype )
	:	mesh_type(mtype),
		poly_mode(FILL),
		is_indexed(false),
		max_index(0),
		min_index(4294967295)
{
}

Mesh::~Mesh()
{
}

void Mesh::add_poly( const Polygon& poly )
{
	std::vector<Vertex> pverts = poly.get_vertices();

	if( is_indexed )
	{
		for( auto pit = pverts.cbegin(); pit != pverts.cend(); ++pit )
		{
			size_t match = 0;
			for( match = 0; match < vertices.size(); ++match )
			{
				// Overload == operator
				if( vertices[match] == *pit )
				{
					min_index = ( match < min_index ) ? match : min_index;
					max_index = ( match > max_index ) ? match : max_index;
					indexes.push_back( match );
					break;
				}
			}

			if( match == vertices.size() )
			{
				vertices.push_back( *pit );
				indexes.push_back( match );
			}
		}
	}

	else // Not indexed
		std::copy( pverts.begin(), pverts.end(), std::back_inserter( vertices ) );
}

/////////////////////////////////////////////////////////////////////

const std::vector<Vertex>& Mesh::get_vertices() const
{
	return vertices;
}

const unsigned int Mesh::get_vertex_count() const
{
	return vertices.size();
}

const std::vector<unsigned short>& Mesh::get_indexes() const
{
	return indexes;
}

const unsigned int Mesh::get_index_count() const
{
	return indexes.size();
}

const unsigned int Mesh::get_max_index() const
{
	return max_index;
}

const unsigned int Mesh::get_min_index() const
{
	return min_index;
}

/////////////////////////////////////////////////////////////////////

void Mesh::reset()
{
	// Completely clear the containers. See GOTW #54
	Vertex_Container().swap( vertices );
	Index_Container().swap( indexes );
}