#include "texture.h"
#define GLFW_NO_GLU
#include <GL/glew.h>
#include <GL/glfw.h>
#include "debug.h"

Texture::Texture()
	: name(0), 
		anisotropic_amount(-1.0f)
{
}

Texture::~Texture()
{
	unload();
}


bool Texture::load( const std::string& filename, float anisotropic_level )
{
	this->filename = filename;
	anisotropic_amount = anisotropic_level;

	glGenTextures(1, &name);
	glActiveTexture( GL_TEXTURE0 );
	glBindTexture(GL_TEXTURE_2D, name );

	// Read the file, call glTexImage2D with the right parameters
	if( !glfwLoadTexture2D( filename.c_str(), GLFW_ORIGIN_UL_BIT ) )
	{
		debug() << "Failed to load texture with path: " << filename << std::endl;
		return false;
	}

	// Nice trilinear filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
	glGenerateMipmap(GL_TEXTURE_2D);


	if( anisotropic_amount > 0 )
	{
		GLint num_extensions;
		glGetIntegerv( GL_NUM_EXTENSIONS, &num_extensions );
		GLint i;
		std::string extension = "GL_EXT_texture_filter_anisotropic";
		for( i = 0; i < num_extensions; i++ )
			if( extension == (const char*) glGetStringi( GL_EXTENSIONS, i ) )
				break;

		if( i != num_extensions )
		{
			float largest_filtering;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest_filtering);

			if( anisotropic_amount > largest_filtering )
				anisotropic_amount = largest_filtering;

			debug() << "Texture::load: Using anisotropic filtering\n";
			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropic_amount );
		}

		else
		debug() << "Texture::load: Anisotropic Filtering NOT Supported\n";
	}

	debug() << "Texture::load: Texture loaded @ " << filename << std::endl;
	return true;
}

void Texture::unload()
{
	glDeleteTextures( 1, &name );
}

unsigned int Texture::get_name() const
{
	return name;
}