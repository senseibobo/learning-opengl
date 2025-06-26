#version 330 core

layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aNormal;
layout(location=2) in vec2 aUV;
layout(location=3) in vec3 aTangent;
layout(location=4) in vec3 aBitangent;

uniform mat4 model;

uniform Camera {
	vec4 viewPos;
	vec4 viewDir;
	mat4 view;
	mat4 projection;
};

out vec3 FragPos;
out vec3 Normal;
out vec2 UV;
out vec3 Tangent;
out vec3 Bitangent;