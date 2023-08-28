#pragma once
#include "Component/RenderComponent.h"
#include "Renderer/Text.h"

namespace hop
{
	class TextRenderComponent : public RenderComponent
	{
	public:
		ClASS_DECLERATION(TextRenderComponent);
		TextRenderComponent() = default;
		TextRenderComponent(const TextRenderComponent& other);
		bool Initialize() override;
		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;
		void SetText(const std::string& string);
	public:
		std::string text;
		std::string fontName;	
		int fontSize = 0;
		Color color{ 1, 1, 1, 1};
	private:
		bool m_changed = true;
		std::unique_ptr<Text> m_text;
	};
}