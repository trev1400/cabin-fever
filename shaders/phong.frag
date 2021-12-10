#version 330 core

uniform mat4 model, view, projection;

// Scene lights
const vec3 lights[] = vec3[](
        // Front upper right of room
        vec3(8, 3, -9),
        // Front upper left of room
        vec3(-8, 3, -9),
        // Back upper right of room
        vec3(-8, 3, 9),
        // Back upper left of room
        vec3(8, 3, 9),
        // Left middle of room
        vec3(-8, 3, 0),
        // Right middle of room
        vec3(8, 3, 0),
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

in vec3 CameraSpace_position; // eye-space position
in vec3 CameraSpace_normal;   // eye-space normal

out vec3 fragColor;

void main(){
    vec3 ambient = color * ambientIntensity;
    vec3 diffuse = vec3(0.f);
    vec3 specular = vec3(0.f);

    for (int i = 0; i < lights.length(); i++) {
        vec3 CameraSpace_toLight = (view*vec4(lights[i],1)).xyz - CameraSpace_position;
        vec3 CameraSpace_toLight_n = normalize(CameraSpace_toLight); // normalized, camera-space vector to light
        vec3 CameraSpace_toEye_n = -normalize(CameraSpace_position); // normalized, camera-space vector to eye
        vec3 CameraSpace_normal_n = normalize(CameraSpace_normal);   // normalized, camera-space normal

        float d = length(CameraSpace_toLight);
        float att = min(1 / (attConstant + attLinear * d + attQuadratic * (d * d)), 1.f);

        diffuse += lightIntensity * att * (color * lightColor * diffuseIntensity * max(0, dot(CameraSpace_normal_n, CameraSpace_toLight_n)));
        specular += lightIntensity * att * (color * lightColor * specularIntensity * pow(max(0, dot(CameraSpace_toEye_n, reflect(-CameraSpace_toLight_n, CameraSpace_normal_n))), shininess));
    }

    fragColor = clamp(ambient + diffuse + specular, 0.f, 1.f);
}
