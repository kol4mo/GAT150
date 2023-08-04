#pragma once
#include "Resource.h"
#include <map>
#include <memory>#
#include <string>

namespace hop
{
	class ResourceManager
	{
	public:
		template<typename T, typename ...TArgs>
		std::shared_ptr<T> Get(const std::string& filename, TArgs ... args);

	private:
		std::map<std::string, std::shared_ptr<Resource>> m_resource;
	};
	template<typename T, typename ...TArgs>
	inline std::shared_ptr<T> ResourceManager::Get(const std::string& filename, TArgs ...args)
	{
		if (m_resource.find(filename) != m_resource.end())
		{
			return std::dynamic_pointer_cast<T>(m_resource[filename]);
		}

		std::shared_ptr<T> resource = std::make_shared<T>();
		resource->Create(filename, args...);
		m_resource[filename] = resource;

		return resource;
	}

	extern ResourceManager g_resources;
}