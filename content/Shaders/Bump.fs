#version 410

smooth out vec4 fragColor;

uniform vec4 ambientCol;
uniform vec4 diffuseCol;
uniform vec4 specularCol;
uniform sampler2D colorMap;
uniform sampler2D normalMap;

smooth in vec3 interpdSurfaceNorm;
smooth in vec3 interpdVec2Light;
smooth in vec2 interpdTexCoords;

void main(void)
{
	const float maxVariance = 2.0; // Mess around with this value to increase/decrease normal perturbation
	const float minVariance = maxVariance / 2.0;
 
	// Create a normal which is our standard normal + the normal map perturbation (which is going to be either positive or negative)
	vec3 normalAdjusted = interpdSurfaceNorm + normalize(texture2D(normalMap, interpdTexCoords.st).rgb * maxVariance - minVariance);
 
	float diffIntensity = max( 0.0, dot( normalize(normalAdjusted), normalize(interpdVec2Light) ) );
	// Add the diffuse contribution blended with the standard texture lookup and add in the ambient light on top
	vec3 color = (diffIntensity * diffuseCol.rgb) * texture2D(colorMap, interpdTexCoords.st).rgb + ambientCol.rgb;
 	
	//fragColor = diffIntensity * diffuseCol;
	
	fragColor = vec4( color, 1.0);
	
	//fragColor *= texture( colorMap, interpdTexCoords );
	
	vec3 reflection = normalize( reflect( -normalize( interpdVec2Light ), normalize( normalAdjusted ) ) );
	float specIntensity = max( 0.0, dot( normalize(normalAdjusted), reflection ) );
	
	if( diffIntensity != 0 )
	{
		float spec = pow( specIntensity, 128.0 );
		fragColor.rgb += vec3( spec * specularCol.rgb );
	}
}