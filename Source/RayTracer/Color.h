#pragma once
#include <glm/glm.hpp>
#include<algorithm>
using color3_t = glm::vec3;
using color4_t = glm::vec4;
using rgba_t = uint32_t;
inline color4_t RGBAToColor(const rgba_t& rgba) {
	color4_t result;
	result.r = (rgba << 24)/255.0f;
	result.g = (0xff & (rgba << 16))/255.0f;
	result.b = (0xff & (rgba << 8))/255.0f;
	result.a = (0xff & (rgba << 0))/255.0f;

	return result;
}

inline rgba_t ColorToRGBA(const color4_t& color) {
	rgba_t result;
	
	result |= uint8_t(glm::clamp(color.r, 0.0f, 1.0f) * 256) << 24;
	result |= uint8_t(glm::clamp(color.g, 0.0f, 1.0f) * 256) << 16;
	result |= uint8_t(glm::clamp(color.b, 0.0f, 1.0f) * 256) << 8;
	result |= uint8_t(glm::clamp(color.r, 0.0f, 1.0f) * 256) << 0;

	return result;
}