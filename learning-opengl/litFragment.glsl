#version 330 core

in vec3 Normal;
in vec2 UV;
in vec3 FragPos;

out vec4 FragColor;

uniform sampler2D myTexture;
uniform vec3 viewPos;


struct Light {
    vec4 position;
    vec4 color;
    float radius;
    float intensity;
    float padding[2];
};

layout(std140) uniform LightBlock {
    int lightCount;
    int padding[3];
    Light lights[32];
};




void main()
{
	float ambientStrength = 0.1;
	vec3 textureColor = texture(myTexture, UV).rgb;

	vec3 resultColor = vec3(0.0);
	for(int i = 0; i < lightCount; i++) 
	{
		Light light = lights[i];

		vec3 posDifference = vec3(light.position) - FragPos;
		vec3 lightDirection = normalize(posDifference);
		vec3 viewDirection = normalize(viewPos - FragPos);
		float diff = max(dot(lightDirection, Normal),0.0);
		vec3 ambient = light.color.rgb * 1000.0;
		vec3 diffuse = light.color.rgb * diff;
		float spec = pow(max(dot(viewDirection, reflect(-lightDirection, Normal)),0.0),32.0);
		vec3 specular = light.color.rgb * spec;

		float dist = length(posDifference);
		float attenuation = max(1.0-dist/light.radius,0.0);
		resultColor += ambient;
	}
	
	resultColor *= textureColor;
	resultColor = lights[0].color.rgb;
	FragColor = vec4(resultColor,1.0);
}