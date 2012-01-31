#ifndef __BUFFER_OBJECT_H__
#define __BUFER_OBJECT_H__

#include <GL/glew.h> 
#include "vertex.h"
#include <vector>

class Buffer_Object
{
	public:
		explicit Buffer_Object();
		~Buffer_Object();

		void alloc( const std::vector< Vertex > &vs );
		void alloc( const std::vector< GLushort > &is );

		void bind()
		{ glBindBuffer( target, name ); }

		void unbind()
		{ glBindBuffer( target, 0 ); }

		operator GLuint() const
		{ return name; }

		GLuint name;
		GLenum target;
		unsigned int mem_size;
};

#endif