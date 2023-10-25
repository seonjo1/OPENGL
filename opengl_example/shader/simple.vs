#version 330 core
// 3.3에서부터 실행 가능하다는 뜻
layout (location = 0) in vec3 aPos;
// location = n : VAO attribute = n 을 나타냄
// aPos 에 정점이 1개씩 들어옴
void main() {
	gl_Position = vec4(aPos, 1.0);
}
