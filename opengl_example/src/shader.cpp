#include "shader.h"

ShaderUPtr Shader::CreateFromFile(const std::string& filename, GLenum shaderType) {
	auto shader = ShaderUPtr(new Shader());
	if (!shader->LoadFile(filename, shaderType))
		return nullptr;
	return std::move(shader);
}

bool Shader::LoadFile(const std::string& filename, GLenum shaderType) {
	auto result = LoadTextFile(filename);
	if (!result.has_value()) //optional 객체 값이 있는지 확인
		return false;

	auto& code = result.value();
	/*
	 == std::string& code = result.value();
		&를 사용한 이유
		- 만약 result 안에 내용이 큰 경우 굳이 복사하여 하나 더 만들면
		  메모리가 낭비되기 때문이다.
	*/
	const char* codePtr = code.c_str();
	int32_t codeLength = (int32_t)code.length();
	/*
	uint8_t = unsigned char
	int8_t = char
	uint16_t = unsigned short
	int16_t = shor
	uint32_t = unsigned int
	int32_t = int
	uint64_t = unsigned long long
	int64_t = long long
	*/

	// create and compile shader
	m_shader = glCreateShader(shaderType); // glCreateShader 는 shader를 하나 생성하는데 shader handle 번호(정수)를 반환한다.
	glShaderSource(m_shader, 1, (const GLchar* const*)&codePtr, &codeLength);
	// glShaderSource(shader handle number, 코드의 개수, 코드 const char *의 참조자, 코드 길이의 참조자)
	glCompileShader(m_shader);
	// glCompileShader : 입력한 code 를 compile해줌

	// check compile error
	int success = 0;
	glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);
	// GL_COMPILE_STATUS : 컴파일의 성공여부를 확인
	// i 는 정수, v 는 뒤에 붙여야하는 인자가 포인터라는 내용
	if (!success) {
		// 에러 출력하는 법
		char infoLog[1024];
		glGetShaderInfoLog(m_shader, 1024, nullptr, infoLog);
		SPDLOG_ERROR("failed to compile shader: \"{}\"", filename);
		SPDLOG_ERROR("reason: {}", infoLog);
		return false;
	}
	return true;
}

Shader::~Shader() {
	if (m_shader) {
		glDeleteShader(m_shader);
	}
}