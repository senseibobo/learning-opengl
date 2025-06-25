#version 330 core

out vec4 FragColor;

struct Light {
    vec4 position; // w=1-point, w=0-directional
    vec4 color;    // rgb and a-intensity
    vec4 direction;
    vec4 params;    // x-type, y-radius, z-, w- something else
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

void main()
{
	FragColor = vec4(1.0);
}