#include "color.h"

Color Color::black	= Color( 0.0f, 0.0f, 0.0f, 1.0f );
Color Color::grey	= Color( 0.5f, 0.5f, 0.5f, 1.0f );
Color Color::yellow = Color( 1.0f, 1.0f, 0.0f, 1.0f );
Color Color::orange = Color( 1.0f, 0.5f, 0.0f, 1.0f );
Color Color::purple = Color( 0.5f, 0.0f, 1.0f, 1.0f );
Color Color::xred	= Color( 1.0f, 0.4f, 0.32f, 1.0f );

Color::Color()
	:	r(1.0f),
		g(1.0f),
		b(1.0f),
		a(1.0f)
{}

Color::Color( float r, float g, float b, float a )
	:	r(r),
		g(g),
		b(b),
		a(a)
{}

Color::Color( const std::string &hex_value )
{
	std::istringstream is( hex_value );

	unsigned int hexcolor;
	is >> std::hex >> hexcolor;

	r = (float)( ( hexcolor >> 16 ) & 0xFF );
	g = (float)( ( hexcolor >> 8 ) & 0xFF );
	b = (float)( hexcolor & 0xFF );
	r /= 255.0f;
	g /= 255.0f;
	b /= 255.0f;
	a = 1.0f;
}

