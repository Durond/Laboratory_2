#version 460 core
out vec4 FragColor;
uniform float timeValue;

void main() {
    float r = sin(timeValue) * 0.5 + 0.5;
    float g = sin(timeValue) * 0.5 + 0.5;
    float b = 1.0; 

    FragColor = vec4(r, g, b, 1.0);
}