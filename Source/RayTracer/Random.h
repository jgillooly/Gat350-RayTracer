#pragma once
#include <random>
#include <algorithm>
inline void seedRandom(unsigned int seed)
{
	srand(seed);
}

inline float random01()
{
	return rand() / float(RAND_MAX);
}

inline float random(float min, float max)
{
	if (min > max) std::swap(min, max);
	return min + random01() * (max - min);
}