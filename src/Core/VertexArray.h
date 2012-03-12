#ifndef VERTEX_ARRAY_H__
#define VERTEX_ARARY_H__

#include <GL3/gl3w.h>
#include "Utils.h"

namespace flow
{
	class VertexArray : private Uncopyable
	{
	public:
		VertexArray() : name(0) {}
		~VertexArray()
		{
			glDeleteVertexArrays( 1, &name );
		}

		void alloc();
		void bind();
		void unbind();

	private:
		GLuint name;
	};

	inline void VertexArray::alloc()
	{	
		glGenVertexArrays( 1, &name );
		glBindVertexArray( name );
	}

	inline void VertexArray::bind()
	{
		glBindVertexArray( name );
	}

	inline void VertexArray::unbind()
	{
		glBindVertexArray( 0 );
	}
};

#endif