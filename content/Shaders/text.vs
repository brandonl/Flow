#version 330 core

// Input vertex data, different for all executions of this shader.
layout( location = 0 ) in vec3 in_position;
layout( location = 1 ) in vec3 in_normal;
layout( location = 2 ) in vec2 in_tex0;
layout( location = 3 ) in vec4 in_color;

// Output data ; will be interpolated for each fragment.
out vec2 UV;

void main(){

	// Output position of the vertex, in clip space
	// map [0..800][0..600] to [-1..1][-1..1]
	vec2 pos_homogeneous = in_position.xy - vec2(400,300); // [0..800][0..600] -> [-400..400][-300..300]
	pos_homogeneous /= vec2(400,300);
	gl_Position =  vec4(pos_homogeneous, 0, 1);
	
	// UV of the vertex. No special space for this one.
	UV = in_tex0;
}

