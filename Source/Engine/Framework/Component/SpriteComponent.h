#pragma once
#include "RenderComponent.h"
#include "Renderer/Texture.h"
#include "Framework/Factory.h"

namespace hop
{
	class SpriteComponent : public RenderComponent
	{
	public:
		virtual const char* GetClassName() {
			return "SpriteComponent";
		} virtual void Read(const rapidjson::Value& vlaue); virtual std::unique_ptr<Object> Clone() {
			return std::make_unique<SpriteComponent>(*this);
		} class Register {
		public: Register() {
			Factory::instance().Register<SpriteComponent>("SpriteComponent");
		}
		};
		

		bool Initialize() override;
		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;



	public:
		Rect source;
		std::string textureName;
		res_t<Texture> m_texture;
	};
}