#version 330 core

out vec4 FragColor;


struct Light {
    vec4 position;
    vec4 color;
    float radius;
    float intensity;
    vec2 padding;
};

layout(std140) uniform LightBlock {
    int lightCount;
    int padding[3];
    Light lights[32];
};



void main()
{
	FragColor = vec4(1.0);
}