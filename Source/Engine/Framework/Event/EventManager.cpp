#include "EventManager.h"
#include "Core/logger.h"

namespace hop {
	void EventManager::Update(float dt)
	{
	}
	void EventManager::subscribe(Event::id_t id, IEventListener* listener, eventFunction function)
	{
		EventDispacther dispatcher;

		dispatcher.listener = listener;
		dispatcher.function = function;

		INFO_LOG("Event Subsribec:" << id);

		m_dispacthers[id].push_back(dispatcher);
	}
	void EventManager::Unsubscribe(Event::id_t id, IEventListener* listener)
	{
	}
	void EventManager::DispatchEvent(Event::id_t id, Event::data_t data, void* sender, float time)
	{
		Event event{ id, data };

		if (m_dispacthers.find(id) != m_dispacthers.end()) {
			auto& dispatchers = m_dispacthers[id];

			for (auto& dispatcher : dispatchers) {
				dispatcher.function(event);
			}
		}

	}
}