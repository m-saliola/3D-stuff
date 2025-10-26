#shader vertex
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

out vec3 v_Normal;
out vec3 v_FragPos;

void main() {
    vec4 worldPos = u_Model * vec4(position, 1.0);
    v_FragPos = worldPos.xyz;

    v_Normal = mat3(transpose(inverse(u_Model))) * normal;

    gl_Position = u_Proj * u_View * worldPos;
}

#shader fragment
#version 330 core

in vec3 v_Normal;
in vec3 v_FragPos;

uniform vec4 u_Color;
uniform vec3 u_LightPos;
uniform float u_MinBrightness;

layout (location = 0) out vec4 color;

void main() {
    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(u_LightPos - v_FragPos);

    float diff = max(dot(norm, lightDir), u_MinBrightness);

    color = vec4(diff * vec3(1.0, 1.0, 1.0) * u_Color.xyz, 1.0);
}
