#version 410

in vec3 Color;
layout (location=0) out vec4 FragColor;

void main() {
    FragColor = vec4( 1, 0, 0 , 1);//vec4(Color, 1.0);
}
