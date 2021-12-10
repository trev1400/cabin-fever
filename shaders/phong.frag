#version 330 core

uniform mat4 model, view, projection;

// Scene lights
const vec3 lights[] = vec3[](
        // Front upper right of room
        vec3(8, 3, -9),
        // Front lower right of room
        vec3(8, -3, -9),
        // Front upper left of room
        vec3(-8, 3, -9),
        // Front upper left of room
        vec3(-8, -3, -9),
        // Back upper right of room
        vec3(-8, 3, 9),
        // Back upper right of room
        vec3(-8, -3, 9),
        // Back upper left of room
        vec3(8, 3, 9),
        // Back lower left of room
        vec3(8, -3, 9),
        // Left upper middle of room
        vec3(-8, 3, 0),
        // Left middle middle of room
        vec3(-8, 0, 0),
        // Left lower middle of room
        vec3(-8, -3, 0),
        // Right upper middle of room
        vec3(8, 3, 0),
        // Right lower middle of room
        vec3(8, 0, 0),
        // Right lower middle of room
        vec3(8, -3, 0),
        // Back upper middle of room
        vec3(0, 3, 9),
        // Back upper middle of room
        vec3(0, 0, 9),
        // Back lower middle of room
        vec3(0, -3, 9),
        // Center ceiling of room
        vec3(0, 3.5, 0),
        vec3(2, 2, -15));
uniform vec3 lightColor;
uniform float lightIntensity;

// Attenuation Properties
uniform float attQuadratic;
uniform float attLinear;
uniform float attConstant;

// Material properties
uniform vec3 color;
uniform float ambientIntensity;
uniform float diffuseIntensity;
uniform float specularIntensity;
uniform float shininess;

uniform sampler2D tex;

in vec3 CameraSpace_position; // eye-space position
in vec3 CameraSpace_normal;   // eye-space normal
in vec2 texCoord;

out vec3 fragColor;

void main(){
    vec3 ambient = color * ambientIntensity;
    vec3 texColor = vec3(texture(tex, texCoord));
    float blend = 1.f;
    vec3 diffuse = vec3(0.f);
    vec3 specular = vec3(0.f);

    for (int i = 0; i < lights.length(); i++) {
        vec3 CameraSpace_toLight = vec3(view*vec4(lights[i],1)) - CameraSpace_position;
        vec3 CameraSpace_toLight_n = normalize(CameraSpace_toLight); // normalized, camera-space vector to light
        vec3 CameraSpace_toEye_n = -normalize(CameraSpace_position); // normalized, camera-space vector to eye
        vec3 CameraSpace_normal_n = normalize(CameraSpace_normal);   // normalized, camera-space normal

        float d = length(CameraSpace_toLight);
        float att = min(1 / (attConstant + attLinear * d + attQuadratic * (d * d)), 1.f);
        float surfaceLight = max(0, dot(CameraSpace_normal_n, CameraSpace_toLight_n));

        diffuse += lightIntensity * lightColor * att * ((blend * texColor * surfaceLight) + ((1 - blend) * color * diffuseIntensity * surfaceLight));
        specular += lightIntensity * att * (color * lightColor * specularIntensity * pow(max(0, dot(CameraSpace_toEye_n, reflect(-CameraSpace_toLight_n, CameraSpace_normal_n))), shininess));
    }

    fragColor = clamp(ambient + diffuse + specular, 0.f, 1.f);

}
