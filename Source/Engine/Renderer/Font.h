#pragma once
#include "Framework/Resource/Resource.h"
#include <string>
struct _TTF_Font;
namespace hop
{
	class Font : public Resource
	{
	public:
		Font() = default;
		Font(const std::string& filename, int fontSize);
		~Font();
		virtual bool Create(std::string filename, ...) override;
		bool Load(const std::string& filename, int fontSize);
		_TTF_Font* m_ttfFont = nullptr;
	private:

		// Inherited via Resource
	};
}
