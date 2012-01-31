#ifndef APP_H
#define APP_H

#include "window.h"
#include "input.h"
#include "../scene.h"
#include <string>

class App
{
	public:
		static const float DELTA_TIME;

		explicit App();
		~App();

		void run();
		void init( const std::string& name ="F L O W", unsigned width = 800, unsigned height = 600 );
		void set( Scene* );
		std::string get_fps();

	private:
		void quit();
		Window window;
		Input input;
		Scene *scene;
		bool running;
};
#endif
