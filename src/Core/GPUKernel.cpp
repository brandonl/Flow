#include "GPUKernel.h"

using namespace flow;

GPUKernel::GPUKernel( const std::string &fn, ShaderType type )
	: name(glCreateShader( type )), source( fn )
{
	const GLchar* src = source.referencedData().c_str();
	GLint len			= source.referencedData().length();
	glShaderSource( name, 1, &src, &len );

	if( !compile() )
		printf( "Failed to compile shader from source %s\n", fn.c_str() );
}

bool GPUKernel::compile()
{
	glCompileShader( name );

	GLint compile_test = 0;

	glGetShaderiv( name, GL_COMPILE_STATUS, &compile_test );
	if( compile_test == GL_FALSE )
	{
		printf( "### GPUKernel Failed To Compile ###\nFilename: %s.\n", source.getFileName() );
		GLsizei len = 0;
		GLint size = 0;
		glGetShaderiv( name, GL_INFO_LOG_LENGTH, &size );

		char *infoLog = new char[size];
		glGetShaderInfoLog( name, size, &len, infoLog );

		printf( "Info Log:\n %s.\n", infoLog );

		delete [] infoLog;
		return false;
	}
	return true;
}