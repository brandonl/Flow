#include <iostream>
#include "input.h"
#include "window.h"

Input *Input::instance = NULL;

Input::Input()
{
	if( instance != NULL )
		std::cerr << "Only one Input context may be active at a time.";
	instance = this;
}

Input::~Input()
{
}

void Input::init()
{
	for( unsigned int i = 0; i < MAX_KEYS; ++i )
		prev_key_events[i] = curr_key_events[i] = key_events[i] = false;

	for( unsigned int i = 0; i < MAX_MOUSE_BUTTONS; ++i )
		prev_mouse_buttons[i] = curr_mouse_buttons[i] = mouse_button_events[i] = false;
}

void Input::update()
{
	for( unsigned int i = 0; i < MAX_KEYS; ++i )
	{
		instance->prev_key_events[i] = instance->curr_key_events[i];
		instance->curr_key_events[i] = instance->key_events[i];
	}

	for( unsigned int i = 0; i < MAX_MOUSE_BUTTONS; ++i )
	{
		instance->prev_mouse_buttons[i] = instance->curr_mouse_buttons[i];
		instance->curr_mouse_buttons[i] = instance->mouse_button_events[i];
	}
}

///////////////////////////////////////////////////////////////////////////////
// K E Y S A P I
///////////////////////////////////////////////////////////////////////////////
void Input::key_event( int key, int action )
{
	instance->key_events[key] = action > 0 ? true : false;
}

bool Input::is_key_held( int k )
{
	return instance->curr_key_events[k];
}

bool Input::is_key_pressed( int k )
{
	return instance->curr_key_events[k] && !instance->prev_key_events[k];
}

bool Input::is_key_released( int k )
{
	return !instance->curr_key_events[k] && instance->prev_key_events[k];
}

///////////////////////////////////////////////////////////////////////////////
// M O U S E A P I
///////////////////////////////////////////////////////////////////////////////
void Input::mouse_down_event( int key, int action )
{
	instance->mouse_button_events[key] = action > 0 ? true : false;
}

void Input::mouse_move_event( int x, int y )
{
	instance->mouse_position = glm::vec2( x, y );
}

bool Input::is_mouse_button_held( int b )
{
	return instance->curr_mouse_buttons[b];
}

bool Input::is_mouse_button_pressed( int b )
{
	return instance->curr_mouse_buttons[b] && !instance->prev_mouse_buttons[b];
}

bool Input::is_mouse_button_released( int b )
{
	return !instance->curr_mouse_buttons[b] && instance->prev_mouse_buttons[b];
}

glm::vec2 Input::get_mouse_position()
{
	return glm::vec2( instance->mouse_position );
}

glm::vec2 Input::get_mouse_percentage()
{
	return glm::vec2( 	instance->mouse_position.x / Window::get_width(),
					instance->mouse_position.y / Window::get_height() );
}

