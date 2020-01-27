#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D shadowMap;

float LinearizeDepth(in vec2 uv)
{
    float zNear = 0.5;    // TODO: Replace by the zNear of your perspective projection
    float zFar  = 2000.0; // TODO: Replace by the zFar  of your perspective projection
    float depth = texture2D(shadowMap, uv).x;
    return (2.0 * zNear) / (zFar + zNear - depth * (zFar - zNear));
}

void main()
{ 
    float depthValue = LinearizeDepth(TexCoords);
    FragColor = vec4(vec3(depthValue), 1.0);
}