#version 330 core

in vec3 Normal;
in vec2 UV;
in vec3 FragPos;

out vec4 FragColor;

uniform sampler2D myTexture;

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

vec3 calculateLighting(Light light)
{
	float radius = light.params[1];

	vec3 posDifference = vec3(light.position) - FragPos;
	vec3 lightDirection = normalize(posDifference);
	vec3 viewDirection = normalize(viewPos.xyz - FragPos);
	
	// ambient
	vec3 ambient = light.color.rgb * 0.05;

	// diffuse
	float diff = max(dot(lightDirection, Normal),0.0);
	vec3 diffuse = light.color.rgb * diff;

	// specular
	float spec = pow(max(dot(viewDirection, reflect(-lightDirection, Normal)),0.0),32.0);
	vec3 specular = light.color.rgb * spec;

	// radius stuff
	float dist = length(posDifference);
	float attenuation = max(1.0-dist/radius,0.0);

	return (ambient+diffuse+specular) * light.color.a * attenuation;
}


void main()
{
	float ambientStrength = 0.1;
	vec3 textureColor = texture(myTexture, UV).rgb;

	vec3 resultColor = vec3(0.0);
	for(int i = 0; i < lightCount; i++) 
	{
		resultColor += calculateLighting(lights[i]);
	}
	
	resultColor *= textureColor;
	FragColor = vec4(resultColor,1.0);
}