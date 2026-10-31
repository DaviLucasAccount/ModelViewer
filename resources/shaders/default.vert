#version 330

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aColor;

out vec4 vColor;

uniform mat4 uMVP;

void main() {
    vec4 pos = vec4(aPosition, 1.0);
    gl_Position = uMVP * pos;
    vColor = vec4(aColor, 1.0);
}
