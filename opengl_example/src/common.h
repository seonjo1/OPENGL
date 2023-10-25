#ifndef __COMMON_H__
#define __COMMON_H__

#include <memory>
#include <string>
#include <optional>
#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define CLASS_PTR(klassName) \
class klassName; \
using klassName ## UPtr = std::unique_ptr<klassName>; \
using klassName ## Ptr = std::shared_ptr<klassName>; \
using klassName ## WPtr = std::weak_ptr<klassName>;

/*
CLASS_PTR(Shader); 를 쓰면
class Shader;
using ShaderUPtr = std::unique_ptr<Shader>;
using ShaderPtr = std::shared_ptr<Shader>;
using ShaderWPtr = std::weak_ptr<Shader>;
위의 내용이 적용됨
*/

std::optional<std::string> LoadTextFile(const std::string& filename);
// optional은 값이 있는경우 string을 쓰고 값이 없으면 못꺼내는 것을 나타냄
// string*로 할당하면서 에러시 nullptr을 반환할 수도 있지만 
// 할당을 하는 자체가 free해야하는 수고가 들기 때문에
// optional을 사용하는 것이 유리함
#endif