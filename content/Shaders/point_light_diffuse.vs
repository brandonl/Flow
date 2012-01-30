#version 400

layout( location = 0 ) in vec3 in_position;
layout( location = 1 ) in vec3 in_normal;
layout( location = 2 ) in vec2 in_tex0;
layout( location = 3 ) in vec4 in_color;

uniform mat4 mv_matrix;
uniform mat4 p_matrix;
uniform vec3 light_pos;

out vec4 ex_color;

void main(void) 
{ 
	 mat3 normal_matrix;
	 normal_matrix[0] = normalize( mv_matrix[0].xyz );
	 normal_matrix[1] = normalize( mv_matrix[1].xyz );
	 normal_matrix[2] = normalize( mv_matrix[2].xyz );
	 vec3 norm = normalize( normal_matrix * in_normal );
	 vec4 ec_position;
	 vec3 ec_position3;
	 ec_position = mv_matrix * vec4( in_position, 1.0f );
	 ec_position3 = ec_position.xyz / ec_position.w;
	 vec3 light_dir = normalize( light_pos - ec_position3 );
	 float f_dot = max( 0.0, dot( norm, light_dir ) ); 
	 ex_color.rgb = in_color.rgb * f_dot;
	 ex_color.a = in_color.a;
	 mat4 mvp_matrix;
	 mvp_matrix = mv_matrix * p_matrix;
	 gl_Position = mvp_matrix * vec4( in_position, 1.0f ); 
}