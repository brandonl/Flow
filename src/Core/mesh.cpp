#include "Mesh.h"
#include <algorithm>
#include <iterator>

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

void Mesh::add( const Polygon& poly )
{
	const std::vector<Vertex> pverts = poly.vertices();
	std::copy( pverts.cbegin(), pverts.cend(), std::back_inserter( vertices_ ) );
}