#shader vertex
#version 330 core

layout (location = 0) in vec4 position;
layout (location = 2) in vec2 texCoord;

out vec2 v_TexCoord;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

void main() {
    gl_Position = u_Proj * u_View * u_Model * vec4(position, 1.0);
};

#shader fragment
#version 330 core

layout (location = 0) out vec4 color;

in vec2 v_TexCoord;

void main() {
    color = vec4(v_TexCoord, 0.0, 1.0);
};