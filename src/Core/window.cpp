#define GLFW_NO_GLU
#include <GL/glfw.h>
#include "Window.h"
#include <cstdio>

using namespace flow;

Window::Window( const std::string& ntitle, int w, int h, int cdepth, int zdepth )
{
	if( !glfwInit() )
		printf( "GLFW Error: Failed to initialize GLFW\n" );

	int bitsPerColor = cdepth / 4;
	if( h == 0 ) h = 1;

	// TODO: Add option.
	glfwOpenWindowHint( GLFW_WINDOW_NO_RESIZE, GL_TRUE );

	if( !glfwOpenWindow( 	w, h,
									bitsPerColor, bitsPerColor, bitsPerColor, bitsPerColor,
									zdepth, 0,
									GLFW_WINDOW ) )
		printf( "GLFW Error:  Failed to open GL Context Window\n" );

	this->center();

	// Disable polling on swap buffers; we will call on our own terms.
	glfwDisable( GLFW_AUTO_POLL_EVENTS );
	glfwSetWindowTitle( ntitle.c_str() );
	glfwEnable( GLFW_KEY_REPEAT );
	glfwSetWindowSizeCallback( windowResizeCB );
}

Window::~Window()
{
	glfwCloseWindow();
	glfwTerminate();
}

void Window::update()
{
	glfwPollEvents();
}

void Window::clear()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void Window::swapBuffers()
{
	glfwSwapBuffers();
}

bool Window::isOpen()
{
	return ( !glfwGetWindowParam( GLFW_OPENED ) ? false : true );
}

void Window::close()
{
	glfwCloseWindow();
}

void Window::center()
{
	glfwSetWindowPos( ( getDisplayWidth() - getWidth() ) / 2, ( getDisplayHeight() - getHeight() ) / 2 );
}

void Window::windowResizeCB( int w, int h )
{
	glViewport( 0, 0, w, h );
}

const int Window::getWidth()
{
	int w = 0, h = 0;
	glfwGetWindowSize( &w, &h );
	return w;
}

const int Window::getHeight()
{
	int w = 0, h = 0;
	glfwGetWindowSize( &w, &h );
	return h;
}

const float Window::getAspectRatio()
{
	return ( static_cast<GLfloat>( getWidth() ) / getHeight() );
}

const double Window::getTime()
{
	return glfwGetTime();
}

void Window::setTitle( const std::string& ntitle )
{
	glfwSetWindowTitle( ntitle.c_str() );
}

const int Window::getDisplayHeight()
{
	GLFWvidmode desktopResolution;
	glfwGetDesktopMode( &desktopResolution );
	return desktopResolution.Height;
}

const int Window::getDisplayWidth()
{
	GLFWvidmode desktopResolution;
	glfwGetDesktopMode( &desktopResolution );
	return desktopResolution.Width;
}