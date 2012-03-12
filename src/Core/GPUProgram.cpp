#include "GPUProgram.h"

using namespace flow;

void GPUProgram::load( const std::string &vkfn, const std::string &fkfn, const std::string &gkfn )
{
	name = glCreateProgram();
	kernels.reserve(2);

	if( vkfn.size() )
		kernels.emplace_back( GPUKernel( vkfn, GPUKernel::VERTEX_KERNEL ) );
	if( fkfn.size() )
		kernels.emplace_back( GPUKernel( fkfn, GPUKernel::FRAGMENT_KERNEL ) );
	if( gkfn.size() )
		kernels.emplace_back( GPUKernel( gkfn, GPUKernel::GEOMETRY_KERNEL ) );

	attachKernels();
	if( linkKernels() )
	{
		// Shader object is deleted while attached to a program object -> flagged for deletion
		// and deletion will not occur until glDetachShader is called to 
		// detach it from all program objects to which it is attached.
		for( auto it = kernels.cbegin(); it != kernels.cend(); ++it )
				glDetachShader( name, it->getGLName() );
	}
}

GPUProgram::~GPUProgram()
{
	if( name != 0 )
	{
		for( auto it = kernels.cbegin(); it != kernels.cend(); ++it )
				glDetachShader( name, it->getGLName() );

		glDeleteProgram( name );
		name = 0;
	}
}

void GPUProgram::attachKernels()
{
	for( auto it = kernels.cbegin(); it != kernels.cend(); ++it )
	{
		glAttachShader( name, it->getGLName() );
		glDeleteShader( it->getGLName() );
	}
}

bool GPUProgram::linkKernels()
{
	glLinkProgram( name );

	GLint link_test;
	glGetProgramiv( name, GL_LINK_STATUS, &link_test );

	if( link_test == GL_FALSE )
	{
		printf( "GPUProgram failed to link.\n### Program Linking Log ###\n" );
		GLsizei len = 0;
		GLint size = 0;
		glGetProgramiv( name, GL_INFO_LOG_LENGTH, &size );

		char *infoLog = new char[size];
		glGetProgramInfoLog( name, size, &len, infoLog );

		printf( "Info Log:\n %s.\n", infoLog );
		delete infoLog;

		return false;
	}

	return true;
}
