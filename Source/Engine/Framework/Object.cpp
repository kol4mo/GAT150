#include "Object.h"

namespace hop {
	void Object::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, name);
	}
}