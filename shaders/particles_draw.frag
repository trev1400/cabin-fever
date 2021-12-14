#version 330 core

in vec2 uv;

out vec4 fragColor;

void main() {
    if (length(uv - 0.5) < 0.5) {
        fragColor = vec4(1.f);
    } else {
        discard;
    }
}
