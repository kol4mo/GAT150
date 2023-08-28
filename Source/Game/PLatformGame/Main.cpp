#include "Core/core.h"
#include "Core/logger.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Framework/Framework.h"
#include "Physics/PhysicsSystem.h"
#include "PlatformGame.h"
#include <functional>
#include <iostream>
#include <chrono>
#include <vector>
#include <thread>
#include <memory>

using namespace std;





int main(int argc, char* argv[])
{




	INFO_LOG("Initialize Engine...");

	hop::MemoryTracker::Initialize();

	hop::seedRandom((unsigned int)time(nullptr));
	hop::setFilePath("Assets/Platform");


	hop::g_renderer.Initialize();
	hop::g_renderer.CreateWindow("CSC196", 960, 544);

	hop::g_inputSystem.Initialize();
	hop::g_audioSystem.Initialize();
	hop::PhysicsSystem::instance().Initialize();

	unique_ptr<PlatformGame> game = make_unique<PlatformGame>();
	game->Initialize();





	//Main game loop
	bool quit = false;

	while (!quit)
	{

		hop::g_time.tick();
		hop::g_inputSystem.Update();
		hop::g_audioSystem.Update();
		if (hop::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}
		hop::g_particleSystem.Update(hop::g_time.GetDeltaTime());

		hop::PhysicsSystem::instance().Update(hop::g_time.GetDeltaTime());




		game->update(hop::g_time.GetDeltaTime());
		hop::g_renderer.SetColor(0, 0, 0, 255);
		hop::g_renderer.BeginFrame();


		game->draw(hop::g_renderer);
		hop::g_particleSystem.Draw(hop::g_renderer);
		hop::g_renderer.EndFrame();

	}

	//scene.RemoveAll();
	hop::MemoryTracker::DisplayInfo();
	return 0;
}
