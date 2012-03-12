#include "Texture2.h"
#include <cstdio>

using namespace flow;

void Texture2::load( const ImageRef &&iref )
{
	if( iref )
	{
		hwidth = iref.getImageWidth();
		hheight = iref.getImageHeight();

		glEnable( GL_TEXTURE_2D );
		glGenTextures( 1, &name );
		glBindTexture( GL_TEXTURE_2D, name );

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

		glTexImage2D(	GL_TEXTURE_2D, 0, GL_RGBA, 
							hwidth, hheight, 0, GL_RGBA, 
							GL_UNSIGNED_BYTE,
							iref.referencedData() 
						);

		hheight >>= 1;
		hwidth >>= 1;
		glDisable( GL_TEXTURE_2D );
	}
	else printf( "Failed to create Texture2 from ImageRef: %s", iref.getImageName().c_str() );
}

void Texture2::load( const std::string &imageFileName )
{
	load( ImageRef( imageFileName ) );
}

Texture2::~Texture2()
{
	if( name != 0 )
	{
		glDeleteTextures( 1, &name );
		name = 0;
	}
}

