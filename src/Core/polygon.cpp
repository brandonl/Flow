#include "Polygon.h"

Polygon::Polygon()
{
}

Polygon::~Polygon()
{
}

void Polygon::add( Vertex vertex )
{
	vertices_.push_back( vertex );
}

void Polygon::add( float x, float y, float z, float u, float v, float normx, float normy, float normz, const Color& col )
{
	add( Vertex( x, y, z, u, v, normx, normy, normz, col ) );
}

void Polygon::add( float x, float y, float z, const Color& col )
{
	add( Vertex( x, y, z, col ) );
}

const std::vector<Vertex>& Polygon::vertices() const
{
	return vertices_;
}

glm::vec3 Polygon::normal() const
{
	glm::vec3 a( vertices_[0].position[0], vertices_[0].position[1], vertices_[0].position[2] );
	glm::vec3 b( vertices_[1].position[0], vertices_[1].position[1], vertices_[1].position[2] );
	glm::vec3 c( vertices_[2].position[0], vertices_[2].position[1], vertices_[2].position[2] );
	return glm::normalize( glm::cross( c - a,  b - a ) );
}