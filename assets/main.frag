#version 330 core

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;

in vec2 fragUV;
in vec3 fragNorm;
in vec3 fragTang;
in vec3 fragBitang;
in vec3 fragPos;
in mat3 tbn;

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

    vec3 tangentNorm = texture(normalMap, fragUV).rgb * 2.0 - 1.0;
    
    vec3 norm = normalize(fragNorm);
    vec3 tang = normalize(fragTang);
    vec3 bitang = normalize(fragBitang);

    //norm = tangentNorm.x*tang + tangentNorm.y*bitang + tangentNorm.z*norm;
    norm = normalize(tbn * tangentNorm);

    vec3 lightDir = normalize(lightPosition - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 viewDir = normalize(eyePosition - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular =  specularStrength * spec * lightColor;

    vec3 color = materialColor * (ambient + diffuse + specular);//vec3(texture(diffuseMap, fragUV))
    //outputColor = texture(diffuseMap, fragUV)*texture(normalMap, fragUV);
    outputColor = vec4(color, 1.0);
    //outputColor = texture(diffuseMap, fragUV);
}