#include "polygon.h"

Polygon::Polygon()
{
}

Polygon::~Polygon()
{
}

void Polygon::add_vertex( Vertex vertex )
{
	add_vertex(		vertex.position[0], vertex.position[1], vertex.position[2],
					vertex.tex0[0], vertex.tex0[1],
					vertex.position[0], vertex.normal[1], vertex.normal[2],
					Color() );
}

void Polygon::add_vertex( float x, float y, float z, float u, float v, float normx, float normy, float normz, const Color& col )
{
	this->vertices.push_back( Vertex( x, y, z, u, v, normx, normy, normz, col ) );
}

void Polygon::add_vertex( float x, float y, float z, float u, float v )
{
	vertices.push_back( Vertex( x, y, z, u, v, 0, 0, 0, Color() ) );
}

void Polygon::add_vertex( float x, float y, float z, const Color& col )
{
	this->vertices.push_back( Vertex( x, y, z, col ) );
}

void Polygon::set_normal( const glm::vec3& norm )
{
	normal = norm;
}

std::vector<Vertex> Polygon::get_vertices() const
{
	return vertices;
}

glm::vec3 Polygon::calculate_normal() const
{
	glm::vec3 a( vertices[0].position[0], vertices[0].position[1], vertices[0].position[2] );
	glm::vec3 b( vertices[1].position[0], vertices[1].position[1], vertices[1].position[2] );
	glm::vec3 c( vertices[2].position[0], vertices[2].position[1], vertices[2].position[2] );
	return glm::normalize( glm::cross( c - a,  b - a ) );
}

glm::vec3 Polygon::get_normal() const
{
	return normal;
}