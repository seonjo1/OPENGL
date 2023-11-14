#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include "common.h"
#include "shader.h"

CLASS_PTR(Program)
class Program
{
public:
	static ProgramUPtr Create(const std::vector<ShaderPtr>& shaders);
	// unique pointer는 단독으로 소유권을 갖는데
	// shared pointer는 소유권을 공동을고 가질 수 있다.
	// (소유권을 갖고 있는 변수가 없을때 메모리 해제)
	// UPtr 을 Ptr로 변환하는 법
	// ShaderPtr shader = Shader::CreateFromFile();
	// but Ptr을 UPtr로 바꾸는건 어렵
		~Program();
	uint32_t Get() const {return m_program;}
	void Use() const;

	void SetUniform(const std::string&name, int value) const;
	void SetUniform(const std::string&name, float value) const;
	void SetUniform(const std::string&name, const glm::vec3& value) const;
	void SetUniform(const std::string&name, const glm::mat4& value) const;
	
private:
	Program() {}
	bool Link(const std::vector<ShaderPtr>& shaders);
	uint32_t m_program {0};
};

#endif