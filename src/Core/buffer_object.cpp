#include "buffer_object.h"

Buffer_Object::Buffer_Object()
	:	name(0),
		mem_size(0)
{
}

Buffer_Object::~Buffer_Object()
{
	glBindBuffer( target, 0 );
	glDeleteBuffers( 1, &name );
}

void Buffer_Object::alloc( const std::vector< Vertex > &verts )
{
	target = GL_ARRAY_BUFFER;
	mem_size = verts.size();
	glGenBuffers( 1, &name );
	bind();
	glBufferData( target, mem_size * sizeof Vertex, &verts[0], GL_STATIC_DRAW );
}


void Buffer_Object::alloc( const std::vector< GLushort > &indexes )
{
	target = GL_ELEMENT_ARRAY_BUFFER;
	mem_size = indexes.size();
	glGenBuffers( 1, &name );
	bind();
	glBufferData( target, mem_size * sizeof( GLushort ), &indexes[0], GL_STATIC_DRAW );
}
