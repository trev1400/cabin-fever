#version 330 core

uniform sampler2D pos;
uniform sampler2D vel;
uniform int numParticles;
uniform float size;

out vec2 uv;

// Offsets and UVs for the triangle around the particle
const int NUM_VERTICES_PER_PARTICLE = 3;
const vec4 TRI_VERTS[NUM_VERTICES_PER_PARTICLE] = vec4[NUM_VERTICES_PER_PARTICLE](
    // TODO [Task 18] Calculate the triangle point offsets (see diagram in handout)
     vec4(0, 2, 0, 0),
     vec4(0, 0, 0, 0),
     vec4(2, 0, 0, 0)
);

void main() {
    int particleID = 0;
    int triID = 0;
    // TODO [Task 18] Which particle and triangle vertex are we dealing with?
    particleID = gl_VertexID / 3;
    triID = gl_VertexID %3;

    // Pass the tex coords to the fragment shader
    uv = TRI_VERTS[triID].xy;

    vec4 posTime = vec4(0,0,0,1);
    vec4 velAge = vec4(0);
    // TODO [Task 18] sample pos and vel textures
    posTime = texelFetch(pos, ivec2(particleID,0), 0);
    velAge = texelFetch(vel, ivec2(particleID,0), 0);

    // Calculate diameter based on age and lifetime
    float diameter = size/10;
    diameter *= min(min(1.0, velAge.w / (0.1 * posTime.w)),
                    min(1.0, abs(posTime.w - velAge.w) / (0.1 * posTime.w)));


    // the offset to the points of the triangle
    vec4 triPos = diameter * TRI_VERTS[triID];

    // anchor point in clip space
    vec4 anchorPoint = vec4(posTime.xyz, 1.0);

    // Center the particle around anchorPoint
    gl_Position = anchorPoint + triPos - diameter * vec4(0.5, 0.5, 0.0, 0.0);
}
