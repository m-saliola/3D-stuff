#shader vertex
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;
uniform float u_Time;

out vec3 v_FragPos;
out vec3 v_Normal;

float getHeight(float x, float z) {
    return 0.5 * sin(x + z + u_Time * 2);
}

float getSlope(float x, float z) {
    return 0.5 * cos(x + z + u_Time * 2);
}

void main() {
    vec4 worldPos = u_Model * vec4(position, 1.0);
    worldPos.y += getHeight(worldPos.x, worldPos.z) - 2;

    v_FragPos = worldPos.xyz;

    float slope = getSlope(worldPos.x, worldPos.z);

    vec3 newNormal = normalize(vec3(-slope, 1.0, -slope));

    v_Normal = mat3(transpose(inverse(u_Model))) * newNormal;

    gl_Position = u_Proj * u_View * worldPos;
}

#shader fragment
#version 330 core

in vec3 v_FragPos;
in vec3 v_Normal;

uniform vec3 u_ViewPos;

uniform vec3 u_Color;
uniform vec3 u_AmbientColor;
uniform vec3 u_SpecularColor;
uniform vec3 u_LightPos;
uniform float u_Shininess;

layout (location = 0) out vec4 color;

void main() {
    vec3 normal = normalize(v_Normal);
    vec3 lightDir = normalize(u_LightPos - v_FragPos);

    vec3 ambient = u_AmbientColor * u_Color;
    vec3 diffuse = max(dot(normal, lightDir), 0.0) * u_Color;

    vec3 viewDir = normalize(u_ViewPos - v_FragPos);
    vec3 halfway = normalize(lightDir + viewDir);

    vec3 specular = pow(max(dot(normal, halfway), 0.0), u_Shininess) * u_SpecularColor;

    color = vec4(ambient + diffuse + specular, 1.0);
}
