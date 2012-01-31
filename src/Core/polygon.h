#ifndef __POLYGON_H__
#define __POLYGON_H__

#include "vertex.h"
#include <vector>
#include <glm/glm.hpp>

class Polygon
{
	public:
		Polygon();
		~Polygon();

		/////////////////////////////////////////////////////////////
		void			add_vertex( Vertex vertex );
		void			add_vertex( float x, float y, float z, float u, float v, 
													float normx, float normy, float normz, const Color& col = Color() );
		void			add_vertex( float x, float y, float z, float u, float v );
		void			add_vertex( float x, float y, float z, const Color& col );

		glm::vec3		calculate_normal() const;

		void				set_normal( const glm::vec3& norm );

		std::vector<Vertex>	get_vertices() const;
		glm::vec3						get_normal() const;
		Vertex							get_vertex( unsigned int index ) const;



	private:
		std::vector< Vertex > vertices;
		glm::vec3 normal;
};

#endif