#pragma once
#include "Core/Vexctor2.h"
#include "Framework/Resource/Resource.h"

struct SDL_Texture;

namespace hop
{
	class Texture : public Resource
	{
	public:
		Texture() = default;
		~Texture();

		virtual bool Create(std::string filename, ...) override;

		bool Load( std::string filename, class Renderer& renderer);
		vec2 GetSize();

		friend class Renderer;

	private:
		SDL_Texture* m_texture = nullptr;

		// Inherited via Resource
	};
}