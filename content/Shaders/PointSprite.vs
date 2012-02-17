#version 410

layout( location = 0 ) in vec4 inPosition;
layout( location = 1 ) in vec3 inNormal;
layout( location = 2 ) in vec2 inTex0;
layout( location = 3 ) in vec4 inColor;


uniform mat4   mvp;
uniform float  deltaT;

out vec4 pointSprCol;

void main(void) 
    {
    vec4 tmpPosition = inPosition;
    pointSprCol = inColor;
    
    // Offset by running time, makes it move closer
    tmpPosition.z += deltaT;
    
    // If out of range, adjust
    if(tmpPosition.z > -1.0)
        tmpPosition.z -= 999.0;

    gl_PointSize = 30.0 + (tmpPosition.z / sqrt(-tmpPosition.z));

    // If they are very small, fade them up
    if(g l_PointSize < 4.0 )
        pointSprCol = smoothstep( 0.0, 4.0, gl_PointSize ) * pointSprCol;


    // Don't forget to transform the geometry!
    gl_Position = mvp * tmpPosition;
    }
