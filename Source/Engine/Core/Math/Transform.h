#pragma once
#include "core/core.h"
#include "Matrix22.h"
#include "Matrix33.h"
#include"core/Json.h"

namespace hop
{
	class Transform
	{
	public:
		vec2 position;
		float rotation;
		float scale = 1;

	public:
		Transform() = default;
		Transform(const vec2& position, float  rotation, float scale) :
			position{ position },
			rotation{ rotation },
			scale{ scale } {}

		mat3 GetMatrix() const {
			mat3 ms = mat3::CreateScale(scale);
			mat3 mr = mat3::CreateRotation(rotation);
			mat3 mt = mat3::CreateTranslation(position);
			return mt * ms * mr;
		}

		void Read(const json_t& value);

	};
}