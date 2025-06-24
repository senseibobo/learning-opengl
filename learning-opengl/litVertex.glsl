#version 330 core

layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aNormal;
layout(location=2) in vec2 aUV;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Pos;
out vec3 Normal;
out vec2 UV;

void main()
{
	gl_Position = projection * view * model * vec4(aPos.xyz, 1.0);
	Normal = aNormal;
	UV = aUV;
}