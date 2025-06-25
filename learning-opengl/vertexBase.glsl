#version 330 core

layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aNormal;
layout(location=2) in vec2 aUV;

uniform mat4 model;

uniform Camera {
	vec4 viewPos;
	vec4 viewDir;
	mat4 view;
	mat4 projection;
};

out vec3 Normal;
out vec2 UV;
out vec3 FragPos;