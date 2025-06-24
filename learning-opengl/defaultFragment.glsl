#version 330 core

in vec2 UV;
in vec3 Normal;
out vec4 FragColor;

uniform sampler2D myTexture;
uniform sampler2D otherTexture;

void main()
{
	FragColor = mix(texture(myTexture, UV), 
					texture(otherTexture,UV), 0.5);
}