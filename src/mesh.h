#ifndef __MESH_H__
#define __MESH_H__

#include "polygon.h"
#include <string>
#include <glm/glm.hpp>

// All meshes are indexed unless specified before loading/creating the mesh. 
// Except for primitives which are always indexed regardless of the users choice.
// Trying to change a primitive to non-indexed will result in error in drawing that mesh.

class Mesh
{
	public:
		typedef std::vector<Vertex>					Vertex_Container;
		typedef std::vector<unsigned short> Index_Container;
		typedef std::vector<Polygon>				Face_Container; 

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
		// Non-indexed bounding box; facilitates debugging.
		void			build_bbox( const glm::vec3& min, const glm::vec3& max, const Color& col = Color() );

		//-----------------------------------------------------------
		// Accesors
		/////////////////////////////////////////////////////////////
		const Vertex_Container&	get_vertices() const;
		const unsigned		get_vertex_count() const;
		const Index_Container&	get_indexes() const;
		const unsigned 		get_index_count() const;
		const unsigned 		get_poly_count() const;

		const unsigned 		get_max_index() const;
		const unsigned 		get_min_index() const;

		//-----------------------------------------------------------
		// Modifiers
		/////////////////////////////////////////////////////////////
		static void	set_working_dir( const std::string& directory );
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
		bool								data_is_dirty;
		static std::string	working_directory;

		Face_Container		polys;
		Vertex_Container	vertices;
		Index_Container		indexes;
}; 

#endif