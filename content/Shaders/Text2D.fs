#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;

// Ouput data
out vec4 color;

// Values that stay constant for the whole mesh.
uniform sampler2D texture_sample;
uniform vec4 textColor = vec4( 1, 1, 1, 1 );

void main(){
	// Stupid font loader loads fonts as black, convert to white so we can color...
	color = textColor * ( vec4(1,1,1,0) + texture2D( texture_sample, UV ) );
	
	
}