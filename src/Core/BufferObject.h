#ifndef __BUFFER_OBJECT_H__
#define __BUFER_OBJECT_H__

#include <GL3/gl3w.h>
#include "Vertex.h"
#include "Utils.h"

namespace flow
{
	class BufferObject : private Uncopyable
	{
	public:
		explicit BufferObject( GLenum tar, GLenum usage = GL_STATIC_DRAW )
			:	name(0),
				target(tar),
				usage(usage),
				mem_size(0)
		{}
		~BufferObject()
		{
			glBindBuffer( target, 0 );
			glDeleteBuffers( 1, &name );
		}


		template <class T>
		void alloc( const T &vs );

		template <class T>
		void update( const T &vs );

		void bind();
		void unbind();

		operator GLuint() const;

	private:
		GLuint name;
		GLenum target;
		GLenum usage;
		unsigned int mem_size;
	};

	inline void BufferObject::bind()
	{ 
		glBindBuffer( target, name ); 
	}

	inline void BufferObject::unbind()
	{ 
		glBindBuffer( target, 0 ); 
	}

	inline BufferObject::operator GLuint() const
	{ 
		return name; 
	}

	template <class T>
	inline void BufferObject::alloc( const T &cdata )
	{
		mem_size = cdata.size();
		glGenBuffers( 1, &name );
		bind();
		glBufferData( target, mem_size * sizeof T::value_type, &cdata[0], usage );
	}

	template <class T>
	inline void BufferObject::update( const T &cdata )
	{
		bind();
		glBufferData( target, cdata	.size() * sizeof T::value_type, &cdata[0], usage );
	}
};

#endif