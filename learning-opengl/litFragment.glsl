#version 330 core
in vec3 Pos;
in vec3 Normal;
in vec2 UV;

out vec4 FragColor;

uniform sampler2D myTexture;
uniform vec3 lightColor;

void main()
{
	float ambientStrength = 0.1;
	vec3 resultColor = texture(myTexture, UV).rgb;
	resultColor *= lightColor * ambientStrength;
	FragColor = vec4(Normal,1.0);
}