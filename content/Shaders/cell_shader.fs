#version 400

uniform sampler2D tex_unit0;
out vec4 frag_color;
in vec4 ex_color;
varying vec2 uv;

void main(void)
{ 
   frag_color = ex_color * texture( tex_unit0, uv );
}