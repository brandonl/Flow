#ifndef __VERTEX_H__
#define __VERTEX_H__

#include "Color.h"
#include <cmath>
#include <array>
#include <GL3/gl3w.h>
#include <vector>

namespace flow
{
	struct Vertex
	{
		Vertex();
		Vertex( float x, float y, float z, const Color& col = Color() );
		Vertex( float x, float y, float z, float u, float v, float normx, float normy, float normz, const Color& col = Color() );
		Vertex( float x, float y, float u, float v, const Color& col = Color() );
		bool operator ==( const Vertex& lhs ) const;

		std::array<GLfloat, 3> position;
		std::array<GLfloat, 2> texCoord;
		std::array<GLfloat, 4> color;
		std::array<GLfloat, 3> normal;
	};

	typedef std::vector<Vertex> VertList;

	inline bool Vertex::operator ==( const Vertex& lhs ) const
	{
		return (	( fabs( this->position[0]	- lhs.position[0] )	< 0.00001f ) &&
					( fabs( this->position[1]	- lhs.position[1] )	< 0.00001f ) && 
					( fabs( this->position[2]	- lhs.position[2] )	< 0.00001f ) && 
					( fabs( this->normal[0]		- lhs.normal[0] )		< 0.00001f ) && 
					( fabs( this->normal[1]		- lhs.normal[1] )		< 0.00001f ) && 
					( fabs( this->normal[2]		- lhs.normal[2] )		< 0.00001f ) && 
					( fabs( this->texCoord[0]	- lhs.texCoord[0] )		< 0.00001f ) && 
					( fabs( this->texCoord[1]	- lhs.texCoord[1] )		< 0.00001f ) );
	}
};

#endif