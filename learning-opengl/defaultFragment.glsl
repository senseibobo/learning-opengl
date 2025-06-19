#version 330 core

in vec2 UV;
out vec4 FragColor;

void main()
{
	FragColor = vec4(UV.x,UV.y,0.8,1.0);
}