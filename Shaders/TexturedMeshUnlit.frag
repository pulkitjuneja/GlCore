#version 330 core
out vec4 FragColor;

in vec3 vert_normal;
in vec2 vert_texCoords;

struct Material {
	int diffuseCount;
	int specularCount;
	sampler2D texture_diffuse[5];
	sampler2D texture_specular[5];
};

uniform Material material;

void main()
{
	FragColor = texture(material.texture_diffuse[0],vert_texCoords);
}
