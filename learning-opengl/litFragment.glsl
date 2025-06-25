struct MaterialInfo {
	vec3 albedo;
	float roughness;
	float specular;
	sampler2D albedoMap;
	sampler2D roughnessMap;
	sampler2D specularMap;
};


uniform MaterialInfo material;


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
	float roughness = material.roughness * texture(material.roughnessMap, UV).r;
	float shininess = 1.0/(0.01+0.99*roughness);
	float spec = pow(max(dot(viewDirection, reflect(-lightDirection, Normal)),0.0),shininess);
	spec *= material.specular * texture(material.specularMap, UV).r;
	vec3 specular = light.color.rgb * spec;

	// radius stuff
	float dist = length(posDifference);
	float attenuation = max(1.0-dist/radius,0.0);

	return (ambient+diffuse+specular) * light.color.a * attenuation;
}


void main()
{
	float ambientStrength = 0.1;

	vec3 resultColor = vec3(0.0);
	for(int i = 0; i < lightCount; i++) 
	{
		resultColor += calculateLighting(lights[i]);
	}
	
	resultColor *= material.albedo * texture(material.albedoMap, UV).rgb;
	FragColor = vec4(resultColor,1.0);
}