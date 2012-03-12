#include "Mesh.h"
#include <algorithm>
#include <iterator>

using namespace flow;

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

void Mesh::add( const Plane& poly )
{
	const std::vector<Vertex> pverts = poly.vertices();
	std::copy( pverts.cbegin(), pverts.cend(), std::back_inserter( vertices_ ) );
}