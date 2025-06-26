struct MaterialInfo {
	vec3 albedo;
	float roughness;
	float specular;
	sampler2D albedoMap;
	sampler2D roughnessMap;
	sampler2D specularMap;
};


uniform MaterialInfo material;


vec3 calculatePointLight(Light light)
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

vec3 calculateDirectionalLight(Light light)
{
	float radius = light.params[1];

	vec3 posDifference = vec3(light.position) - FragPos;
	vec3 lightDirection = light.direction.xyz;
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

	return (ambient+diffuse+specular) * light.color.a;
}

vec3 calculateSpotLight(Light light)
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
	float cosInner = light.params[2];
	float cosOuter = light.params[3];

	float spot = dot(vec3(light.direction), lightDirection); 
	float spotAttenuation = smoothstep(cosOuter, cosInner, spot);
	
	return (ambient+(diffuse+specular) * spotAttenuation) * light.color.a * attenuation;
}

vec3 calculateLighting(Light light)
{
	float type = light.params[0];
	if(abs(type - TYPE_POINT) < 0.01) return calculatePointLight(light);
	else if(abs(type - TYPE_DIRECTIONAL) < 0.01) return calculateDirectionalLight(light);
	else if(abs(type - TYPE_SPOT) < 0.01) return calculateSpotLight(light);
	else return vec3(0.0);
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