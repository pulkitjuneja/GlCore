#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D shadowMap;

void main()
{ 
    float depthValue = texture2D(shadowMap, TexCoords.xy).x;
    FragColor = vec4(vec3(depthValue), 1.0);
}