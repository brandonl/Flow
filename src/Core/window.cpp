#include "window.h"
#include <iostream>
#include "input.h"

Window *Window::instance = NULL;

Window::Window()
{
	if( instance != NULL )
		std::cerr << "Only one Window may be active at a time."<< std::endl;

	instance = this;
}

Window::~Window()
{
	glfwCloseWindow();
	glfwTerminate();
}

void Window::init( const std::string& ntitle, int w, int h, int cdepth, int zdepth )
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

	glfwSetKeyCallback( key_event_callback );
	glfwSetMouseButtonCallback( mouse_button_callback );
	glfwSetMousePosCallback( mouse_position_callBack );
}

void Window::update()
{
	int last_width = instance->width;
	int last_height = instance->height;

	glfwGetWindowSize( &instance->width, &instance->height );

	if( last_width != instance->width || last_height != instance->height )
		glViewport( 0, 0, instance->width, instance->height );

	glfwPollEvents();
}

void Window::clear()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void Window::swap_buffers()
{
	glfwSwapBuffers();
}

bool Window::is_open()
{
	return ( glfwGetWindowParam( GLFW_OPENED ) == 0 ? false : true );
}

int Window::get_width()
{
	return instance->width;
}

int Window::get_height()
{
	return instance->height;
}

float Window::get_aspect_ratio()
{
	return instance->ratio;
}

double Window::tick()
{
	return glfwGetTime();
}

void Window::set_title( const std::string& ntitle )
{
	glfwSetWindowTitle( ntitle.c_str() );
}

void Window::center()
{
	int *display_size = instance->display_size();

	glfwGetWindowSize( &instance->width, &instance->height );
	glfwSetWindowPos( ( display_size[0] - instance->width ) / 2, ( display_size[1] - instance->height ) / 2 );
}

int *Window::display_size()
{
	GLFWvidmode desktop_resolution;
	glfwGetDesktopMode( &desktop_resolution );
	static int display_size[2] = { desktop_resolution.Width, desktop_resolution.Height };
	return display_size;
}

void Window::key_event_callback( int key, int action )
{
	Input::key_event( key, action );
}

void Window::mouse_position_callBack( int x, int y )
{
	Input::mouse_move_event( x, y );
}

void Window::mouse_button_callback( int button, int action )
{
	Input::mouse_down_event( button, action );
}