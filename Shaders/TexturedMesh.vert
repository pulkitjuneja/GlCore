#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 vert_normal;
out vec2 vert_texCoords;
out vec3 fragPos;

void main() {
	vec4 homogenousVertexPosition = vec4(position.x, position.y, position.z, 1.0);
	vert_normal = mat3(inverse(transpose(modelMatrix)))*normal;
	vert_texCoords = texCoords;
	fragPos = vec3(modelMatrix* homogenousVertexPosition);
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * homogenousVertexPosition;
}
