#version 410

layout( location = 0 ) in vec3 inPosition;
layout( location = 1 ) in vec2 inTexCoord0;
layout( location = 2 ) in vec4 inColor;
layout( location = 3 ) in vec3 inNormal;

smooth out vec4 colors;

void main(void)
{
	colors = inColor;
	
	gl_Position = vec4( inPosition, 1.0 );
}