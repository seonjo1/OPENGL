#version 330 core
// 3.3에서부터 실행 가능하다는 뜻
layout (location = 0) in vec3 aPos;

void main() {
	gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
}
