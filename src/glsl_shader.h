#ifndef __GLSL_SHADER_H_
#define __GLSL_SHADER_H_

#include <GL/glew.h>
#include "asset.h"
#include <fstream>
#include <iostream>
#include <map>
#include <glm/glm.hpp>

class GLSL_Shader : public Asset
{
	public:
		enum Shader_Type
		{
			VERTEX_SHADER = 0,
			FRAGMENT_SHADER,
			GEOMETRY_SHADER
		};

		GLSL_Shader();
		~GLSL_Shader();

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

	protected:
		// Access by Asset_Manager, whom is a friend of Asset base type
		bool load_source( Shader_Type type );
		bool link();
		void map_uniform_locations();
		bool compile( GLuint id );
		bool reload();
		void unload();

	private:
		GLuint name;
		GLuint shaders[3];
		std::map< std::string, GLint > uniform_loc_map;
};

#endif