#define WIN32_LEAN_AND_MEAN   // This trims down the libraries.
#define VC_LEANMEAN           // Trims even farther.
#include <GL/glew.h>

#include "input.h"
#include "window.h"

#include "scene.h"
#include "debug.h"
#include "app.h"

#include "mesh.h"
#include "shapes.h"
#include "camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "buffer_object.h"
#include "shader.h"
#include "matrix_stack.h"

using namespace std;
using namespace glm;

namespace
{
	GLDEBUGPROCARB debug_callback( GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, GLvoid *user_param )
	{
		std::string src_name;
		switch(source)
		{
			case GL_DEBUG_SOURCE_API_ARB: src_name = "API"; break;
			case GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB: src_name = "Window System"; break;
			case GL_DEBUG_SOURCE_SHADER_COMPILER_ARB: src_name = "Shader Compiler"; break;
			case GL_DEBUG_SOURCE_THIRD_PARTY_ARB: src_name = "Third Party"; break;
			case GL_DEBUG_SOURCE_APPLICATION_ARB: src_name = "Application"; break;
			case GL_DEBUG_SOURCE_OTHER_ARB: src_name = "Other"; break;
		}

		std::string error_type;
		switch(type)
		{
			case GL_DEBUG_TYPE_ERROR_ARB: error_type = "Error"; break;
			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB: error_type = "Deprecated Functionality"; break;
			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB: error_type = "Undefined Behavior"; break;
			case GL_DEBUG_TYPE_PORTABILITY_ARB: error_type = "Portability"; break;
			case GL_DEBUG_TYPE_PERFORMANCE_ARB: error_type = "Performance"; break;
			case GL_DEBUG_TYPE_OTHER_ARB: error_type = "Other"; break;
		}

		std::string type_severity;
		switch(severity)
		{
			case GL_DEBUG_SEVERITY_HIGH_ARB: type_severity = "High"; break;
			case GL_DEBUG_SEVERITY_MEDIUM_ARB: type_severity = "Medium"; break;
			case GL_DEBUG_SEVERITY_LOW_ARB: type_severity = "Low"; break;
		}

		debug() << error_type << " from , priority\nMessage: " << message << endl;
		exit(2);
	}

	void init_main()
	{
		if( glDebugMessageCallbackARB )
		{
			glEnable( GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB );
			glDebugMessageControlARB( GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, 0, GL_TRUE );
			glDebugMessageCallbackARB( (GLDEBUGPROCARB)debug_callback, 0 );
		}
		//----------------------------------------------
		// Initialize GL Extension Wrangler
		////////////////////////////////////////////////
		glewExperimental = GL_TRUE;
		GLenum err = glewInit();
		if( GLEW_OK != err ) 
		debug() << "GLEW Error: Failed to initialize GLEW." << endl;

		//------------------------------------------------------------
		// Prepare GL context.
		///////////////////////////////////////////////////////////////
		glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
		glClearColor( 0.4f, 0.4f, 0.4f, 1.0f );
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		// Accept fragment if it closer to the camera than the former one
		//glDepthFunc(GL_LESS); 
		//glEnable(GL_CULL_FACE);
	}

};

GLuint loadTGA_glfw(const char * imagepath){

	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glActiveTexture( GL_TEXTURE0 );
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Read the file, call glTexImage2D with the right parameters
	glfwLoadTexture2D(imagepath, 0);

	// Nice trilinear filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
	glGenerateMipmap(GL_TEXTURE_2D);

	// Return the ID of the texture we just created
	return textureID;
}

class Grey : public Scene
{
public:
	Grey() : Scene()  
	{
	}

	~Grey()
	{
		glUseProgram(0);
		glBindTexture( GL_TEXTURE_2D, 0 );
		glBindVertexArray( vao );
		for( unsigned int i = 0; i <= Shader::ATTRIBUTE_TEX2; ++i )
			glDisableVertexAttribArray( i );
		glBindVertexArray(0);
		glDeleteVertexArrays( 1, &vao );
	}

