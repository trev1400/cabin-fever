#version 330 core

layout(location = 0) in vec3 OS_position;
layout(location = 1) in vec3 OS_normal;

uniform mat4 model, view, projection;

out vec3 WS_position; // world-space position
out vec3 WS_normal;   // world-space normal

void main() {
    WS_position = vec3(model * vec4(OS_position, 1.0));
    WS_normal = vec3(model * vec4(OS_normal, 0.0));

    gl_Position = projection * view * vec4(WS_position, 1.0);
}
