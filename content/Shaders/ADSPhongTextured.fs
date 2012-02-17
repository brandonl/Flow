#version 410

smooth out vec4 fragColor;

uniform vec4 ambientCol;
uniform vec4 diffuseCol;
uniform vec4 specularCol;
uniform sampler2D colorMap;

smooth in vec3 interpdSurfaceNorm;
smooth in vec3 interpdVec2Light;
smooth in vec2 interpdTexCoords;

void main(void)
{
	float diffIntensity = max( 0.0, dot( normalize(interpdSurfaceNorm), normalize(interpdVec2Light) ) );
	
	fragColor = diffIntensity * diffuseCol;
	
	fragColor += ambientCol;
	
	fragColor *= texture( colorMap, interpdTexCoords );
	
	vec3 reflection = normalize( reflect( -normalize( interpdVec2Light ), normalize( interpdSurfaceNorm ) ) );
	float specIntensity = max( 0.0, dot( normalize(interpdSurfaceNorm), reflection ) );
	
	if( diffIntensity != 0 )
	{
		float spec = pow( specIntensity, 128.0 );
		fragColor.rgb += vec3( spec, spec, spec );
	}
}