#ifndef APP_H
#define APP_H

#include "Window.h"
#include "Input.h"
#include <string>
#include "Camera.h"
#include "MatrixStack.h"
#include "Utils.h"

namespace flow
{
	class App : private Uncopyable
	{
		public:
			App( const std::string& name, int width = 800, int height = 600 );
			void run();
			void init();

		protected:
			static std::string fps();

		private:
			void baseInit();
			virtual void doUpdate() = 0;
			virtual void doDraw() = 0;
			virtual void doInit() = 0;
			static const float DELTA_TIME;

		protected:
			Camera cam;
			MatrixStack mv;
			MatrixStack p;

		private:
			Window window;
			Input input;
	};

	inline void App::init()
	{
		baseInit();
		doInit();
	}
};
#endif
