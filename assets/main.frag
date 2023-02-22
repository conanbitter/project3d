#version 330 core

uniform sampler2D diffuse;
uniform sampler2D normal;

in vec2 fragUV;
in vec4 fragNorm;

out vec4 outputColor;

void main() {
    float color = (fragNorm.x + 1.0)/2.0;
    outputColor = texture(diffuse, fragUV)*texture(normal, fragUV);//*vec4(color,color,color, 1.0);
}