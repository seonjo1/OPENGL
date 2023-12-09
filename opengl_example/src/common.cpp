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

glm::vec3 GetAttenuationCoeff(float distance) {
	// Attenuation을 구하는데 사용되는 식인데 교수님이 만든거라 굳이 설명은 안하심
	// distance를 넣으면 coeffcient값이 3개 튀어나오는 함수라 생각
	const auto linear_coeff = glm::vec4(8.4523112e-05, 4.4712582e+00, -1.8516388e+00, 3.3955811e+01);
	const auto quad_coeff = glm::vec4(-7.6103583e-04, 9.0120201e+00, -1.1618500e+01, 1.0000464e+02);

	float kc = 1.0f;
	float d = 1.0f / distance;
	auto dvec = glm::vec4(1.0f, d, d*d, d*d*d);
	float kl = glm::dot(linear_coeff, dvec);
	float kq = glm::dot(quad_coeff, dvec);

	return glm::vec3(kc, glm::max(kl, 0.0f), glm::max(kq*kq, 0.0f));
}

float RandomRange(float minValue, float maxValue)
{
	return ((float)rand() / (float)RAND_MAX) * (maxValue - minValue) + minValue;
}