#version 330 core

uniform float firstPass;
uniform sampler2D prevPos;
uniform sampler2D prevVel;
uniform int numParticles;
uniform float gravity;

// output from quad.vert
in vec2 uv;

// TODO [Task 15] setup the output locations
layout(location = 0) out vec4 pos;
layout(location = 1) out vec4 vel;

const float PI = 3.14159;
const float dt = 0.0167; // 1 sec/60 fps

/*
    A particle has the following properties:
        - pos.xyz = clip space position
        - pos.w = lifetime in seconds (doesn't change)
        - vel.xyz = clip space velocity
        - vel.w = current age in seconds
*/

// A helpful procedural "random" number generator
float hash(float n) { return fract(sin(n)*753.5453123); }

// Helper functions to procedurally generate lifetimes and initial velocities
// based on particle index
float calculateLifetime(int index) {
//    const float MAX_LIFETIME = 15.0;
//    const float MIN_LIFETIME = 8;
//    return MIN_LIFETIME + (MAX_LIFETIME - MIN_LIFETIME) * hash(index * 2349.2693);
    return 20.0;
}

vec2 calculateInitialVelocity(int index) {
    float theta = PI * hash(index * 872.0238);
    const float MAX_VEL = 0.3;
    float velMag = MAX_VEL * hash(index * 98723.345);
    return velMag * vec2(cos(theta), sin(theta));
}

vec4 initPosition(int index) {
    float x = hash(index) * 2 - 1;
    vec3 spawn = vec3(x, 1, 0);
    return vec4(spawn, calculateLifetime(index));
}

vec4 initVelocity(int index) {
    return vec4(0, -gravity, 0, 0);
}

vec4 updatePosition(int index) {
    vec4 pPos = texture(prevPos, uv);
    vec4 pVel = texture(prevVel, uv);
    vec4 xyz = pPos + pVel * dt;
    return vec4(xyz.xyz, pPos.w);
}

vec4 updateVelocity(int index) {
    vec4 pVel = texture(prevVel, uv);
    return vec4(pVel.x, -gravity, pVel.z, pVel.w + (dt * gravity * 10)) ;
}

void main() {
    int index = int(uv.x * numParticles);
    if (firstPass > 0.5) {
        pos = initPosition(index);
        float rand = hash(index * 2349.2693) * 10;
        pos.y += rand;
        pos.w += rand * 10;
        vel = initVelocity(index);
    } else {
        pos = updatePosition(index);
        vel = updateVelocity(index);

        if (pos.w < vel.w) {
            pos = initPosition(index);
            vel = initVelocity(index);
        }
    }
}
