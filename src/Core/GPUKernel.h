#ifndef __GPU_KERNEL_H__
#define __GPU_KERNEL_H__

#include <string>
#include "ShaderRef.h"
#include <GL3/gl3w.h>

namespace flow
{
	class GPUProgram;

	class GPUKernel
	{
		friend class GPUProgram;
		private:
			enum ShaderType {
				VERTEX_KERNEL =  GL_VERTEX_SHADER,
				FRAGMENT_KERNEL =  GL_FRAGMENT_SHADER,
				GEOMETRY_KERNEL =  GL_GEOMETRY_SHADER
			};

			// Usage: for creating shader references persistant between objects.
			//GPUKernel( const ShaderRef &sr );
			GPUKernel( const std::string &fn, ShaderType type );
			const GLuint getGLName() const;

		private:
			bool compile();

		private:
			GLuint name;
			ShaderRef source;
	};

	inline const GLuint GPUKernel::getGLName() const
	{
		return name;
	}
};

#endif