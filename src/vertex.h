#ifndef __VERTEX_H__
#define __VERTEX_H__

#include "color.h"

class Vertex
{
	public:
		void print() const;

		Vertex();
		Vertex( float x, float y, float z, const Color& col = Color() );
		Vertex( float x, float y, float z, float u, float v, float normx, float normy, float normz, const Color& col = Color() );
		Vertex( float *vertices, float *tex_coords, float *color  );

		// Uses a threshold to approximate equality since dealign with floating point types.
		bool operator ==( const Vertex& lhs ) const;

		float	position[3];
		float	color	[4];
		float	tex0	[2];
		float	normal[3];
		float	tex1	[2];
		float	tex2	[2];
};

inline bool Vertex::operator ==( const Vertex& lhs ) const
{
	return (	( fabs( this->position[0]	- lhs.position[0] ) < 0.00001f ) &&
				( fabs( this->position[1]	- lhs.position[1] ) < 0.00001f ) && 
				( fabs( this->position[2]	- lhs.position[2] ) < 0.00001f ) && 
				( fabs( this->normal[0]		- lhs.normal[0] )	< 0.00001f ) && 
				( fabs( this->normal[1]		- lhs.normal[1] )	< 0.00001f ) && 
				( fabs( this->normal[2]		- lhs.normal[2] )	< 0.00001f ) && 
				( fabs( this->tex0[0]		- lhs.tex0[0] )		< 0.00001f ) && 
				( fabs( this->tex0[1]		- lhs.tex0[1] )		< 0.00001f ) && 
				( fabs( this->tex1[0]		- lhs.tex1[0] )		< 0.00001f ) && 
				( fabs( this->tex1[1]		- lhs.tex1[1] )		< 0.00001f ) && 
				( fabs( this->tex2[0]		- lhs.tex2[0] )		< 0.00001f ) && 
				( fabs( this->tex2[1]		- lhs.tex2[1] )		< 0.00001f ) );
}

#endif