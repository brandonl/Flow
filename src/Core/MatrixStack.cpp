#include "MatrixStack.h"
#include "Debug.h"
#include <glm/gtc/matrix_transform.hpp>

MatrixStack::MatrixStack( int d )
	: depth(d), pointer(0)
{
	stack = new glm::mat4[depth];
	stack[0] = glm::mat4(1.0f);
}

MatrixStack::~MatrixStack()
{
	delete stack;
}

void MatrixStack::load_identity()
{
	stack[pointer] = glm::mat4(1.0f);
}

void MatrixStack::save()
{
	if( pointer < (depth - 1) )
	{
		pointer++;
		stack[pointer] = stack[pointer - 1];
	}
	else
		debug() << "Matrix stack overflow.\n";
}

void MatrixStack::restore()
{
	if( pointer > 0 )
		pointer--;
	else
		debug() << "Matrix stack underflow.\n";
}

void MatrixStack::modify( const glm::mat4& m )
{
	glm::mat4 temp  = stack[pointer];
	stack[pointer] = temp * m;
}

void MatrixStack::scale( float x, float y, float z )
{
	glm::scale( stack[pointer], glm::vec3( x, y, z ) );
}

void MatrixStack::translate( float x, float y, float z )
{
	glm::translate( stack[pointer], glm::vec3( x, y, z ) );
}

void MatrixStack::rotate( float theta, float x, float y, float z )
{
	glm::rotate( stack[pointer], theta, glm::vec3( x, y, z ) );
}

void MatrixStack::set( const glm::mat4& m )
{
	stack[pointer] = m;
}

const glm::mat4& MatrixStack::top()
{
	return stack[pointer];
}
