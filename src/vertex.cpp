#include "vertex.h"
#include <cstring>
#include <iostream>


void Vertex::print() const
{
	std::cout << "\tVertices: "; 
	for( int i = 0; i < 3; ++i )
		std::cout << position[i] << ", ";
	//std::cout << std::endl;
	std::cout << "TexCoords0: "; 
	for( int i = 0; i < 2; ++i )
		std::cout << tex0[i] << ", ";
	std::cout << std::endl;
/*	
	std::cout << "Color: "; 
	for( int i = 0; i < 4; ++i )
		std::cout << color[i] << ", ";
	std::cout << std::endl;

	std::cout << "Normal: "; 
	for( int i = 0; i < 3; ++i )
		std::cout << normal[i] << ", ";
	std::cout << std::endl;

	std::cout << "TexCoords0: "; 
	for( int i = 0; i < 2; ++i )
		std::cout << tex0[i] << ", ";
	std::cout << std::endl;

	std::cout << "TexCoords1: "; 
	for( int i = 0; i < 2; ++i )
		std::cout << tex1[i] << ", ";
	std::cout << std::endl;

	std::cout << "TexCoords2: "; 
	for( int i = 0; i < 2; ++i )
		std::cout << tex2[i] << ", ";
	std::cout << std::endl;

	std::cout << "About: \t" << "Offsets: " << offsetof(Vertex, position) << ", " 
		<< offsetof(Vertex, color) << ", " << offsetof(Vertex, normal) << ", "<< offsetof(Vertex, tex0) << ", "
		<< offsetof(Vertex, tex1) << ", " << offsetof(Vertex, tex2) << std::endl;

	std::cout << "Size ofs:\t" << (sizeof(position)/sizeof(float) ) << ", "
		<< (sizeof(color)/sizeof(float) ) << ", "
		<< (sizeof(normal)/sizeof(float) ) << ", "
		<< (sizeof(tex0)/sizeof(float) ) << ", "
		<< (sizeof(tex1)/sizeof(float) ) << ", "
		<< (sizeof(tex2)/sizeof(float) ) <<std::endl;
*/
}

// Make sure Vertex size is a multiple of 32
static_assert( sizeof( Vertex ) % 32 == 0, "Vertex data does not fit on mutliple of 32 bit slot" );

Vertex::Vertex()
{
}

Vertex::Vertex( float x, float y, float z, const Color& col )
{
	position[0] = x;
	position[1] = y;
	position[2] = z;
	memcpy( color, &col, sizeof(Color) );
	tex0[0] = 0.0f;
	tex0[1] = 0.0f;
    memset( normal, 0, sizeof(float)*3 );
    memset( tex1,	0, sizeof(float)*2 );
    memset( tex2,	0, sizeof(float)*2 );
}

Vertex::Vertex( float x, float y, float z, float u, float v, float normx, float normy, float normz, const Color& col )
{
	position[0] = x;
	position[1] = y;
	position[2] = z;
	tex0[0] = u;
	tex0[1] = v;
	memcpy( color, &col, sizeof(Color) );
    normal[0] = normx;
	normal[1] = normy;
	normal[2] = normz;
    memset( tex1,	0, sizeof(float)*2 );
    memset( tex2,	0, sizeof(float)*2 );
}

Vertex::Vertex( float *vertices, float *color, float *tex_coords )
{
	memcpy( position, vertices, sizeof(vertices) );
	memcpy( this->color, color, sizeof(float)*4 );
	memcpy( tex0, tex_coords, sizeof(tex_coords) );
    memset( normal, 0, sizeof(float)*3 );
    memset( tex1,	0, sizeof(float)*2 );
    memset( tex2,	0, sizeof(float)*2 );
}

