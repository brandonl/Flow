#ifndef INPUT_H
#define INPUT_H

#include <glm/glm.hpp>
#include "Utils.h"

namespace flow
{
	class Input : private Uncopyable
	{
		static const unsigned int MAX_KEYS  = 322;
		static const unsigned int MAX_MOUSE_BUTTONS  = 10;

		public:
			Input();
			~Input();
			void init();
			static void update();

			//! \brief Is the key currently being held.
			static bool isKeyHeld( int );
			//! \brief Has the key been pressed in the current frame (Press then release).
			static bool isKeyPressed( int );
			//! \brief Has the key been released in the current frame.
			static bool isKeyReleased( int );

			//! \brief Is the mouse Button key currently being held.
			static bool isMouseButtonHeld( int );
			//! \brief Has the mouse Button been pressed in the current frame (Press then release).
			static bool isMouseButtonPressed( int );
			//! \brief Has the mouse Button been released in the current frame.
			static bool isMouseButtonReleased( int );
			//! \brief The position of the mouse in World coordinates.
			static glm::vec2 getMousePosition();
			//! \brief Return the x and y percentage of the mouse position 0.0 - 1.0
			static glm::vec2 getMousePercentage();
			static void	setMousePosition( int x, int y );

		private:
			//! \brief Handles registering key events from the glfw callback
			//! \param int keycode, int action ( 0:pressed, 1:released)
			static void keyEvent( int, int );
			//! \brief Handles registering mouse Button events from the glfw callback
			//! \param int keycode, int action ( 0:pressed, 1:released)
			static void mouseDownEvent( int, int );
			//! \brief Handles registering mouse movement events from the glfw callback
			//! \param int x horizontal position of the mouse, int y vertical position of the mouse.
			static void mouseMoveEvent( int, int );

		private:
			static Input *instance;

			bool prevKeyEvents[MAX_KEYS];
			bool currKeyEvents[MAX_KEYS];

			bool prevMouseButtons[MAX_MOUSE_BUTTONS];
			bool currMouseButtons[MAX_MOUSE_BUTTONS];
			glm::vec2 mousePosition;

			//!< \brief The actual key/mouse buttons events registered by the glfw key callback function handled
			//!< in the glfw initilizer class: Window.h
			bool keyEvents[MAX_KEYS];
			bool mouseButtonEvents[MAX_MOUSE_BUTTONS];

		public:
			enum
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

			enum
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
