#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aUV;

out vec2 UV;
out vec3 Pos;
out vec3 Normal;

uniform float time;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vec4 resultPosition = vec4(aPos.xyz,1.0f);
	//resultPosition.x += mod(time,1.0);
	resultPosition = model * resultPosition;
	resultPosition = view * resultPosition;
	resultPosition = projection * resultPosition;
	gl_Position = resultPosition;
	UV = aUV;
	Normal = aNormal;
	Pos = gl_Position.xyz;
}