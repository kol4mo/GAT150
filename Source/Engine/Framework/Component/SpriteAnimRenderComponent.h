#pragma once
#include "SpriteComponent.h"

namespace hop
{
	class SpriteAnimRenderComponent : public SpriteComponent
	{
	public:
		struct AnimSequence
		{
			std::string name;

			float fps = 0;
			int numColumns = 0;
			int numRows = 0;

			int startFrame = 0;
			int endFrame = 0;

			bool loop = true;

			std::shared_ptr<Texture> texture;
		};
	public:

		virtual const char* GetClassName() {
			return "SpriteAnimRenderComponent";
		} 
		virtual void Read(const rapidjson::Value& value);
		virtual std::unique_ptr<Object> Clone() {
			return std::make_unique<SpriteAnimRenderComponent>(*this);
		} 
		class Register {
		public: Register() {
			Factory::instance().Register<SpriteAnimRenderComponent>("SpriteAnimRenderComponent");
		}
		};


		bool Initialize() override;
		void Update(float dt) override;

		void SetSequence(const std::string& name);
		void UpdateSource();


	public:
		int frame = 0;
		float frameTimer = 0;
	private:
		std::string defaultSequenceName;
		std::map<std::string, AnimSequence> m_sequences;
		AnimSequence* m_sequence = nullptr;
	};
}