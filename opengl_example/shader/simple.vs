#version 330 core // 3.3에서부터 실행 가능하다는 뜻

layout (location = 0) in vec3 aPos; // 0번째 attribute가 정점의 위치
// location = n : VAO attribute = n 을 나타냄, aPos 에 정점이 1개씩 들어옴

uniform mat4 transform;

void main() {
	gl_Position = transform * vec4(aPos, 1.0);
}
