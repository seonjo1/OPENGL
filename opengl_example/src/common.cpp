#include "common.h"
#include <fstream>
#include <sstream>

// 파일 로딩 함수
std::optional<std::string> LoadTextFile(const std::string& filename) {
// c++ 스타일의 파일 읽기
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        SPDLOG_ERROR("failed to open file: {}", filename);
        return {}; // 아무것도 리턴하지 않음
    }
    std::stringstream text;
    text << fin.rdbuf(); // text에 file 내용을 전부 입력
    return text.str(); // text에 들어있는 file 내용을 string으로 변환해서 반환
}