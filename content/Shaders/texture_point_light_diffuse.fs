#version 400

in vec4 ex_color;
out vec4 out_color;

varying vec2 texture;
uniform sampler2D tex_unit0;

void main(void)
{
	out_color = ex_color * texture2D( tex_unit0, texture );
}