#ifndef INPUT_H
#define INPUT_H

#if defined(_MSC_VER)&&(_MSC_VER>=1200)
#pragma once
#endif

#include <Box2D.h>

typedef b2Vec2 vec2;

namespace slge
{

	static const unsigned int MAX_KEYS  = 322;
	static const unsigned int MAX_MOUSE_BUTTONS  = 10;
	//! \class input
	//! \brief As name suggests: Manages game input including key evens and mouse events.
	//!
	class input
	{
		public:
			explicit input();
			~input();
			void init();
			static void update();

			/**		Keys API	**/
			//! \brief Handles registering key events from the glfw callback
			//! \param int keycode, int action ( 0:pressed, 1:released)
			static void key_event( int, int );
			//! \brief Is the key currently being held.
			static bool is_key_held( int );
			//! \brief Has the key been pressed in the current frame (Press then release).
			static bool is_key_pressed( int );
			//! \brief Has the key been released in the current frame.
			static bool is_key_released( int );

			/** 	Mouse API	**/
			//! \brief Handles registering mouse button events from the glfw callback
			//! \param int keycode, int action ( 0:pressed, 1:released)
			static void mouse_down_event( int, int );
			//! \brief Handles registering mouse movement events from the glfw callback
			//! \param int x horizontal position of the mouse, int y vertical position of the mouse.
			static void mouse_move_event( int, int );
			//! \brief Is the mouse button key currently being held.
			static bool is_mouse_button_held( int );
			//! \brief Has the mouse button been pressed in the current frame (Press then release).
			static bool is_mouse_button_pressed( int );
			//! \brief Has the mouse button been released in the current frame.
			static bool is_mouse_button_released( int );
			//! \brief The position of the mouse in world coordinates.
			static vec2 get_mouse_position();
			//! \brief Return the x and y percentage of the mouse position 0.0 - 1.0
			static vec2 get_mouse_percentage();

		private:
			static input *instance;

			bool prev_key_events[MAX_KEYS];
			bool curr_key_events[MAX_KEYS];

			bool prev_mouse_buttons[MAX_MOUSE_BUTTONS];
			bool curr_mouse_buttons[MAX_MOUSE_BUTTONS];
			vec2 mouse_position;

			//!< \brief The actual key/mouse buttons events registered by the glfw key callback function handled
			//!< in the glfw initilizer class: window.h
			bool key_events[MAX_KEYS];
			bool mouse_button_events[MAX_MOUSE_BUTTONS];

		public:
			enum Terminal
			{
				NO_TERMINAL = -1,
				ESC = 257,
				F1,
				F2,
				F3,
				F4,
				F5,
				F6,
				F7,
				F8,
				F9,
				F10,
				F11,
				F12,
				F13,
				F14,
				F15,
				F16,
				F17,
				F18,
				F19,
				F20,
				F21,
				F22,
				F23,
				F24,
				F25,
				UP,
				DOWN,
				LEFT,
				RIGHT,
				TAB = 293,
				ENTER,
				BACKSPACE,
				INSERT,
				DEL,
				PAGE_UP,
				PAGE_DOWN,
				HOME,
				END,
				KP_0,
				KP_1,
				KP_2,
				KP_3,
				KP_4,
				KP_5,
				KP_6,
				KP_7,
				KP_8,
				KP_9,
				KP_DIVIDE,
				KP_MULTIPLY,
				KP_SUBTRACT,
				KP_ADD,
				KP_DECIMAL,
				KP_EQUAL,
				KP_ENTER,
				KP_NUM_LOCK,
				CAPS_LOCK,
				SCROLL_LOCK,
				PAUSE
			};
			enum Mouse_Terminal
			{			
				MOUSE_LEFT = 0,
				MOUSE_RIGHT,
				MOUSE_MIDDLE,
				MOUSE4,
				MOUSE5,
				MOUSE6,
				MOUSE7,
				MOUSE8,
				MOUSE_WHEEL_UP,
				MOUSE_WHEEL_DOWN
			};
	};


};

#endif
