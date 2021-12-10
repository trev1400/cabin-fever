#version 330 core

uniform sampler2D tex;

in vec2 texCoord;

out vec3 fragColor;

void main(){
    fragColor = vec3(texture(tex, texCoord));
}
