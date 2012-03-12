#ifndef __GPU_PROGRAM_H__
#define __GPU_PROGRAM_H__

#include <GL3/gl3w.h>
#include "GPUKernel.h"
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace flow
{
	class GPUProgram
	{
		public:
			enum Attribute
			{
				ATTRIBUTE_POS = 0,
				ATTRIBUTE_TEXCOORD,
				ATTRIBUTE_COLOR,
				ATTRIBUTE_NORMAL,
				ATTRIBUTE_UNDEF
			};

		public:
			GPUProgram() : name(0) {}
			~GPUProgram();

			void load( const std::string &vkfn, const std::string &fkfn, const std::string &gkfn = "" );
			// Pass false as use param to unbind/unset program (use program 0 ).
			void use( bool douse = true ) const;
			void uniform1i( const char* uniformName, int value) const;
			void uniform1f( const char* uniformName, float value) const;
			void uniform2v( const char* uniformName, const glm::vec2& value) const;
			void uniform3v( const char* uniformName, const glm::vec3& value) const;
			void uniform4v( const char* uniformName, const glm::vec4& value) const;
			void uniform3m( const char* uniformName, const glm::mat3& value) const;
			void uniform4m( const char* uniformName, const glm::mat4& value) const;

		private:
			void attachKernels();
			bool linkKernels();

		private:
			GLuint name;
			std::vector<GPUKernel> kernels;
	};

	inline void GPUProgram::use( bool douse ) const
	{
		glUseProgram( ( douse ? name : 0 ) );
	}

	inline void GPUProgram::uniform1i( const char* uniformName, int value) const
	{
		GLint loc = glGetUniformLocation( name, uniformName );
		glUniform1i( loc, value );
	}

	inline void GPUProgram::uniform1f( const char* uniformName, float value) const
	{
		GLint loc = glGetUniformLocation( name, uniformName );
		glUniform1f( loc, value );
	}

	inline void GPUProgram::uniform2v( const char* uniformName, const glm::vec2& value) const
	{
		GLint loc = glGetUniformLocation( name, uniformName );
		glUniform2fv( loc, 1, glm::value_ptr(value) );
	}

	inline void GPUProgram::uniform3v( const char* uniformName, const glm::vec3& value) const
	{
		GLint loc = glGetUniformLocation( name, uniformName );
		glUniform3fv( loc, 1, glm::value_ptr(value) );
	}

	inline void GPUProgram::uniform4v( const char* uniformName, const glm::vec4& value) const
	{
		GLint loc = glGetUniformLocation( name, uniformName );
		glUniform4fv( loc, 1, glm::value_ptr(value) );
	}

	inline void GPUProgram::uniform3m( const char* uniformName, const glm::mat3& value) const
	{
		GLint loc = glGetUniformLocation( name, uniformName );
		glUniformMatrix3fv( loc, 1, GL_FALSE, glm::value_ptr(value) );
	}

	inline void GPUProgram::uniform4m( const char* uniformName, const glm::mat4& value) const
	{
		GLint loc = glGetUniformLocation( name, uniformName );
		glUniformMatrix4fv( loc, 1, GL_FALSE, glm::value_ptr(value) );
	}
};

#endif