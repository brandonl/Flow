#ifndef _SHADER_H_
#define _SHADER_H_

#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <map>
#include <glm/glm.hpp>

class Shader
{
	public:
		enum Shader_Type
		{
			VERTEX_SHADER = 0,
			FRAGMENT_SHADER,
			GEOMETRY_SHADER
		};

		enum Attribute
		{
			ATTRIBUTE_POS = 0,
			ATTRIBUTE_NORMAL,
			ATTRIBUTE_TEX0,
			ATTRIBUTE_COLOR,
			ATTRIBUTE_TEX1,
			ATTRIBUTE_TEX2,
			ATTRIBUTE_UNDEF
		};

		Shader();
		~Shader();

		bool load( const std::string& prefix );

		//----------------------------------------------------------------
		// M u t a t o r s
		///////////////////////////////////////////////////////////////////
		void set_int( const std::string& uniform_name, int value) const;
		void set_float( const std::string& uniform_name, float value) const;
		void set_vec2( const std::string& uniform_name, const glm::vec2& value) const;
		void set_vec3( const std::string& uniform_name, const glm::vec3& value) const;
		void set_vec4( const std::string& uniform_name, const glm::vec4& value) const;
		void set_mat3( const std::string& uniform_name, const glm::mat3& value) const;
		void set_mat4( const std::string& uniform_name, const glm::mat4& value) const;

		//----------------------------------------------------------------
		// A c c e s s o r s
		///////////////////////////////////////////////////////////////////
		const unsigned int get_name() const;

	private:
		bool load_source( Shader_Type type );
		bool link();
		bool compile( GLuint id );
		void map_uniform_locations();
		void unload();

		std::string filename;
		GLuint name;
		GLuint shaders[3];
		std::map< std::string, GLint > uniform_loc_map;
};

#endif