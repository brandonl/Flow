#version 410

layout( location = 0 ) in vec3 inPosition;
layout( location = 1 ) in vec2 inTexCoord0;
layout( location = 2 ) in vec4 inColor;
layout( location = 3 ) in vec3 inNormal;

uniform mat4 mvp;
uniform mat4 mv;
uniform mat3 surfaceNorm;
uniform vec3 lightPos;

smooth out vec3 interpdSurfaceNorm;
smooth out vec3 interpdVec2Light;
smooth out vec2 interpdTexCoords;

void main(void)
{
	interpdSurfaceNorm = surfaceNorm * inNormal;
	
	vec4 pos4 = mv * vec4( inPosition, 1.0 );
	vec3 pos3 = pos4.xyz / pos4.w;
	
	interpdVec2Light = normalize( lightPos - pos3 );
	
	interpdTexCoords = inTexCoord0;
	
	gl_Position = mvp * vec4( inPosition, 1.0 );
}