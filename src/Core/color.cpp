#include "Color.h"
#include <sstream>

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

Color::Color( const char* hexValue )
{
	std::istringstream is( hexValue );

	unsigned hexcolor;
	is >> std::hex >> hexcolor;

	r = static_cast<float>( ( hexcolor >> 16 ) & 0xFF );
	g = static_cast<float>( ( hexcolor >> 8 ) & 0xFF );
	b = static_cast<float>( hexcolor & 0xFF );
	r /= 255.0f;
	g /= 255.0f;
	b /= 255.0f;
	a = 1.0f;
}

