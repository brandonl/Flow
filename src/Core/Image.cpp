#include "Image.h"
#include "stb_image.hpp"

using namespace flow;

Image::Image( const std::string& fn )
	:	Resource( fn ),
		raw( stbi_load( fn.c_str(), &width, &height, nullptr, STBI_rgb_alpha ), stbi_image_free )
{
	if( !raw.get() )
		printf( "Image file (%s) does not appear to be a valid image file; expect errors.\n", fn.c_str() );
}

Image& Image::operator=( Image&& m )
{
	width = std::move( m.width );
	height = std::move( m.height );
	raw.swap( m.raw );
	return *this;
}