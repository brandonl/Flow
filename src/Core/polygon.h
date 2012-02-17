#ifndef __POLYGON_H__
#define __POLYGON_H__

#include <vector>
#include <glm/glm.hpp>
#include "Vertex.h"

class Polygon
{
	public:
		Polygon();
		~Polygon();

		void add( Vertex vertex );
		void add( float x, float y, float z, float u, float v, float normx, float normy, float normz, const Color& col = Color() );
		void add( float x, float y, float z, const Color& col );

		glm::vec3										normal() const;
		const std::vector<Vertex>&	vertices() const;

	private:
		std::vector< Vertex > vertices_;
		glm::vec3 normal_;
};

#endif