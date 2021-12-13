#version 330 core

layout(location = 0) in vec3 ObjectSpace_position; // object-space vertex position
layout(location = 1) in vec3 ObjectSpace_normal;   // object-space vertex normal
layout(location = 5) in vec2 ObjectSpace_texCoord;   // object-space texture coordinate

uniform mat4 model, view, projection;

out vec2 texCoord;

void main() {
    gl_Position = projection * view * model * vec4(ObjectSpace_position, 1.0);

    texCoord = ObjectSpace_texCoord;
}
