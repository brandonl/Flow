//#define WIN32_LEAN_AND_MEAN   // This trims down the libraries. Gl3w wanted to do this
#define VC_LEANMEAN           // Trims even farther.
#include "Opening.h"
#include <GL3/gl3w.h>

namespace
{
	inline void checkError( const std::string& errorMsg )
	{
		const GLenum errorVal = glGetError();

		if( errorVal != GL_NO_ERROR )
		{
			std::stringstream ss;
			ss << errorVal;
			printf( "GL_Renderer::checkError: %s with error code %s.\n", errorMsg.c_str(), ss.str().c_str() );
		}
	}
	
	void initMain()
	{
		//-----------------------------------------------------------
		// Initialize GL3W
		/////////////////////////////////////////////////////////////
      if (gl3wInit())
               fprintf(stderr, "failed to initialize OpenGL\n");

      if (!gl3wIsSupported(3, 2))
               fprintf(stderr, "OpenGL 3.2 not supported\n");
      printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION),
               glGetString(GL_SHADING_LANGUAGE_VERSION));

		//------------------------------------------------------------
		// Prepare GL context.
		///////////////////////////////////////////////////////////////
		glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
		glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
		glClearColor( 0.7f, 0.7f, 0.7f, 1.0f );
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
	Opening app;
	initMain(); // Context needs to be set up first	
	checkError( "Context + GLEW INIT" );
	app.init();
	checkError( "APP INIT" );

	app.run();

	return 0;
}
