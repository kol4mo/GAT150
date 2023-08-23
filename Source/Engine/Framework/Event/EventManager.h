#pragma once
#include "Event.h"
#include "Framework/Singleton.h"
#include <map>
#include <list>
#include <functional>

#define EVENT_SUBSCRIBE(id, function)	hop::EventManager::instance().subscribe(id, this, std::bind(&function, this, std::placeholders::_1))
#define EVENT_UNSUBSCRIBE(id)			hop::EventManager::instance().Unsubscribe(id, this)

namespace hop {
	class IEventListener {

	};

	class EventManager: public Singleton<EventManager> {
	public:
		using eventFunction = std::function<void(const Event&)>;
	
		struct EventDispacther {
			IEventListener* listener = nullptr;

			eventFunction function;
		};
	public:
		void Update(float dt);
		void subscribe(Event::id_t id, IEventListener* listener, eventFunction function);
		void Unsubscribe(Event::id_t id, IEventListener* listener);

		void DispatchEvent(Event::id_t id, Event::data_t data, void* sender = nullptr, float time = 0);


	private:
		std::map<Event::id_t, std::list<EventDispacther>> m_dispacthers;
	};
}