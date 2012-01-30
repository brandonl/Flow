// Simple Cell Shading
#version 400

layout( location = 0 ) in vec3 in_position;
layout( location = 1 ) in vec3 in_normal;
layout( location = 2 ) in vec2 in_tex0;
layout( location = 3 ) in vec4 in_color;

varying vec2 uv;
out vec4 ex_color;

uniform mat4	mvp_matrix;
uniform mat4	mv_matrix;

void main(void) 
{ 
	mat3 normal_matrix;
	normal_matrix[0] = normalize( mv_matrix[0].xyz );
	normal_matrix[1] = normalize( mv_matrix[1].xyz );
	normal_matrix[2] = normalize( mv_matrix[2].xyz );
	
    // Get surface normal in eye coordinates
    vec3 eye_normal = normal_matrix * in_normal;

    // Get vertex position in eye coordinates
    vec4 position = mv_matrix * vec4( in_position, 1.0f );
    vec3 position3 = position.xyz / position.w;

    // Get vector to light source
	vec3 default_light_dir = vec3( 0.0, 0.0, 1.0 ); 
    vec3 light_direction = normalize( default_light_dir - position3 );

    // Dot product gives us diffuse intensity
    float f_dot = max( 0.0, dot( eye_normal, light_direction ) );
	ex_color.rgb = in_color.rgb * f_dot;
	ex_color.a = in_color.a;
	
	uv = in_tex0;
	
    // Don't forget to transform the geometry!
    gl_Position = mvp_matrix * vec4( in_position, 1.0f );
}