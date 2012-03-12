#version 410

smooth out vec4 fragColor;
smooth in vec4 colors;

void main(void)
{
	fragColor = colors;
}