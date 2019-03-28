#version 410

in vec3 Color;
// layout (location=0) 
out vec4 FragColor;

void main() {
    FragColor = vec4(0.2f, 0.5f, 0.6f, 1.0f);//vec4(Color, 1.0);
}
