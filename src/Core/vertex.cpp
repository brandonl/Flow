#include "vertex.h"
#include <cstring>
#include <iostream>

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

