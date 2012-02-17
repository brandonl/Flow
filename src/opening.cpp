#include <GL/glew.h>

#include "Core/Input.h"
#include "Core/Window.h"
#include "Core/Debug.h"
#include "Opening.h"
#include "OBJLoader.h"
#include "Indexer.h"
#include "Core/Shapes.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace std;
using namespace glm;

Opening::Opening() 
	:	Scene(),
		vbo( GL_ARRAY_BUFFER ),
		ibo( GL_ELEMENT_ARRAY_BUFFER ),
		vboFloor( GL_ARRAY_BUFFER )
{
}

Opening::~Opening()
{
}

void Opening::init()
{
	//obj::import( "../../content/Models/Dragon.obj", obj.mesh );
	shape::build_torus( 4.0f, 2.0f, 40, 40, obj.mesh );
	obj.indexes = indexer::compute( obj.mesh );
	indexer::findMinMax( obj.indexes, obj.minix, obj.maxix );


	vao.alloc();
	vbo.alloc( obj.mesh.vertices() );
	ibo.alloc( obj.indexes );	

	glVertexAttribPointer( Shader::ATTRIBUTE_POS,		3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)0 );
	glVertexAttribPointer( Shader::ATTRIBUTE_NORMAL,	3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, normal) );
	glVertexAttribPointer( Shader::ATTRIBUTE_TEX0,		2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, tex0) );
	glVertexAttribPointer( Shader::ATTRIBUTE_COLOR,		4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, color) );
	for( unsigned int i = 0; i <= Shader::ATTRIBUTE_COLOR; ++i ) glEnableVertexAttribArray( i );


	s1.load( "../../content/Shaders/Bump" );
	s2.load( "../../content/Shaders/ADSPhongTextured" );
	obj.shader = &s2;

	glActiveTexture(GL_TEXTURE0);
	obj.texture.load( "../../content/Textures/StoneWall.tga", 0 );
	
	glActiveTexture(GL_TEXTURE1);
	obj.bumpMap.load( "../../content/Textures/StoneWallNorm.tga", 0 );


	/* CELL SHADING
	glGenTextures(1, &texture1D);
	glBindTexture(GL_TEXTURE_1D, texture1D);

	GLubyte textureData[4][3] = { 32,  16, 1,
												64, 32, 1,
												128, 64, 1,
												255, 128, 1};

	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, 4, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	*/

	// Reset State

	vao.unbind();
	vbo.unbind();
	ibo.unbind();
	////////////////////////
	vaoFloor.alloc();

	glActiveTexture(GL_TEXTURE0);
	floorTexture.load( "../../content/Textures/grass.tga", 0 );

	obj::import( "../../content/Models/quad.obj", floorMesh );
	vboFloor.alloc( floorMesh.vertices() );

	glVertexAttribPointer( Shader::ATTRIBUTE_POS,		3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)0 );
	glVertexAttribPointer( Shader::ATTRIBUTE_NORMAL,	3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, normal) );
	glVertexAttribPointer( Shader::ATTRIBUTE_TEX0,		2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, tex0) );
	glVertexAttribPointer( Shader::ATTRIBUTE_COLOR,		4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, color) );
	for( unsigned int i = 0; i <= Shader::ATTRIBUTE_COLOR; ++i ) glEnableVertexAttribArray( i );

	vaoFloor.unbind();
	vboFloor.unbind();
}

void Opening::update()
{
}

void Opening::draw()
{
		obj.shader->use();

		obj.shader->set_int( "colorMap", 0 );
		obj.shader->set_int( "normalMap", 1 );
		obj.shader->set_vec3( "lightPos", vec3( -100.0f, 100.0f, 100.0f ) );
		obj.shader->set_vec4( "ambientCol", vec4( 0.2f, 0.2f, 0.2f, 1.0f ) );
		obj.shader->set_vec4( "diffuseCol", vec4( 1.0f, 1.0f, 1.0f, 1.0f ) );
		obj.shader->set_vec4( "specularCol", vec4( 1.0f, 1.0f, 1.0f, 1.0f ) );


	App::model_view().save();

		vao.bind();
		glActiveTexture(GL_TEXTURE0);
		obj.texture.bind();
		glActiveTexture(GL_TEXTURE1);
		obj.bumpMap.bind();

		if( Input::is_key_pressed( 'Z' ) )
			obj.shader = ( obj.shader == &s1 ) ? &s2 : &s1;

		obj.shader->set_mat4( "mvp", App::projection().top() * App::model_view().top() );
		obj.shader->set_mat4( "mv", App::model_view().top() );
		obj.shader->set_mat3( "surfaceNorm", mat3( App::model_view().top() ) );	// Decompose mvp into rotation mat ( or normal matrix )

		// Draw Model
		glDrawRangeElements(	GL_TRIANGLES, obj.minix, obj.maxix, obj.indexes.size(), GL_UNSIGNED_SHORT, (const GLvoid*)0 );

		// Reset State
		vao.unbind();
		obj.shader->detach();
		obj.texture.unbind();

	App::model_view().restore();

}