#pragma once
#include <random>
#include "MathUtils.h"

namespace hop
{
	inline void seedRandom(unsigned int seed) { srand(seed); }
	inline int random() { return rand();}
	inline int random(unsigned int max) { return rand() % max; }
	inline int random(unsigned int min, unsigned int max) { return min + random((max - min) + 1); }

	inline float randomf() { return random() / (float)RAND_MAX; }
	inline float randomf(float max) { return randomf() * max; }
	inline float randomf(float min, float max) { return min + randomf(max-min); }
	inline float randomDir() {
		int temp = random(4);
		switch (temp) {
		case 0:
			return halfPi;
		case 1:
			return PI;
		case 2:
			return halfPi + PI;
		case 3:
			return TwoPi;
		}
	};
}