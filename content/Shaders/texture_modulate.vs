#version 400

layout( location = 0 ) in vec3 in_position;
layout( location = 1 ) in vec3 in_normal;
layout( location = 2 ) in vec2 in_tex0;
layout( location = 3 ) in vec4 in_color;

varying vec2 texture;
uniform mat4 mvp_transform;

out vec4 ex_color;

void main()
{
	ex_color = in_color;
	texture =  in_tex0;
	gl_Position = mvp_transform * vec4( in_position, 1.0f );
}
