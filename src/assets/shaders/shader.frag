#version 310 es
#ifdef GL_ES
    precision highp float;
#endif

uniform sampler2D tex;

in vec2 fragTexCoord;

out vec4 outputColor;

void main() {
    outputColor = texture(tex, fragTexCoord);
}