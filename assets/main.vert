#version 330 core

layout(location = 0) in vec3 vertPos;
layout(location = 1) in vec3 vertNorm;
layout(location = 2)in vec2 vertUV;

out vec2 fragUV;

void main() {
    gl_Position = vec4(vertPos.x, vertPos.y, vertPos.z, 1.0);
    fragUV = vertUV;
}