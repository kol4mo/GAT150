#include "Font.h"
#include <SDL2-2.28.0/include/SDL_ttf.h>

namespace hop
{

	hop::Font::Font(const std::string& filename, int fontSize)
	{
		Load(filename, fontSize);
	}

	hop::Font::~Font()
	{
		if (m_ttfFont != nullptr)
			TTF_CloseFont(m_ttfFont);
	}

	void hop::Font::Load(const std::string& filename, int fontSize)
	{
		m_ttfFont = TTF_OpenFont(filename.c_str(), fontSize);
	}
}