#ifndef __MESH_H__
#define __MESH_H__

#include "polygon.h"
#include <string>
#include <glm/glm.hpp>

// Upon importing or building a poly mesh, the data is transfered to GPU memory.
// Thus the order of data in the GPU is described by the order of mesh creation(not initialization)
// This offers the user the ability to draw all of the meshes contiguously if they desire.
// Drawing seperate meshes at a time is also availble and most used.

// All meshes are indexed unless specified before loading/creating the mesh. 
// Except for primitives which are always indexed regardless of the users choice.
// Trying to change a primitive to non-indexed will result in error in drawing that mesh.

class Mesh
{
	public:
		typedef std::vector<Vertex>			Vertex_Container;
		typedef std::vector<unsigned short> Index_Container;
		typedef std::vector<Polygon>		Face_Container; 

		enum Mesh_Type
		{
			TRI_MESH = 0,
			TRI_FAN_MESH,
			TRI_STRIP_MESH,
			LINE_MESH,
			LINE_STRIP_MESH,
			LINE_LOOP_MESH,
			POINT_MESH
		};

		enum Poly_Mode
		{
			FILL = 0,
			POINTS,
			LINES
		};

		Mesh( Mesh_Type type = TRI_MESH );
		~Mesh();

		/////////////////////////////////////////////////////////////
		void			import_obj( const std::string& filename );
		void			add_poly( const Polygon& poly );
		//-----------------------------------------------------------
		// Primitives
		////////////////////////////////////////////////////////////
		void			build_cube( float radius, const Color& col = Color() );
		void			build_sphere( float radius, int lats, int longs, const Color& col = Color() );
		void			build_torus( float outer_raidus, float inner_radius, int num_major, int num_minor, const Color& col = Color() );
		void			build_cylinder( float base_radius, float top_radius, float length, int longs, int lats, const Color& col = Color() );

		// Non-indexed bounding box; facilitates debugging.
		void			build_bbox( const glm::vec3& min, 
									const glm::vec3& max,
									const Color& col = Color() );
		//-----------------------------------------------------------
		// Accesors
		/////////////////////////////////////////////////////////////
		const Vertex_Container&	get_vertices() const;
		const unsigned int		get_vertex_count() const;

		const Index_Container&	get_indexes() const;
		const unsigned int		get_index_count() const;

		const unsigned int		get_poly_count() const;

		// Availble in public interface to facilitate contiguous drawing.
		const unsigned int		get_vbo_pos() const;
		const unsigned int		get_ibo_pos() const;
		const unsigned int		get_max_index() const;
		const unsigned int		get_min_index() const;
		const unsigned int		get_buffer_particpation() const;

		//-----------------------------------------------------------
		// Modifiers
		/////////////////////////////////////////////////////////////
		void		set_ibo_pos( unsigned int ibo_pos );
		void		set_vbo_pos( unsigned int vbo_pos );
		static void	set_working_dir( const std::string& directory );
		void		set_buffer_particpation( unsigned int buffer_object );
		void		reset_mesh();
		//-----------------------------------------------------------
		// Public Member Vars
		/////////////////////////////////////////////////////////////
		Mesh_Type			mesh_type;
		Poly_Mode			poly_mode;
		bool				is_indexed;
		static std::string	working_directory;

	private:
		unsigned int		buffer_particpation;
		unsigned int		vbo_position;
		unsigned int		ibo_position;
		unsigned int		max_index;
		unsigned int		min_index;
		bool				data_is_dirty;

		Face_Container		polys;
		Vertex_Container	vertices;
		Index_Container		indexes;
}; 

#endif