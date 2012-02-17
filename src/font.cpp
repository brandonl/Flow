#include <GL/glew.h>
#include "Font.h"

// This define "expands out the actual implemenation into this file.
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb/stb_truetype.h"
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "Core/polygon.h"
using namespace glm;

Font::Font()
	:	pixel_height(0.0f),
		texture_height(512),
		texture_width(512)
{
}

Font::~Font()
{
	std::cout << "Deleting Font" << std::endl;
	glDeleteTextures( 1, &texid );
	if( cdata )
		delete cdata;
	glDeleteBuffers( 1, &vbo );
	glDeleteVertexArrays( 1, &vao );
}

// Code based on stb_ttf usage examples.
bool Font::load( const std::string &fp, float pixel_height, unsigned int tex_width, unsigned int tex_height )
{
	glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao );
	glGenBuffers( 1, &vbo );
	glBindBuffer( GL_ARRAY_BUFFER, vbo );

	glVertexAttribPointer( 0,	3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)0 );
	glVertexAttribPointer( 1,	3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, normal) );
	glVertexAttribPointer( 2,	2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, tex0) );
	glVertexAttribPointer( 3,	4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, color) );
	for( unsigned int i = 0; i <= 3; ++i )
		glEnableVertexAttribArray( i );

	glBindVertexArray( 0 );

	FILE *ptr_file = fopen( fp.c_str(), "rb" );
	if( ptr_file == NULL )
	{
		std::cerr << "Font::load: Error: Font file failed to open.\n";
		return false;
	}

	unsigned char* buffer = new unsigned char [1<<20];
	fread( buffer, 1, 1<<20, ptr_file );
	fclose( ptr_file );

	this->pixel_height = pixel_height;

	if( tex_width != 0 )
		texture_width = tex_width;

	if( tex_height != 0 )
		texture_width = tex_width;

	// ASCII 32..126 is 95 glyphs
	cdata = new stbtt_bakedchar[96];
	unsigned char* bitmap = new unsigned char[ texture_width*texture_height ];
	if( ( stbtt_BakeFontBitmap( buffer, 0, this->pixel_height, bitmap, texture_width, texture_height, 32, 96, (stbtt_bakedchar *)cdata ) == 0 ) )
	{
		std::cerr << "Font::load: Error: No characters fit and no rows were used.\n";
		delete buffer;
		delete bitmap;
		return false;
	}
	delete buffer;

	glGenTextures( 1, &texid );
	glBindTexture( GL_TEXTURE_2D, texid );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_ALPHA, texture_width, texture_height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, bitmap );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	delete bitmap;

	return true;
}

void Font::begin() const
{
	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, texid );
	glBindVertexArray( vao );
}

void Font::end() const
{
	//End, Reset State
	glDisable( GL_BLEND );
	glBindVertexArray( 0 );
	glUseProgram( 0 );
	glBindTexture( GL_TEXTURE_2D, 0 );
}

void Font::draw ( const std::string &text, float x, float y, float scalar )
{
	char c;
	stbtt_aligned_quad q;
	Polygon quad;

	//Loop through characters
	for( size_t i = 0; i < text.length(); ++i )
	{
		//Make sure character is in range
		c = text[i];
		if ( ( c < 32 ) || ( c >= 128 ) )
			continue;

		stbtt_GetBakedQuad( (stbtt_bakedchar *)cdata, texture_width, texture_height, c - 32, &x, &y, (stbtt_aligned_quad *)&q, 1 );

		quad.add_vertex( q.x0, q.y0, 0.0f, q.s0, q.t1 ); 
		quad.add_vertex( q.x0, q.y1, 0.0f, q.s0, q.t0 );
		quad.add_vertex( q.x1, q.y0, 0.0f, q.s1, q.t1 ); 

		quad.add_vertex( q.x1, q.y1, 0.0f, q.s1, q.t0 );
		quad.add_vertex( q.x1, q.y0, 0.0f, q.s1, q.t1 ); 
		quad.add_vertex( q.x0, q.y1, 0.0f, q.s0, q.t0 );
	}

	glBindBuffer(GL_ARRAY_BUFFER, vbo );
	std::vector<Vertex> vertices = quad.get_vertices();
	glBufferData( GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW );

	glEnable( GL_BLEND );
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size() );
}