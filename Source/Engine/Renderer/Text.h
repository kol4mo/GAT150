#pragma once
#include "Font.h"
#include "Core/math/Color.h"
#include <string>
#include <memory>
struct SDL_Texture;
namespace hop
{
	class Renderer;

	class Text
	{
	public:
		Text() = default;
		Text(std::shared_ptr<Font> font) : m_font{ font } { }
		~Text();
		void Create(Renderer& renderer, const std::string& text, const Color& color);
		void Draw(Renderer& renderer, int x, int y);

		friend class Font;
		friend class Renderer;
	private:
		std::shared_ptr<Font> m_font;
		SDL_Texture* m_texture = nullptr;
	};
}
