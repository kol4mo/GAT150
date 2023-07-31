#pragma once
#include <string>
struct _TTF_Font;
namespace hop
{
	class Font
	{
	public:
		Font() = default;
		Font(const std::string& filename, int fontSize);
		~Font();
		void Load(const std::string& filename, int fontSize);
		_TTF_Font* m_ttfFont = nullptr;
	private:
	};
}
