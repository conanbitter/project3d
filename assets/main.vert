#version 330 core

layout(location = 0) in vec3 vertPos;
layout(location = 1) in vec3 vertNorm;
layout(location = 2) in vec3 vertTang;
layout(location = 3) in vec2 vertUV;

uniform mat4 mvp;
uniform mat4 model;
uniform mat3 normalMat;

out vec2 fragUV;
out vec3 fragNorm;
out vec3 fragTang;
out vec3 fragBitang;
out vec3 fragPos;
out mat3 tbn;

void main() {
    gl_Position = mvp * vec4(vertPos, 1.0);
    fragUV = vertUV;
    fragNorm = normalMat * vertNorm;
    fragTang = normalMat * vertTang;
    fragBitang = cross(fragNorm, fragTang);
    tbn = mat3(fragTang, fragBitang, fragNorm);
    fragPos = vec3(model * vec4(vertPos, 1.0));
}