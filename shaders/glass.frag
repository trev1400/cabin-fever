#version 330 core
float M_PI = 3.1415926535897932384626433832795;

in vec3 vertex;                 // The position of the vertex, in camera space!
in vec3 vertexToCamera;         // Vector from the vertex to the eye, which is the camera
in vec3 eyeNormal;	        // Normal of the vertex, in camera space!

uniform float r0;		// The R0 value to use in Schlick's approximation
uniform float eta1D;		// The eta value to use initially
uniform vec3  eta;              // Contains one eta for each channel (use eta.r, eta.g, eta.b in your code)

uniform mat4 view;
uniform mat4 model;

uniform samplerCube envMap;

out vec4 fragColor;

void main()
{
    vec3 n = normalize(eyeNormal);
    vec3 cameraToVertex = normalize(vertex); //remember we are in camera space!
    vec3 vertexToCamera = normalize(vertexToCamera);

    vec3 reflectionVec = vec3(view * vec4(reflect(cameraToVertex, n), 0));
    vec4 reflectionColor = vec4(texture(envMap, reflectionVec).rgb, 1.0);

    vec3 redRefractedVec = vec3(view * vec4(refract(cameraToVertex, n, eta.r), 0.0));
    vec3 greenRefractedVec = vec3(view * vec4(refract(cameraToVertex, n, eta.g), 0.0));
    vec3 blueRefractedVec = vec3(view * vec4(refract(cameraToVertex, n, eta.b), 0.0));

    float r = texture(envMap, redRefractedVec).r;
    float g = texture(envMap, greenRefractedVec).g;
    float b = texture(envMap, blueRefractedVec).b;

    vec4 refractionColor = vec4(r, g, b, 0.5);

    float F = (r0 + (1 - r0) * pow(1 - max(0, dot(n, vertexToCamera)), 5.0));

    fragColor = mix(refractionColor, reflectionColor, F);
}
