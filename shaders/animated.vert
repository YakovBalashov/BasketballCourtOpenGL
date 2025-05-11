#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoord;

uniform int currentFrame;
uniform int frameCount;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    
    float frameWidth = 1.0f / float(frameCount);
    float offsetX = float(currentFrame) * frameWidth;

    TexCoord = aTexCoord + vec2(offsetX, 0.0f);
}
