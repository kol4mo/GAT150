#pragma once
#include "Core/core.h"
#include "Framework/Resource/Resource.h"
#include <vector>

namespace hop
{
	class Renderer;
	class Model : public Resource
	{
	public:
		Model() = default;
		Model(const std::vector<vec2>& points) : m_points{ points } {}

		bool Load(const std::string& filename);

		void Draw(Renderer& renderer, const vec2& position, float rotation, float scale);
		void Draw(Renderer& renderer, const Transform& transform);

		float getRadius();

		virtual bool Create(std::string filename, ...) override;
	private:
		std::vector<vec2> m_points;
		Color m_color;
		float m_radius = 0;

		// Inherited via Resource
	};
}