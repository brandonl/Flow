#ifndef FONT_H
#define FONT_H

#include <string>

class Font
{
	public:
		explicit Font();
		~Font();

		bool load(	const std::string &fp, 
								float size, 
								unsigned int tex_width = 0, 
								unsigned int tex_height = 0 );

		void begin() const;
		void end() const;
		void draw( const std::string &text, float x, float y, float scalar = 1.0f );

		float pixel_height;
		unsigned int texture_width;
		unsigned int texture_height;

	private:
		unsigned int texid;
		void* cdata;
		unsigned vao, vbo;

};

#endif