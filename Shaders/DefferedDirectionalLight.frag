#version 330 core

out vec4 FragColor;

uniform sampler2D positionTexture;
uniform sampler2D normalTexture;
uniform sampler2D albedoTexture;

in vec2 fragTexcoords;
in vec4 fragPos;

void main()
{   
    FragColor = texture(albedoTexture, fragTexcoords);
}  