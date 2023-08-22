#pragma once
#include "Resource.h"
#include "Framework/Singleton.h"
#include <map>
#include <memory>
#include <string>

#define GET_RESOURCE(type, filename, ...) hop::ResourceManager::instance().Get<type>(filename, __VA_ARGS__)

namespace hop
{
	class ResourceManager : public Singleton<ResourceManager>
	{
	public:
		template<typename T, typename ...TArgs>
		res_t<T> Get(const std::string& filename, TArgs ... args);

	private:
		std::map<std::string, res_t<Resource>> m_resource;
	};
	template<typename T, typename ...TArgs>
	inline res_t<T> ResourceManager::Get(const std::string& filename, TArgs ...args)
	{
		if (m_resource.find(filename) != m_resource.end())
		{
			return std::dynamic_pointer_cast<T>(m_resource[filename]);
		}

		res_t<T> resource = std::make_shared<T>();
		resource->Create(filename, args...);
		m_resource[filename] = resource;

		return resource;
	}

}