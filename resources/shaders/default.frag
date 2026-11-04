#version 330

in vec4 vColor;
in vec2 vTexCoords;

out vec4 fColor;

uniform sampler2D uTex0;
uniform bool uHasTexture;

void main() {
    if (uHasTexture) {
        fColor = texture(uTex0, vTexCoords) * vColor;
    } else {
        fColor = vColor;
    }
}
