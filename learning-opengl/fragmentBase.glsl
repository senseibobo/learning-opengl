#version 330 core

in vec3 Normal;
in vec2 UV;
in vec3 FragPos;

out vec4 FragColor;

#define TYPE_POINT 0.0
#define TYPE_DIRECTIONAL 1.0
#define TYPE_SPOT 2.0

struct Light {
    vec4 position; // w=1-point, w=0-directional
    vec4 color;    // rgb and a-intensity
    vec4 direction;
    vec4 params;    // x-type
};

uniform Lights {
	int lightCount;
	Light lights[16];
};

uniform Camera {
	vec4 viewPos;
	vec4 viewDir;
	mat4 view;
	mat4 projection;
};