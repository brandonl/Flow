#include <cstdio>
#include "Input.h"
#define GLFW_NO_GLU
#include <GL/glfw.h>

using namespace flow;

Input *Input::instance = nullptr;

Input::Input()
{
	if( instance != nullptr )
		printf( "Only one Input context may be active at a time.\n" );
	instance = this;
}

Input::~Input()
{
}

void Input::init()
{
	glfwSetKeyCallback( keyEvent );
	glfwSetMouseButtonCallback( mouseDownEvent );
	glfwSetMousePosCallback( mouseMoveEvent );

	for( unsigned int i = 0; i < MAX_KEYS; ++i )
		prevKeyEvents[i] = currKeyEvents[i] = keyEvents[i] = false;

	for( unsigned int i = 0; i < MAX_MOUSE_BUTTONS; ++i )
		prevMouseButtons[i] = currMouseButtons[i] = mouseButtonEvents[i] = false;
}

void Input::update()
{
	for( unsigned int i = 0; i < MAX_KEYS; ++i )
	{
		instance->prevKeyEvents[i] = instance->currKeyEvents[i];
		instance->currKeyEvents[i] = instance->keyEvents[i];
	}

	for( unsigned int i = 0; i < MAX_MOUSE_BUTTONS; ++i )
	{
		instance->prevMouseButtons[i] = instance->currMouseButtons[i];
		instance->currMouseButtons[i] = instance->mouseButtonEvents[i];
	}
}

///////////////////////////////////////////////////////////////////////////////
// K E Y S A P I
///////////////////////////////////////////////////////////////////////////////
void Input::keyEvent( int key, int action )
{
	instance->keyEvents[key] = action > 0 ? true : false;
}

bool Input::isKeyHeld( int k )
{
	return instance->currKeyEvents[k];
}

bool Input::isKeyPressed( int k )
{
	return instance->currKeyEvents[k] && !instance->prevKeyEvents[k];
}

bool Input::isKeyReleased( int k )
{
	return !instance->currKeyEvents[k] && instance->prevKeyEvents[k];
}

///////////////////////////////////////////////////////////////////////////////
// M O U S E A P I
///////////////////////////////////////////////////////////////////////////////
void Input::mouseDownEvent( int key, int action )
{
	instance->mouseButtonEvents[key] = action > 0 ? true : false;
}

void Input::mouseMoveEvent( int x, int y )
{
	instance->mousePosition = glm::vec2( x, y );
}

bool Input::isMouseButtonHeld( int b )
{
	return instance->currMouseButtons[b];
}

bool Input::isMouseButtonPressed( int b )
{
	return instance->currMouseButtons[b] && !instance->prevMouseButtons[b];
}

bool Input::isMouseButtonReleased( int b )
{
	return !instance->currMouseButtons[b] && instance->prevMouseButtons[b];
}

glm::vec2 Input::getMousePosition()
{
	return glm::vec2( instance->mousePosition );
}

glm::vec2 Input::getMousePercentage()
{
	int w = 0, h = 0;
	glfwGetWindowSize( &w, &h );
	return glm::vec2( instance->mousePosition.x / w,
							instance->mousePosition.y / h );
}

void Input::setMousePosition( int x, int y )
{
	glfwSetMousePos( x, y );
	instance->mousePosition = glm::vec2( x, y );
}