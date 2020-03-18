#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 lightSpaceMatrix;

out VS_OUT {
    vec3 fragPos;
    vec3 vertNormal;
    vec2 texCoords;
    vec4 fragPosLightSpace;
} vsOut;

void main() {
	vec4 homogenousVertexPosition = vec4(position, 1.0);
	vsOut.vertNormal = mat3(inverse(transpose(modelMatrix)))*normal;
	vsOut.texCoords = texCoords;
	vsOut.fragPos = vec3(modelMatrix* homogenousVertexPosition);
	vsOut.fragPosLightSpace = lightSpaceMatrix* vec4(vsOut.fragPos, 1.0);
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * homogenousVertexPosition;
}
