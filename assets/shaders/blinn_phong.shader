#shader vertex
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

out vec3 v_FragPos;
out vec3 v_Normal;

void main() {
    vec4 worldPos = u_Model * vec4(position, 1.0);
    v_FragPos = worldPos.xyz;

    v_Normal = mat3(transpose(inverse(u_Model))) * normal;

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
uniform vec3 u_LightDir;
uniform float u_Shininess;

layout (location = 0) out vec4 color;

void main() {
    vec3 normal = normalize(v_Normal);
    // vec3 lightDir = normalize(u_LightDir - v_FragPos);

    float diffuse = max(dot(normal, normalize(u_LightDir)), 0.0);

    vec3 viewDir = normalize(u_ViewPos - v_FragPos);
    vec3 halfway = normalize((u_LightDir - v_FragPos) + viewDir);

    float specular = max(pow(dot(normal, halfway), u_Shininess), 0.0); // might be shininess

    color = vec4(u_AmbientColor + diffuse * u_Color + specular * u_SpecularColor, 1.0);
}
