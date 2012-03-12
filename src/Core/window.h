#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <string>
#include "Utils.h"

namespace flow
{
	class Window : private Uncopyable
	{
		friend class App;

		private:
			explicit Window( const std::string& title, int w = 800, int h = 600, int cdepth = 32, int zdepth = 24 );
			~Window();

			void update();
			void clear();
			void swapBuffers();
			bool isOpen();
			void close();
			void center();
			static void		windowResizeCB( int width, int height );

		public:
			static void				setTitle( const std::string& );
			static const float	getAspectRatio();
			static const int		getWidth();
			static const int		getHeight();
			static const int		getDisplayWidth();
			static const int		getDisplayHeight();
			static const double	getTime();
	};

};
#endif
