void main()
{
	gl_Position = projection * view * model * vec4(aPos.xyz, 1.0);
	FragPos = vec3(model * vec4(aPos.xyz,1.0));
	Normal = mat3(transpose(inverse(model)))*aNormal;
	UV = aUV;
}