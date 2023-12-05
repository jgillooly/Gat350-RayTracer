#pragma once
#include <glm/glm.hpp>
#include<algorithm>
using color3_t = glm::vec3;
using color4_t = glm::vec4;
using rgba_t = uint32_t;
inline color4_t RGBAToColor(const rgba_t& rgba) {
	color4_t result;
	result.r = (rgba >> 24)/255.0f;
	result.g = (0xff & (rgba >> 16))/255.0f;
	result.b = (0xff & (rgba >> 8))/255.0f;
	result.a = (0xff & (rgba >> 0))/255.0f;

	return result;
}

inline rgba_t ColorToRGBA(const color4_t& color) {
	rgba_t result = 0;
	
	//this is for debugging :)
	uint32_t red   = uint32_t(glm::clamp(color.r, 0.0f, 1.0f) * 255) << 24;
	uint32_t green = uint32_t(glm::clamp(color.g, 0.0f, 1.0f) * 255) << 16;
	uint32_t blue  = uint32_t(glm::clamp(color.b, 0.0f, 1.0f) * 255) << 8;
	uint32_t alpha = uint32_t(glm::clamp(color.r, 0.0f, 1.0f) * 255) << 0;

	result |= uint32_t(glm::clamp(color.r, 0.0f, 1.0f) * 255) << 24;
	result |= uint32_t(glm::clamp(color.g, 0.0f, 1.0f) * 255) << 16;
	result |= uint32_t(glm::clamp(color.b, 0.0f, 1.0f) * 255) << 8;
	result |= uint32_t(glm::clamp(color.r, 0.0f, 1.0f) * 255) << 0;

	return result;
}