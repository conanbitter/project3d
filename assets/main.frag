#version 330 core

uniform sampler2D diffuse;
uniform sampler2D normal;

in vec2 fragUV;
in vec3 fragNorm;
in vec3 fragPos;

uniform mat4 normalMat;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 materialColor;
uniform vec3 eyePosition;
uniform float ambientStregth;
uniform float specularStrength;

out vec4 outputColor;

void main() {
    vec3 ambient = ambientStregth * lightColor;
    
    vec3 norm = normalize(fragNorm);
    vec3 lightDir = normalize(lightPosition - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 viewDir = normalize(eyePosition - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular =  specularStrength * spec * lightColor;

    vec3 color = materialColor * (ambient + diffuse + specular);
    outputColor = vec4(color, 1.0);
    //outputColor = texture(diffuse, fragUV)*texture(normal, fragUV);
}