#ifndef __MESH_H__
#define __MESH_H__

#include <GL/glew.h>
#include "polygon.h"

class Mesh
{
	public:
		typedef std::vector<Vertex>					Vertex_Container;
		typedef std::vector<unsigned short> Index_Container;

		enum Mesh_Type
		{
			TRI_MESH = GL_TRIANGLES,
			TRI_FAN_MESH = GL_TRIANGLE_FAN,
			TRI_STRIP_MESH = GL_TRIANGLE_STRIP,
			LINE_MESH = GL_LINES,
			LINE_STRIP_MESH = GL_LINE_STRIP,
			LINE_LOOP_MESH = GL_LINE_LOOP,
			POINT_MESH = GL_POINTS
		};

		enum Poly_Mode
		{
			FILL = GL_FILL,
			POINTS = GL_POINT,
			LINES = GL_LINE
		};

		Mesh( Mesh_Type type = TRI_MESH );
		~Mesh();
		void			add_poly( const Polygon& poly );

		//-----------------------------------------------------------
		// Accesors
		/////////////////////////////////////////////////////////////
		const Vertex_Container&	get_vertices() const;
		const unsigned					get_vertex_count() const;
		const Index_Container&	get_indexes() const;
		const unsigned 					get_index_count() const;

		const unsigned 					get_max_index() const;
		const unsigned 					get_min_index() const;

		//-----------------------------------------------------------
		// Modifiers
		/////////////////////////////////////////////////////////////
		void				reset();

		//-----------------------------------------------------------
		// Public Member Vars
		/////////////////////////////////////////////////////////////
		Mesh_Type			mesh_type;
		Poly_Mode			poly_mode;
		bool					is_indexed;

	private:
		unsigned 						max_index;
		unsigned 						min_index;

		Vertex_Container	vertices;
		Index_Container		indexes;
}; 

#endif