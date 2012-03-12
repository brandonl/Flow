#include "Vertex.h"
#include <algorithm>

using namespace flow;


// Make sure Vertex size is a multiple of 32
//static_assert( sizeof( Vertex ) % 32 == 0, "Vertex data does not fit on mutliple of 32 bit slot" );

Vertex::Vertex()
{
	position.fill(0.f);
	texCoord.fill(0.f);
	color.fill(0.f);
	normal.fill(0.f);
}

Vertex::Vertex( float x, float y, float z, const Color& col )
{
	position[0] = x;
	position[1] = y;
	position[2] = z;
	memcpy( &color[0], &col, sizeof(Color) );
	texCoord.fill(0.f);
	normal.fill(0.f);
}

Vertex::Vertex( float x, float y, float z, float u, float v, float normx, float normy, float normz, const Color& col )
{
	position[0] = x;
	position[1] = y;
	position[2] = z;
	texCoord[0] = u;
	texCoord[1] = v;
	memcpy( &color[0], &col, sizeof(Color) );
	normal[0] = normx;
	normal[1] = normy;
	normal[2] = normz;
}

