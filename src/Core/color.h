#ifndef __COLOR_H__
#define __COLOR_H__

class Color
{
	public:
		Color();
		Color( float r, float g, float b, float a );
		Color( const char* hexValue );

		static Color black;
		static Color orange;
		static Color grey;
		static Color purple;
		static Color yellow;
		static Color xred;
		float r, g, b, a;
};

#endif
