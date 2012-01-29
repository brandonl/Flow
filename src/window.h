#ifndef WINDOW_H
#define WINDOW_H

#if defined(_MSC_VER)&&(_MSC_VER>=1200)
#pragma once
#endif

#include <string>

namespace slge
{
	class window
	{
		public:
			explicit window();
			~window();
			void init( const std::string& , int, int, int, int );

			static void		update();
			static void		clear();
			static void		swap_buffers();
			static bool		is_open();
			static int		get_width();
			static int		get_height();
			static float	get_aspect_ratio();
			static double	tick();
			static void		set_title( const std::string& );
			static void		center();
			static int		*display_size();

		private:
			std::string title;
			int width;
			int height; 	
			int cdepth; 		
			int zbdepth; 			
			float ratio;		

			static window *instance;
			static void key_event_callback( int, int );
			static void mouse_button_callback( int, int );
			static void mouse_position_callBack( int, int );
	};

};
#endif
