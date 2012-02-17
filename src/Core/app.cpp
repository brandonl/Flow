#include "App.h"
#include "Debug.h"
#include "LexicalCast.h"
#include "../Scene.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

const float App::DELTA_TIME = 1.0f/60.0f;
App *App::instance = 0;

App::App() 
	: scene(0), running(true)
{
	if( instance != NULL )
		std::cerr << "Only one App context may be active at a time.";
	instance = this;
}

App::~App()
{
}

void App::init( const std::string& name, unsigned int width, unsigned int height  )
{
	window.init( name, width, height, 32, 24 );
	input.init();

	p.modify( perspective( 35.0f, static_cast<float>( Window::get_width() ) / Window::get_height(), 0.1f, 100.0f ) );
	cam.set(	vec3( 0.0f, 5.0f, -20.0f ), vec3( 0.0f, 0.0f, 0.0f ), vec3( 0.0f, 1.0f, 0.0f ) );
}

void App::set( Scene* s )
{
	scene = s;
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

			model_view().set( lookAt( cam.position, App::cam.focus, cam.up_direction ) );
			cam.update();

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

std::string App::fps()
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
		fpsstr = lexicalCast<std::string>( FPS );
		FPS = 0;
   }
	return fpsstr;
}

Camera& App::camera()
{	
	return instance->cam;
}

MatrixStack& App::model_view()
{
	return instance->mv;
}

MatrixStack& App::projection()
{
	return instance->p;
}