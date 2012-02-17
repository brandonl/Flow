#ifndef APP_H
#define APP_H

#include "Window.h"
#include "Input.h"
#include <string>
#include "Camera.h"
#include "MatrixStack.h"
#include "Uncopyable.h"

class Scene;

class App : private Uncopyable
{
	public:
		static const float DELTA_TIME;

		App();
		~App();

		void run();
		void init( const std::string& name ="F L O W", unsigned width = 800, unsigned height = 600 );
		void set( Scene* );

		static std::string fps();
		static Camera& camera();
		static MatrixStack& model_view();
		static MatrixStack& projection();

	private:
		static App *instance;
		void quit();
		Window window;
		Input input;
		Scene *scene;

		Camera cam;
		MatrixStack mv;
		MatrixStack p;
		bool running;
};
#endif
