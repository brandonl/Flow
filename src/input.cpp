#include <iostream>
#include "input.h"
#include "window.h"

using namespace slge;

input *input::instance = NULL;

input::input()
{
	if( instance != NULL )
		std::cerr << "Only one input context may be active at a time.";
	instance = this;
}

input::~input()
{
}

void input::init()
{
	for( unsigned int i = 0; i < MAX_KEYS; ++i )
		prev_key_events[i] = curr_key_events[i] = key_events[i] = false;

	for( unsigned int i = 0; i < MAX_MOUSE_BUTTONS; ++i )
		prev_mouse_buttons[i] = curr_mouse_buttons[i] = mouse_button_events[i] = false;
}

void input::update()
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
void input::key_event( int key, int action )
{
	instance->key_events[key] = action > 0 ? true : false;
}

bool input::is_key_held( int k )
{
	return instance->curr_key_events[k];
}

bool input::is_key_pressed( int k )
{
	return instance->curr_key_events[k] && !instance->prev_key_events[k];
}

bool input::is_key_released( int k )
{
	return !instance->curr_key_events[k] && instance->prev_key_events[k];
}

///////////////////////////////////////////////////////////////////////////////
// M O U S E A P I
///////////////////////////////////////////////////////////////////////////////
void input::mouse_down_event( int key, int action )
{
	instance->mouse_button_events[key] = action > 0 ? true : false;
}

void input::mouse_move_event( int x, int y )
{
	instance->mouse_position = vec2( x, y );
}

bool input::is_mouse_button_held( int b )
{
	return instance->curr_mouse_buttons[b];
}

bool input::is_mouse_button_pressed( int b )
{
	return instance->curr_mouse_buttons[b] && !instance->prev_mouse_buttons[b];
}

bool input::is_mouse_button_released( int b )
{
	return !instance->curr_mouse_buttons[b] && instance->prev_mouse_buttons[b];
}

vec2 input::get_mouse_position()
{
	return vec2( instance->mouse_position );
}

vec2 input::get_mouse_percentage()
{
	return vec2( 	instance->mouse_position.x / window::get_width(),
					instance->mouse_position.y / window::get_height() );
}

