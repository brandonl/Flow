#ifndef __MESH_H__
#define __MESH_H__

#include <GL/glew.h>
#include "Polygon.h"

class Mesh
{
	public:
		typedef std::vector<Vertex>	VertexContainer;

		Mesh();
		~Mesh();

		void add( const Polygon& poly );
		const VertexContainer&	vertices() const;
		const unsigned					vertexCount() const;
		void vertices( const VertexContainer& v );
		void reset();

	private:
		VertexContainer	vertices_;
}; 

inline void Mesh::vertices( const VertexContainer& v )
{
	vertices_ = v;
}
inline const std::vector<Vertex>& Mesh::vertices() const
{
	return vertices_;
}

inline const unsigned int Mesh::vertexCount() const
{
	return vertices_.size();
}

inline void Mesh::reset()
{
	// Completely clear the containers. See GOTW #54
	VertexContainer().swap( vertices_ );
}

#endif