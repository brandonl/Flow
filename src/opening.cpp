#include <GL/glew.h>

#include "Core/input.h"
#include "Core/window.h"
#include "Core/debug.h"
#include "opening.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace std;
using namespace glm;


#include "text2d.h"

Opening::~Opening()
{
	glUseProgram(0);
	glBindTexture( GL_TEXTURE_2D, 0 );
	glBindVertexArray( vao );
	for( unsigned int i = 0; i <= Shader::ATTRIBUTE_TEX2; ++i )
		glDisableVertexAttribArray( i );
	glBindVertexArray(0);
	glDeleteVertexArrays( 1, &vao );

	Text::clean();
}

void Opening::init()
{
	debug() << "Started scene" << endl;
	p.modify( perspective( 35.0f, 
													static_cast<float>( Window::get_width() ) / Window::get_height(), 
													0.1f, 100.0f ) );

	cam.set(	vec3( 0.0f, 0.5f, -2.0f ), 
						vec3( 0.0f, 0.5f, 0.0f ), 
						vec3( 0.0f, 1.0f, 0.0f ) );

	shape::build_sphere( 0.2f, 20, 20, obj );

	// Bind New Objects to hold State..
	glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao );
		
	vbo.alloc( obj.get_vertices() );
	ibo.alloc( obj.get_indexes() );	
	
	glVertexAttribPointer( Shader::ATTRIBUTE_POS,			3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)0 );
	glVertexAttribPointer( Shader::ATTRIBUTE_NORMAL,	3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, normal) );
	glVertexAttribPointer( Shader::ATTRIBUTE_TEX0,		2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, tex0) );
	glVertexAttribPointer( Shader::ATTRIBUTE_COLOR,		4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, color) );
	for( unsigned int i = 0; i <= Shader::ATTRIBUTE_COLOR; ++i )
		glEnableVertexAttribArray( i );

	shader.load( "../../content/Shaders/texture" );

	// Must use a program before setting uniforms otherwise error code 1282
	// Invalid Op
	glUseProgram( shader.get_name() );
	shader.set_int( "tex_unit0", 0 );

	texture.load( "../../content/Textures/Block.tga", 0 );
		
	// Reset State
	glUseProgram( 0 );
	glBindVertexArray( 0 );
	vbo.unbind();
	ibo.unbind();
	glBindTexture( GL_TEXTURE_2D, 0 );

	Text::init( "../../content/Fonts/Holstein.tga" );
}

void Opening::update()
{
	mv.set( lookAt( cam.position, cam.focus, cam.up_direction ) );
	cam.update();
}

void Opening::draw()
{
	glBindVertexArray( vao );
	glBindTexture(GL_TEXTURE_2D,  texture.get_name() );
	glUseProgram( shader.get_name() );

	mv.save();
	shader.set_mat4( "mvp_matrix", p.get_matrix() * mv.get_matrix() );
	
	//glEnable( obj.poly_mode == GL_LINE ? GL_LINE_SMOOTH : GL_POLYGON_SMOOTH );
	//glPolygonMode( GL_FRONT_AND_BACK, obj.poly_mode );

	glDrawRangeElements(	obj.mesh_type, 
												obj.get_min_index(), obj.get_max_index(),
												obj.get_index_count(),
												GL_UNSIGNED_SHORT, (const GLvoid*)0 );
	mv.restore();

	// Reset State
	glBindVertexArray( 0 );
	glUseProgram( 0 );
	glBindTexture( GL_TEXTURE_2D, 0 );

	Text::print( "FPS: ", 10, 500, 60 );
}