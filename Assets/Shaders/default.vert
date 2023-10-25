#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

uniform mat4 transformationMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoord;
out vec3 ViewPos;

void main()
{
    Normal = aNormal;
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
    FragPos = vec3(transformationMatrix * vec4(aPos, 1.0f));
    ViewPos = inverse(viewMatrix)[3].rgb;
    gl_Position =  projectionMatrix * viewMatrix * transformationMatrix * vec4(FragPos, 1.0);
}