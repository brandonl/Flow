#include "matrix_stack.h"
#include "debug.h"
#include <glm/gtc/matrix_transform.hpp>

Matrix_Stack::Matrix_Stack( int d )
	: depth(d), pointer(0)
{
	stack = new glm::mat4[depth];
	stack[0] = glm::mat4(1.0f);
}

Matrix_Stack::~Matrix_Stack()
{
	delete stack;
}

void Matrix_Stack::load_identity()
{
	stack[pointer] = glm::mat4(1.0f);
}

void Matrix_Stack::save()
{
	if( pointer < (depth - 1) )
	{
		pointer++;
		stack[pointer] = stack[pointer - 1];
	}
	else
		debug() << "Matrix stack overflow.\n";
}

void Matrix_Stack::restore()
{
	if( pointer > 0 )
		pointer--;
	else
		debug() << "Matrix stack underflow.\n";
}

void Matrix_Stack::modify( const glm::mat4& m )
{
	glm::mat4 temp  = stack[pointer];
	stack[pointer] = temp * m;
}

void Matrix_Stack::scale( float x, float y, float z )
{
	glm::scale( stack[pointer], glm::vec3( x, y, z ) );
}

void Matrix_Stack::translate( float x, float y, float z )
{
	glm::translate( stack[pointer], glm::vec3( x, y, z ) );
}

void Matrix_Stack::rotate( float theta, float x, float y, float z )
{
	glm::rotate( stack[pointer], theta, glm::vec3( x, y, z ) );
}

const glm::mat4& Matrix_Stack::get_matrix()
{
	return stack[pointer];
}
