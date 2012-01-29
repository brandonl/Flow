#define GLFW_NO_GLU
#include <GL/glfw.h>
#include "window.h"
#include <iostream>
#include "input.h"

using namespace slge;

window *window::instance = NULL;

window::window()
{
	if( instance != NULL )
		std::cerr << "Only one window may be active at a time."<< std::endl;

	instance = this;
}

window::~window()
{
	glfwCloseWindow();
	glfwTerminate();
}

void window::init( const std::string& ntitle, int w, int h, int cdepth, int zdepth )
{
	title = ntitle;
	width = w;
	height = h;
	cdepth = cdepth;
	zbdepth = zdepth;
	ratio = ( (GLfloat)width / height );

	if( !glfwInit() )
		std::cerr <<  "GLFW Error: Failed to initialize GLFW" << std::endl;

	int bits_per_color = cdepth / 4;

	if( !glfwOpenWindow( 	width, height,
							bits_per_color, bits_per_color, bits_per_color, bits_per_color,
							zbdepth, 0,
							GLFW_WINDOW ) )
		std::cerr <<  "GLFW Error:  Failed to open GL Context Window"<< std::endl;

	center();

	glfwSetWindowTitle( title.c_str() );

	// Disable polling on swap buffers; we will call on our own terms.
	glfwDisable( GLFW_AUTO_POLL_EVENTS );
	glfwEnable( GLFW_KEY_REPEAT );

	if( height == 0 )
		height = 1;

	glViewport( 0, 0, width, height );

	glfwSetKeyCallback( key_event_callback );
	glfwSetMouseButtonCallback( mouse_button_callback );
	glfwSetMousePosCallback( mouse_position_callBack );
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0f, width, height, 0.0f, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable( GL_TEXTURE_2D );
	glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );

	glDisable( GL_DEPTH_TEST );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}

void window::update()
{
	int last_width = instance->width;
	int last_height = instance->height;

	glfwGetWindowSize( &instance->width, &instance->height );

	if( last_width != instance->width || last_height != instance->height )
		glViewport( 0, 0, instance->width, instance->height );

	glfwPollEvents();
}

void window::clear()
{
	glClear( GL_COLOR_BUFFER_BIT );
}

void window::swap_buffers()
{
	glfwSwapBuffers();
}

bool window::is_open()
{
	return ( glfwGetWindowParam( GLFW_OPENED ) == 0 ? false : true );
}

int window::get_width()
{
	return instance->width;
}

int window::get_height()
{
	return instance->height;
}

float window::get_aspect_ratio()
{
	return instance->ratio;
}

double window::tick()
{
	return glfwGetTime();
}

void window::set_title( const std::string& ntitle )
{
	glfwSetWindowTitle( ntitle.c_str() );
}

void window::center()
{
	int *display_size = instance->display_size();

	glfwGetWindowSize( &instance->width, &instance->height );
	glfwSetWindowPos( ( display_size[0] - instance->width ) / 2, ( display_size[1] - instance->height ) / 2 );
}

int *window::display_size()
{
	GLFWvidmode desktop_resolution;
	glfwGetDesktopMode( &desktop_resolution );
	static int display_size[2] = { desktop_resolution.Width, desktop_resolution.Height };
	return display_size;
}

void window::key_event_callback( int key, int action )
{
	input::key_event( key, action );
}

void window::mouse_position_callBack( int x, int y )
{
	input::mouse_move_event( x, y );
}

void window::mouse_button_callback( int button, int action )
{
	input::mouse_down_event( button, action );
}