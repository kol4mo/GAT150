#include "Core/core.h"
#include "Core/logger.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Enemy.h"
#include "Audio/AudioSystem.h"
#include "Player.h"	
#include "Framework/Framework.h"
#include "Physics/PhysicsSystem.h"
#include "FunGame.h"
#include <functional>
#include <iostream>
#include <chrono>
#include <vector>
#include <thread>
#include <memory>

using namespace std;

class Star
{
public:
	Star(const hop::Vexctor2 pos, const hop::Vexctor2 vel) :
		m_pos{ pos },
		m_vel{ vel }
	{}

	void update(float width, float height)
	{
		m_pos += m_vel * hop::g_time.GetDeltaTime();
		if (m_pos.x > width) m_pos.x = 0;
		if (m_pos.y > height) m_pos.y = 0;
		if (m_pos.x < 0) m_pos.x = width;
		if (m_pos.y < 0) m_pos.y = height;
	}

	void Draw(hop::Renderer& renderer)
	{
		renderer.DrawPoint(m_pos.x, m_pos.y);
	}
public :
	hop::vec2 m_pos;
	hop::vec2 m_vel;
};

//void zero(int v) {
//	v = 0;
//}
//
//void zero(int* v) {
//	*v = 0;
//}
//
//void zero_ref(int& v) {
//	v = 0;
//}
//

void print(int i) {
	cout << i << endl;
}

class A {
public:
	int add(int i1, int i2) {
		return i1 + i2;
	}
};

union Data {

};

int main(int argc, char* argv[])
{
	void (*func_ptr)(int) = &print;
	func_ptr(5);

	int (*op_ptr)(int, int);

	std::function<int(int, int)> op;

	A a;
	op = std::bind(&A::add, &a, std::placeholders::_1, std::placeholders::_2);

	//int i = 5;
	//zero(i);
	//cout << i << endl;
	//zero(&i);
	//cout << i << endl;
	//i = 5;
	//zero_ref(i);
	//cout << i << endl;


	INFO_LOG("Initialize Engine...");

	hop::MemoryTracker::Initialize();

	hop::seedRandom((unsigned int)time(nullptr));
	hop::setFilePath("Assets");

	rapidjson::Document document;
	hop::Json::Load("json.txt", document);
	int i1;
	hop::Json::Read(document, "integer1", i1);
	std::cout << i1 << std::endl;
	int i2;
	hop::Json::Read(document, "integer2", i2);
	std::cout << i2 << std::endl;
	std::string str;
	hop::Json::Read(document, "string", str);
	std::cout << str << std::endl;
	bool b;
	hop::Json::Read(document, "boolean", b);
		std::cout << b << std::endl;
	float f;
	hop::Json::Read(document, "float", f);
		std::cout << f << std::endl;
	hop::vec2 v2;
	hop::Json::Read(document, "vector2", v2, true);
	std::cout << v2 << std::endl;

	hop::g_renderer.Initialize();
	hop::g_renderer.CreateWindow("CSC196", 1080, 540);

	hop::g_inputSystem.Initialize();
	hop::g_audioSystem.Initialize();
	hop::PhysicsSystem::instance().Initialize();

	unique_ptr<FunGame> game = make_unique<FunGame>();
	game->Initialize();

	hop::res_t<hop::Texture> texture = GET_RESOURCE(hop::Texture, "Sans_undertale.jpg", hop::g_renderer);




	//Main game loop
	bool quit = false;

	while (!quit)
	{

		hop::g_time.tick();
		hop::g_inputSystem.Update();
		hop::g_audioSystem.Update();
		hop::g_particleSystem.Update(hop::g_time.GetDeltaTime());
		if (hop::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}



		//end = false;
		//while (!end) {
		//	if (hop::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		//	{
		//		quit = true;
		//		end = true;
		//	}
		game->update(hop::g_time.GetDeltaTime());
		hop::g_renderer.SetColor(0, 0, 0, 255);
		hop::g_renderer.BeginFrame();

			//text->Draw(hop::g_renderer, 400, 300);
		game->draw(hop::g_renderer);
		//hop::g_renderer.DrawTexture(texture.get(), 200.0f, 200.0f, 0.0f);
		hop::g_renderer.EndFrame();
		//	if (scene.getLength() == 1) {
		//		end = true;
		//	}
		//}
		//x++;

	}

	//scene.RemoveAll();
	hop::MemoryTracker::DisplayInfo();
	return 0;
}
	//vector<Star> stars;
	//int r;
	//int g;
	//int b;
	//int d;
	//int o;
	//for (int i = 0; i < 10000; i++) {
	//	hop::Vexctor2 pos(hop::random(hop::g_renderer.GetWidth()), hop::random(hop::g_renderer.GetHeight()));
	//	hop::Vexctor2 vel(0.0f, hop::randomf(12, 15));

	//	stars.push_back(Star(pos, vel));
	//}
		/*hop::vec2 direction;
		if (inputSystem.GetKeyDown(SDL_SCANCODE_W)) direction.y = -1;
		if (inputSystem.GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
		if (inputSystem.GetKeyDown(SDL_SCANCODE_S)) direction.y = 1;
		if (inputSystem.GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;

		transform.position += direction * speed * hop::g_time.GetDeltaTime();*/
		//this_thread::sleep_for(chrono::milliseconds(100));
		//draw
		//for (int i = 0; i < 1000; i++) {
		//	hop::Vexctor2 pos(hop::randomf(renderer.GetWidth()), hop::randomf(renderer.GetHeight()));
		//	renderer.SetColor(hop::random(255), hop::random(255), hop::random(255), hop::random(255));
		//	renderer.DrawPoint(pos.x, pos.y);
		//	//renderer.DrawLine(hop::random(renderer.GetWidth()), hop::random(renderer.GetHeight()), hop::random(renderer.GetWidth()), hop::random(renderer.GetHeight()));
		//}
		/*for (auto& star : stars) {

			star.update(hop::g_renderer.GetWidth(), hop::g_renderer.GetHeight());
			d = sqrt(pow(abs(star.m_pos.x - player.m_transform.position.x), 2) + pow(abs(star.m_pos.y - player.m_transform.position.y), 2));
			r = hop::random(255);
			b = hop::random(255);
			g= hop::random(255);
			
			if (r - d < 0) {
				r = 0;
			}
			else {
				r - d;
			}
			if (b - d < 0) {
				b= 0;
			}
			else {
				b- d;
			}
			if (g - d < 0) {
				g = 0;
			}
			else {
				g - d;
			}
			if (d < 0) {
				o = 0;
			}
			else {
				o = (100 - d) * 2.55f;
			}

			hop::g_renderer.SetColor(o,o,o, 255);
			star.Draw(hop::g_renderer);
		}*/