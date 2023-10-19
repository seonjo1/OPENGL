#ifndef __COMMON_H__
#define __COMMON_H__

#include <memory>
#include <string>
#include <optional>
#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

std::optional<std::string> LoadTextFile(const std::string& filename);
// optional은 값이 있는경우 string을 쓰고 값이 없으면 못꺼내는 것을 나타냄
// string*로 할당하면서 에러시 nullptr을 반환할 수도 있지만 
// 할당을 하는 자체가 free해야하는 수고가 들기 때문에
// optional을 사용하는 것이 유리함
#endif