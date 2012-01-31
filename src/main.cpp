#define WIN32_LEAN_AND_MEAN   // This trims down the libraries.
#define VC_LEANMEAN           // Trims even farther.
#include "opening.h"
#include "Core/debug.h"
#include "Core/app.h"

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

		debug() << error_type << " from , priority\nMessage: " << message << std::endl;
		exit(2);
	}

	inline void check_error( const std::string& error_msg )
	{
		const GLenum error_val = glGetError();

		if( error_val != GL_NO_ERROR )
		{
			std::stringstream ss;
			ss << error_val;
			debug() << "GL_Renderer::check_error: " << error_msg << " with error code " << ss.str() << std::endl;
		}
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
		debug() << "GLEW Error: Failed to initialize GLEW." << std::endl;

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


int main(int argc, char * argv[])
{
	App app;
	app.init( "T H E g R E Y", 1024, 768 );
	check_error( "APP INIT" );

	init_main(); // Context needs to be set up first	
	check_error( "Context + GLEW INIT" );

	Opening *scene = new Opening();
	scene->init();
	check_error( "Scene INIT" );

	app.set( scene );
	app.run();

	delete scene;
	return 0;
}
