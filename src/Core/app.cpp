#include "App.h"
#include "Utils.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;
using namespace flow;

const float App::DELTA_TIME = 1.0f/60.0f;

App::App( const std::string &name, int width, int height )
	:	window( name, width, height )
{
}

void App::baseInit()
{
	input.init();

	p.modify(	perspective( 35.0f, 
					static_cast<float>( window.getWidth() ) / window.getHeight(), 
					0.1f, 100.0f ) 
				);
	cam.set(	vec3( 0.0f, 5.0f, -20.0f ), 
				vec3( 0.0f, 0.0f, 0.0f ), 
				vec3( 0.0f, 1.0f, 0.0f )
				);
}

void App::run()
{
	double last_tick = window.getTime();
	double time_since_last_update = 0.0;
	bool running = true;
	while( running && window.isOpen() )
	{
		window.update();

		time_since_last_update += window.getTime() - last_tick;
		last_tick = window.getTime();
		if( time_since_last_update >= DELTA_TIME )
		{
			Input::update();
			if( Input::isKeyPressed( Input::ESC ) )
				running = false;

			mv.set( lookAt( cam.position, cam.focus, cam.upDir ) );
			cam.update();

			doUpdate();
			time_since_last_update = 0;
		}

		window.clear();
		doDraw();
		window.swapBuffers();
	}
}

std::string App::fps()
{
   static std::string fpsstr = ""; 
   static int FPS = 60;
   double next_sec = 0.0f;
   static double prev_sec = 0.0f;

   FPS++;
   next_sec = Window::getTime();				

   if( next_sec - prev_sec > 1.0f )
   {
		prev_sec = next_sec;
		fpsstr = lexicalCast<std::string>( FPS );
		FPS = 0;
   }
	return fpsstr;
}