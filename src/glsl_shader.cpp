#include "glsl_shader.h"
#include "debug.h"
#include <sstream>
#include "gl_renderer.h"
#include <glm/gtc/type_ptr.hpp>

GLSL_Shader::GLSL_Shader()
	: Asset( SHADER_ASSET )
{
	memset( shaders, -1, sizeof(GLuint)*3 );
}

GLSL_Shader::~GLSL_Shader()
{
	unload();
}

bool GLSL_Shader::load( const std::string& prefix )
{
	this->filename = prefix;
	name = glCreateProgram();

	if( load_source( VERTEX_SHADER ) )
		glAttachShader( name, shaders[ VERTEX_SHADER ] );
	if( load_source( FRAGMENT_SHADER ) )
		glAttachShader( name, shaders[ FRAGMENT_SHADER ] );
	if( load_source( GEOMETRY_SHADER ) )
		glAttachShader( name, shaders[ GEOMETRY_SHADER ] );

	GL_Renderer::check_error( "Failed to load source files @ " + filename );

	if( !link() )
		return false;
	GL_Renderer::check_error( "Failed to link shaders @ " + filename );

	map_uniform_locations();
	GL_Renderer::check_error( "Failed to map uniform locations of shaders @ " + filename );

	// Shader object is deleted while attached to a program object -> flagged for deletion
	// and deletion will not occur until glDetachShader is called to 
	// detach it from all program objects to which it is attached.
	for( unsigned int i = 0 ; i < 3; ++i )
	{
		if(  shaders[i] != -1 )
			glDetachShader( name, shaders[i] );
	}
	GL_Renderer::check_error( "Failed to detach shaders @ " + filename );
	Debug::report( "GLSL_Shader Asset::load: Shader Program loaded @ " + filename );
	loaded = true;
	return true;
}

bool GLSL_Shader::load_source( Shader_Type type )
{
	GLuint id = 0;

	std::string source_file = filename;
	switch( type )
	{
		case( VERTEX_SHADER ) :
			id = glCreateShader( GL_VERTEX_SHADER );
			source_file += ".vs";
		break;

		case( FRAGMENT_SHADER ) :
			id = glCreateShader( GL_FRAGMENT_SHADER );
			source_file += ".fs";
		break;

		case( GEOMETRY_SHADER ) :
			id = glCreateShader( GL_GEOMETRY_SHADER );
			source_file += ".gs";
		break;
	}

	std::ifstream input( source_file.c_str() );

	if( input.is_open() )
	{
		shaders[type] = id;
		std::string source;
		std::string line = "";

		while( std::getline( input, line ) )
		{
			std::string qualifier, var_type, uniform_name;
			std::stringstream ss;
			ss << line;
			ss >> qualifier;
			if( qualifier == "uniform" )
			{
				ss >> var_type >> uniform_name;
				uniform_name.erase( uniform_name.size() - 1, 1 );
				uniform_loc_map[ uniform_name ] = -1;
			}

			source += "\n" + line;
		}
		input.close();

		const int len = source.length();
		char const * shader_source = source.c_str();
		glShaderSource( id, 1, &shader_source, &len );
		if( compile( id ) )
		{	
			std::stringstream ss;
			ss << (unsigned int)type;
			Debug::report( "GLSL_Shader Asset::load: " + ss.str() + " Shader loaded @ " + filename );
			loaded = true;
			return true;
		}
	}

	Debug::report( "GLSL_Shader::load: Failed to load shader source @ " + source_file );
	return false;
}

bool GLSL_Shader::link()
{
	glLinkProgram( name );

	Debug::report( "GLSL_Shader::link: Linking program" );

	GLint link_test;
	glGetProgramiv( name, GL_LINK_STATUS, &link_test );
	if( link_test == GL_FALSE )
	{
		Debug::error( "GLSL_Shader Asset::load: Shader Program failed to link @ " + filename );
		std::cerr << "---Program Linking Log---\n"
				  << "Filename: " << filename << std::endl;
		GLsizei len = 0;
		GLint size;
		glGetProgramiv( name, GL_INFO_LOG_LENGTH, &size );
		char *info_log = new char[size];
		glGetProgramInfoLog( name, size, &len, info_log );
		std::cerr << info_log;
		return false;
	}
	return true;
}

bool GLSL_Shader::compile( GLuint id )
{
	Debug::report( "GLSL_Shader::compile: Compiling shader" );

	glCompileShader( id );

	GLint compile_test;

	glGetShaderiv( id, GL_COMPILE_STATUS, &compile_test );
	if( compile_test == GL_FALSE )
	{
		std::cerr << "---Shader Failed To Compile---\n"
				  << "Filename: " << filename << std::endl;
		GLsizei len = 0;
		GLint size = 0;
		glGetShaderiv( id, GL_INFO_LOG_LENGTH, &size );
		char *info_log = new char[size];
		glGetShaderInfoLog( id, size, &len, info_log );
		std::cerr << info_log;
		return false;
	}
	return true;
}

void GLSL_Shader::set_int( const std::string& uniform_name, int value) const
{
	glUniform1i( uniform_loc_map.find( uniform_name )->second, value );
}

void GLSL_Shader::set_float( const std::string& uniform_name, float value) const
{
	glUniform1f( uniform_loc_map.find( uniform_name )->second, value );
}

void GLSL_Shader::set_vec2( const std::string& uniform_name, const glm::vec2& value) const
{
	glUniform2fv( uniform_loc_map.find( uniform_name )->second, 1, glm::value_ptr(value) );
}

void GLSL_Shader::set_vec3( const std::string& uniform_name, const glm::vec3& value) const
{
	glUniform3fv( uniform_loc_map.find( uniform_name )->second, 1, glm::value_ptr(value) );
}

void GLSL_Shader::set_vec4( const std::string& uniform_name, const glm::vec4& value) const
{
	glUniform4fv( uniform_loc_map.find( uniform_name )->second, 1, glm::value_ptr(value) );
}

void GLSL_Shader::set_mat3( const std::string& uniform_name, const glm::mat3& value) const
{
	glUniformMatrix3fv( uniform_loc_map.find( uniform_name )->second, 1, GL_FALSE, glm::value_ptr(value) );
}

void GLSL_Shader::set_mat4( const std::string& uniform_name, const glm::mat4& value) const
{
	glUniformMatrix4fv( uniform_loc_map.find( uniform_name )->second, 1, GL_FALSE, glm::value_ptr(value) );
}

const unsigned int GLSL_Shader::get_name() const
{
	return name;
}

void GLSL_Shader::map_uniform_locations()
{
	std::map< std::string, GLint >::iterator it;
	GLint loc;
	std::cout << "Uniforms needed to map data exist:\n";
	for( it = uniform_loc_map.begin(); it != uniform_loc_map.end(); ++it )
	{
		loc = glGetUniformLocation( name, (*it).first.c_str() );
		uniform_loc_map[ (*it).first.c_str() ] = loc;
		std::cout << (*it).first.c_str() << std::endl;
	}
}

bool GLSL_Shader::reload()
{
	if( filename.length() > 0 )
	{
		unload();
		return load( filename );
	}
	Debug::error( "GLSL_Shader::reload: No filename found for this shader asset." );
	return false;
}

void GLSL_Shader::unload()
{
	if( name != 0 )
	{
		for( unsigned int i = 0 ; i < 3; ++i )
		{
			if(  shaders[i] != -1 )
				glDetachShader( name, shaders[i] );
		}
		glDeleteProgram( name );
		name = 0;
	}
}