#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

void main()
{
	vec4 vertexPosition = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    gl_Position = vertexPosition;
	TexCoords = aTexCoords;
}
