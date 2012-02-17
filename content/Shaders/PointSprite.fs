#version 410

out vec4 fragCol;

in vec4 pointSprCol;

uniform sampler2D  pointSpr;

void main(void)
{ 
    fragCol = texture( pointSpr, gl_PointCoord ) * pointSprCol;
}
    