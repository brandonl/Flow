#ifndef __COLOR_H__
#define __COLOR_H__

#include <sstream>
#include <string>

class Color
{
	public:
		Color();
		Color( float r, float g, float b, float a );
		Color( const std::string &hex_value );

		static Color black;
		static Color orange;
		static Color grey;
		static Color purple;
		static Color yellow;
		static Color xred;
		float r, g, b, a;
};

#endif
