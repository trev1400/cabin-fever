#version 330 core

uniform mat4 model, view, projection;

// Scene lights
const vec3 lights[] = vec3[](
        // 1: Front upper right of room
        vec3(12, 6, -12),
        // 2: Front upper left of room
        vec3(-12, 6, -12),
        // 3: Front lower left of room
        vec3(-40, -20, -40),
        // 4: Back upper right of room
        vec3(-12, 6, 12),
        // 5: Back upper left of room
        vec3(12, 6, 12),
        // 6: Left upper middle of room
        vec3(-20, 6, 0),
        // 7: Left lower middle of room
        vec3(-20, -6, 0),
        // 8: Right upper middle of room
        vec3(20, 6, 0),
        // 9: Right lower middle of room
        vec3(20, -6, 0),
        // 10: Back middle left of room
        vec3(15, 2, 20),
        // 11: Back middle right of room
        vec3(-15, 2, 20),
        // 14: Back upper middle of room
        vec3(0, 6, 20),
        // 15: Back lower middle of room
        vec3(0, -6, 15),
        // 16: Center ceiling of room
        vec3(0, 12, 0),
        // 17: Center floor of room
        vec3(0, -12, 0),
        // 18: Outside cabin middle of sky
        vec3(0, 15, -25),
        // 19: Outside cabin right in front
        vec3(3, -3, -15),
        // 20: Back floor of room
        vec3(0, -12, 6));

// Scene light colors
const vec4 lightColors[] = vec4[](
        // 1: Front upper right of room
        vec4(1, 1, 1, 1),
        // 2: Front upper left of room
        vec4(1, 1, 1, 1),
        // 3: Front lower left of room
        vec4(1, 1, 1, 1),
        // 4: Back upper right of room
        vec4(1, 1, 1, 1),
        // 5: Back upper left of room
        vec4(1, 1, 1, 1),
        // 6: Left upper middle of room
        vec4(1, 1, 1, 1),
        // 7: Left lower middle of room
        vec4(0.5, 0.5, 0.5, 1),
        // 8: Right upper middle of room
        vec4(1, 1, 1, 1),
        // 9: Right lower middle of room
        vec4(0.5, 0.5, 0.5, 1),
        // 10: Back middle left of room
        vec4(1, 1, 1, 1),
        // 11: Back middle right of room
        vec4(1, 1, 1, 1),
        // 14: Back upper middle of room
        vec4(0.5, 0.5, 0.5, 1),
        // 15: Back lower middle of room
        vec4(0, 0, 0, 1),
        // 16: Center ceiling of room
        vec4(1, 1, 1, 1),
        // 17: Center floor of room
        vec4(1, 1, 1, 1),
        // 18: Outside cabin middle of sky
        vec4(1, 1, 1, 1),
        // 19: Outside cabin right in front
        vec4(1, 1, 1, 1),
        // 20: Back floor of room
        vec4(1, 1, 1, 1));

uniform float lightIntensity;

// Attenuation Properties
uniform float attQuadratic;
uniform float attLinear;
uniform float attConstant;

// Material properties
uniform vec4 color;
uniform float ambientIntensity;
uniform float diffuseIntensity;
uniform float specularIntensity;
uniform float shininess;
uniform bool hasTexture;

uniform sampler2D tex;

in vec3 CameraSpace_position; // eye-space position
in vec3 CameraSpace_normal;   // eye-space normal
in vec2 texCoord;

out vec4 fragColor;

void main(){
    vec4 ambient = color * ambientIntensity;
    vec4 texColor = texture(tex, texCoord);
    float blend = hasTexture ? 1.f : 0.f;
    vec4 diffuse = vec4(0.f);
    vec4 specular = vec4(0.f);

    if (texColor.a < 0.1f) {
        fragColor = texColor;
    } else {
        for (int i = 0; i < lights.length(); i++) {
            vec3 CameraSpace_toLight = vec3(view*vec4(lights[i],1)) - CameraSpace_position;
            vec3 CameraSpace_toLight_n = normalize(CameraSpace_toLight); // normalized, camera-space vector to light
            vec3 CameraSpace_toEye_n = -normalize(CameraSpace_position); // normalized, camera-space vector to eye
            vec3 CameraSpace_normal_n = normalize(CameraSpace_normal);   // normalized, camera-space normal

            float d = length(CameraSpace_toLight);
            float att = min(1 / (attConstant + attLinear * d + attQuadratic * (d * d)), 1.f);
            float surfaceLight = max(0, dot(CameraSpace_normal_n, CameraSpace_toLight_n));

            diffuse += lightIntensity * lightColors[i] * att * ((blend * texColor * surfaceLight) + ((1 - blend) * color * diffuseIntensity * surfaceLight));
            specular += lightIntensity * att * (color * lightColors[i] * specularIntensity * pow(max(0, dot(CameraSpace_toEye_n, reflect(-CameraSpace_toLight_n, CameraSpace_normal_n))), shininess));
        }

        fragColor = clamp(ambient + diffuse + specular, 0.f, 1.f);
    }
}
