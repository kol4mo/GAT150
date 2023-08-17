#pragma once
#include "Factory.h"
#include "Core/Json.h"
#include <string>

#define ClASS_DECLERATION(classname) \
	virtual const char* GetClassName() { return #classname; } \
	virtual void Read(const rapidjson::Value& vlaue); \
	class Register \
	{ \
	public: \
		Register() \
		{ \
			Factory::instance().Register<classname>(#classname); \
		} \
	};

#define CLASS_DEFINITION(classname) \
	classname::Register register_class;

namespace hop {
	class Object
	{
	public:
		Object() = default;
		Object(const std::string& name) : name{ name } {};

		virtual ~Object() { OnDestroy(); }

		ClASS_DECLERATION(Object)

		virtual bool Initialize() { return true; }
		virtual void OnDestroy() {}

	protected:
		std::string name;
	};
}