#version 400

varying vec2 texture;

uniform sampler2D tex_unit0;

void main(void)
{
	gl_FragColor = texture2D( tex_unit0, texture );
}