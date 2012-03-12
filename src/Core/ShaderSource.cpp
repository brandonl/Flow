#include "ShaderSource.h"
#include <GL3/gl3w.h>
#include <cstdio>
#include <sstream>
#include <fstream>

using namespace flow;

ShaderSource::ShaderSource( const std::string& fn )
	:	Resource( fn )
{
	std::ifstream input( fn.c_str() );
	if( input.is_open() )
	{
		std::stringstream buffer;
		buffer << input.rdbuf();
		input.close();
		source = buffer.str();

		if( !source.length())
			printf( "Shader source file (%s) does not appear to be valid; expect errors.\n", fn.c_str() );
	}
	else
		printf( "Failed to load shader source: %s\n", fn.c_str() );
}

ShaderSource& ShaderSource::operator=( ShaderSource&& m )
{
	source.swap( std::move( m.source ) );
	return *this;
}