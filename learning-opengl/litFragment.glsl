#version 330 core
in vec3 Normal;
in vec2 UV;
in vec3 FragPos;

out vec4 FragColor;

uniform sampler2D myTexture;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
	float ambientStrength = 0.1;
	vec3 textureColor = texture(myTexture, UV).rgb;

	vec3 resultColor = textureColor;
	resultColor *= lightColor * ambientStrength;
	
	vec3 direction = normalize(lightPos - FragPos);
	float dotProduct = dot(direction, Normal);
	resultColor = mix(resultColor, textureColor*lightColor, clamp(dotProduct,0.0,1.0));

	FragColor = vec4(resultColor.xyz, 1.0);
}