	void init()
	{
		debug() << "Started scene" << endl;

		p.modify( perspective( 35.0f, 
														static_cast<float>( Window::get_width() ) / Window::get_height(), 
														0.1f, 100.0f ) );

		cam.set(	vec3( 0.0f, 0.5f, -2.0f ), 
							vec3( 0.0f, 0.5f, 0.0f ), 
							vec3( 0.0f, 1.0f, 0.0f ) );

		shape::build_sphere( 0.2f, 20, 20, obj );
		glGenVertexArrays( 1, &vao );
		glBindVertexArray( vao );
		
		vbo.alloc( obj.get_vertices() );
		ibo.alloc( obj.get_indexes() );
		
		glVertexAttribPointer( Shader::ATTRIBUTE_POS,		3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0 );
		glVertexAttribPointer( Shader::ATTRIBUTE_NORMAL,	3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal) );
		glVertexAttribPointer( Shader::ATTRIBUTE_TEX0,		2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex0) );
		glVertexAttribPointer( Shader::ATTRIBUTE_COLOR,		4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color) );
		// Not used in current shaders.
		glVertexAttribPointer( Shader::ATTRIBUTE_TEX1, 		2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex1 ) );
		glVertexAttribPointer( Shader::ATTRIBUTE_TEX2, 		2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex2 ) );
		for( unsigned int i = 0; i <= Shader::ATTRIBUTE_TEX2; ++i )
			glEnableVertexAttribArray( i );
		
		vbo.unbind();
		ibo.unbind();
		
		//shader.load( "../../content/Shaders/flat" );
		//shader.load( "../../content/Shaders/StandardShading" );
		shader.load( "../../content/Shaders/texture" );

		glActiveTexture( GL_TEXTURE0 );
		glBindTexture(GL_TEXTURE_2D,  loadTGA_glfw( "../../content/Textures/Block.tga" ) );
		
		// Must use a program before setting uniforms otherwise error code 1282
		// Invalid Op
		glUseProgram( shader.get_name() );
		shader.set_int( "tex_unit0", 0 );
	}

	void update()
	{
		mv.set( lookAt( cam.position, cam.focus, cam.up_direction ) );
		cam.update();
	}
	
	void draw()
	{
		glUseProgram( shader.get_name() );
		mv.save();
		shader.set_mat4( "mvp_matrix", p.get_matrix() * mv.get_matrix() );
	
		//shader.set_mat4( "MVP", p.get_matrix() * mv.get_matrix() );
		//shader.set_mat4( "M", mat4(1.0f) );
		//shader.set_mat4( "V", mv.get_matrix() );
		//shader.set_vec3( "LightPosition_worldspace", vec3( 4, 4, 4 ) );

		// Only Array buffer bindings are stored in the VAO implicitly not IBOS
		// Must rebind...We have 1 vao referencing 1 vbo in scene no need to rebind
		ibo.bind();

		glEnable( obj.poly_mode == GL_LINE ? GL_LINE_SMOOTH : GL_POLYGON_SMOOTH );
		glPolygonMode( GL_FRONT_AND_BACK, obj.poly_mode );

		glDrawRangeElements(	obj.mesh_type, 
													obj.get_min_index(), obj.get_max_index(),
													obj.get_index_count(),
													GL_UNSIGNED_SHORT, (const GLvoid*)0 );
		mv.restore();				
	}

private:
	Matrix_Stack mv, p;
	Camera cam;
	Mesh obj;
	Buffer_Object vbo;
	Buffer_Object ibo;
	GLuint vao;
	Shader shader;
};


inline void check_error( const std::string& error_msg )
{
	const GLenum error_val = glGetError();

	if( error_val != GL_NO_ERROR )
	{
		std::stringstream ss;
		ss << error_val;
		debug() << "GL_Renderer::check_error: " << error_msg << " with error code " << ss.str() << endl;
	}
}


int main(int argc, char * argv[])
{
	App app;
	app.init( "T H E g R E Y" );
	check_error( "APP INIT" );

	init_main(); // Context needs to be set up first	
	check_error( "Context + GLEW INIT" );

	Grey *scene = new Grey();
	scene->init();
	check_error( "Scene INIT" );

	app.set( scene );
	app.run();

	delete scene;
	return 0;
}
