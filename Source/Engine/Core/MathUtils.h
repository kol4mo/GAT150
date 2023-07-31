#pragma once
#include <cmath>

namespace hop
{
	constexpr float PI = 3.14159265359f;
	constexpr float TwoPi = PI * 2;
	constexpr float halfPi = PI / 2;
	constexpr float e = 2.71828182846f;

	constexpr float RadToDeg(float radians) { return radians * 180.0f / PI; }
	constexpr float DegToRad(float degrees) { return degrees * PI / 180.0f; }

	constexpr int Wrap(int value, int max) { return (value % max) + ((value < 0) ? max : 0);	}
	//constexpr float Wrap(float value, float max) { return fmod(value, max) + ((value < 0) ? max : 0); }

	template <typename T>
	inline T Max(T a, T b)
	{
		return (a > b) ? a : b;
	}

	template <typename T>
	inline T Min(T a, T b)
	{
		return (a < b) ? a : b;
	}

	template <typename T>
	inline T Clamp(T value, T min, T max) {
		if (min > max) std::swap(min, max);

		return (value < min) ? min : (value > max) ? max : value;
	}

	template<typename T>
	constexpr T Lerp(const T& a, const T& b, float t)
	{
		return (a * (1.0f - t)) + (b * t);
	}
}