#pragma once
#include <cmath>
#include <sstream>

namespace hop
{
	class Vexctor2
	{
	public:
		float x, y;
	
	public:
		Vexctor2() : x{ 0 }, y{ 0 } {}
		Vexctor2(float v) : x{ v }, y{ v } {}
		Vexctor2(float x, float y) : x{ x }, y{ y } {}
		Vexctor2(int x, int y) : x{ (float)x }, y{ (float)y } {}

		Vexctor2 operator + (const Vexctor2& v) const { return Vexctor2(x + v.x, y + v.y); }
		Vexctor2 operator - (const Vexctor2& v) const { return Vexctor2(x - v.x, y - v.y); }
		Vexctor2 operator / (const Vexctor2& v) const { return Vexctor2(x / v.x, y / v.y); }
		Vexctor2 operator * (const Vexctor2& v) const { return Vexctor2(x * v.x, y * v.y); }

		Vexctor2 operator + (float s) const { return Vexctor2(x + s, y + s); }
		Vexctor2 operator - (float s) const { return Vexctor2(x - s, y - s); }
		Vexctor2 operator / (float s) const { return Vexctor2(x / s, y / s); }
		Vexctor2 operator * (float s) const { return Vexctor2(x * s, y * s); }

		Vexctor2& operator += (const Vexctor2& v) { x += v.x; y += v.y; return *this; }
		Vexctor2& operator -= (const Vexctor2& v) { x -= v.x; y -= v.y; return *this; }
		Vexctor2& operator /= (const Vexctor2& v) { x /= v.x; y /= v.y; return *this; }
		Vexctor2& operator *= (const Vexctor2& v) { x *= v.x; y *= v.y; return *this; }


		float lengthSqr() const { return (x * x) + (y * y); }
		float length() const { return sqrt(lengthSqr()); }

		float DistanceSqr(const Vexctor2& v) const { return (v - *this).lengthSqr(); }
		float Distance(const Vexctor2& v) const { return (v - *this).length(); }

		Vexctor2 Normalized() const  { return *this / length();}
		void Normalize() { *this /= length(); }

		float Angle() const { return std::atan2f(y, x); }
		Vexctor2 Rotate(float radians) const;

		static float SignedAngle(const Vexctor2& v1, const Vexctor2& v2);
		static float Angle(const Vexctor2& v1, const Vexctor2& v2);
		static float Dot(const Vexctor2& v1, const Vexctor2& v2);
	};



	inline Vexctor2 Vexctor2::Rotate(float radians) const
	{
		float _x = x * std::cos(radians) - y * std::sin(radians);
		float _y = x * std::sin(radians) + y * std::cos(radians);

		return { _x, _y };
	}

	// get the unsigned angle in radians between the normalized v1 and normalized v2
	inline float Vexctor2::Angle(const Vexctor2& v1, const Vexctor2& v2)
	{
		return std::acos(Dot(v1, v2));
	}

	// get the signed counterclockwise angle in radians between v1 and v2
	inline float Vexctor2::SignedAngle(const Vexctor2& v1, const Vexctor2& v2)
	{
		float y = v1.x * v2.y - v1.y * v2.x;
		float x = v1.x * v2.x + v1.y * v2.y;

		return std::atan2(y, x);
	}

	// get the dot product beteen v1 and v2 https://www.falstad.com/dotproduct/
	inline float Vexctor2::Dot(const Vexctor2& v1, const Vexctor2& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	inline std::istream& operator >> (std::istream& stream, Vexctor2& v)
	{
		std::string line;
		std::getline(stream, line);

		// { ##, ## }
		std::string xs = line.substr(line.find("{") + 1, line.find(",") - (line.find("{") + 1));
		v.x = std::stof(xs);

		std::string ys = line.substr(line.find(",") + 1, line.find("}") - (line.find(",") + 1));
		v.y = std::stof(ys);

		return stream;
	}

	using vec2 = Vexctor2;
}