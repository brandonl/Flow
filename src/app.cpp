#include "app.h"
#include <iostream>
#include <sstream>

const float App::DELTA_TIME = 1.0f/60.0f;

App::App() : running(true)
{
}

App::~App()
{
}

void App::init( const std::string& name, unsigned int width, unsigned int height  )
{
	window.init( name, width, height, 32, 24 );
	input.init();
}

void App::set( Scene* s )
{
	scene = s;
}

std::string App::get_fps()
{
   static std::string fpsstr = ""; 
   static int FPS = 60;
   double next_sec = 0.0f;
   static double prev_sec = 0.0f;

   FPS++;
   next_sec = Window::tick();				

   if( next_sec - prev_sec > 1.0f )
   {
		prev_sec = next_sec;
		std::stringstream ss;
		ss << FPS << " FPS";
		ss >> fpsstr;
		FPS = 0;
   }
	return fpsstr;
}

void App::run()
{
	double last_tick = Window::tick();
	double time_since_last_update = 0.0;

	while( running && Window::is_open() )
	{
		Window::update();

		time_since_last_update += Window::tick() - last_tick;
		last_tick = Window::tick();
		if( time_since_last_update >= DELTA_TIME )
		{
			Input::update();
			if( Input::is_key_pressed( Input::ESC ) )
				quit();
			scene->update();
			time_since_last_update = 0;
		}

		Window::clear();
		scene->draw();
		Window::swap_buffers();
	}
}


void App::quit()
{
	running = false;
}
