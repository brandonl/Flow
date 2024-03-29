// Cell lighting Shader
// Vertex Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
#version 130

layout( location = 0 ) in vec4 inPosition;
layout( location = 1 ) in vec3 inTexCoord0;
layout( location = 2 ) in vec2 inColor;
layout( location = 3 ) in vec4 inNormal;

smooth out float textureCoordinate;

uniform vec3	vLightPosition;
uniform mat4	mvpMatrix;
uniform mat4	mvMatrix;
uniform mat3	normalMatrix;


void main(void) 
    { 
    // Get surface normal in eye coordinates
    vec3 vEyeNormal = normalMatrix * inNormal;

    // Get vertex position in eye coordinates
    vec4 vPosition4 = mvMatrix * inPosition;
    vec3 vPosition3 = vPosition4.xyz / vPosition4.w;

    // Get vector to light source
    vec3 vLightDir = normalize(vLightPosition - vPosition3);

    // Dot product gives us diffuse intensity
    textureCoordinate = max(0.0, dot(vEyeNormal, vLightDir));

    // Don't forget to transform the geometry!
    gl_Position = mvpMatrix * inPosition;
    }