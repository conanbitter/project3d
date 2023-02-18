#version 330 core

layout(location = 0) in vec3 vertPos;
layout(location = 1) in vec3 vertNorm;
layout(location = 2)in vec2 vertUV;

uniform mat4 mvp;

out vec2 fragUV;
out vec4 fragNorm;

void main() {
    gl_Position = mvp * vec4(vertPos, 1.0);
    fragUV = vertUV;
    fragNorm = mvp * vec4(vertNorm, 1.0);
}