#ifndef PRIM_SHAPES_H__
#define PRIM_SHAPES_H__

#include "Color.h"
#include "Mesh.h"

namespace flow
{
	namespace shape
	{
		//-------------------------------------------------------------------
		// Primitives code based off of source code from OpenGL SuperBible 5ed.
		/////////////////////////////////////////////////////////////////////
		void build_cube( float r, Mesh &mesh, const Color& col = Color() );

		void build_sphere( float r, int lats, int longs, Mesh &mesh, const Color& col = Color() );

		void build_torus( float outer_radius, float inner_radius, int num_major, int num_minor, Mesh &mesh, const Color& col = Color() );

		void build_bbox( const glm::vec3& min, const glm::vec3& max, Mesh &mesh, const Color& col = Color() );
	};
};

#endif