#include <GL3/gl3w.h>
#include "Core/Input.h"
#include "Core/Window.h"
#include "Opening.h"
#include "Core/OBJLoader.h"
#include "Core/Indexer.h"
#include "Core/Shapes.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace std;
using namespace glm;
using namespace flow;

Opening::Opening() 
	:	App( " f l 0 w " ),
		vbo( GL_ARRAY_BUFFER ),
		ibo( GL_ELEMENT_ARRAY_BUFFER )
{
}

Opening::~Opening()
{
}



void Opening::doInit()
{
	//obj::import( "../../content/Models/Dragon.obj", model.mesh );
	shape::build_cube( 1.0f, model.mesh );

	model.indexes = indexer::compute( model.mesh );
	indexer::findMinMax( model.indexes, model.minix, model.maxix );

	vao.alloc();
	vbo.alloc( model.mesh.vertices() );
	ibo.alloc( model.indexes );	

	glVertexAttribPointer( GPUProgram::ATTRIBUTE_POS,			3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)0 );
	glVertexAttribPointer( GPUProgram::ATTRIBUTE_TEXCOORD,	2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, texCoord) );
	glVertexAttribPointer( GPUProgram::ATTRIBUTE_COLOR,		4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, color) );
	glVertexAttribPointer( GPUProgram::ATTRIBUTE_NORMAL,		3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, normal) );
	for( unsigned i = 0; i <= GPUProgram::ATTRIBUTE_NORMAL; ++i ) glEnableVertexAttribArray( i );

	model.shader.load( "Shaders/ADSPhongTextured.vs", "Shaders/ADSPhongTextured.fs" );

	glActiveTexture(GL_TEXTURE0);
	model.texture.load( "Textures/bg.png" );
	
	//glActiveTexture(GL_TEXTURE1);
	//model.bumpMap.load( "Textures/StoneWallNorm.tga", 0 );


	//CELL SHADING
	//glGenTextures(1, &texture1);
	//glBindTexture(GL_TEXTURE_1D, texture1);

	//GLubyte textureData[4][3] = { 32,  16, 1,
	//											64, 32, 1,
	//											128, 64, 1,
	//											255, 128, 1};

	//glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, 4, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
	//glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

	// Reset State
	vao.unbind();
	vbo.unbind();
	ibo.unbind();
}

void Opening::doUpdate()
{
}

void Opening::doDraw()
{
	model.shader.use();

	model.shader.uniform1i( "colorMap", 0 );
	model.shader.uniform1i( "normalMap", 1 );
	model.shader.uniform3v( "lightPos", vec3( -100.0f, 100.0f, 100.0f ) );
	model.shader.uniform4v( "ambientCol", vec4( 0.2f, 0.2f, 0.2f, 1.0f ) );
	model.shader.uniform4v( "diffuseCol", vec4( 1.0f, 1.0f, 1.0f, 1.0f ) );
	model.shader.uniform4v( "specularCol", vec4( 1.0f, 1.0f, 1.0f, 1.0f ) );


	mv.save();

	vao.bind();

	glActiveTexture(GL_TEXTURE0);
	model.texture.use();

	//glActiveTexture(GL_TEXTURE1);
	//model.bumpMap.bind();

	//if( Input::isKeyPressed( 'Z' ) )
	//	model.shader = ( model.shader == &s1 ) ? &s2 : &s1;

	model.shader.uniform4m( "mvp", p.top() * mv.top() );
	model.shader.uniform4m( "mv", mv.top() );
	model.shader.uniform3m( "surfaceNorm", mat3( mv.top() ) );	// Decompose mvp into rotation mat ( or normal matrix )

	// Draw Model
	glDrawRangeElements(	GL_TRIANGLES, model.minix, model.maxix, model.indexes.size(), GL_UNSIGNED_SHORT, (const GLvoid*)0 );
	// Reset State
	vao.unbind();
	model.shader.use(0);
	model.texture.use(0);

	mv.restore();

}