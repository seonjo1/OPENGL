#version 330 core

uniform vec4 color; // uniform 변수
out vec4 fragColor;

void main() {
	fragColor = color;
}