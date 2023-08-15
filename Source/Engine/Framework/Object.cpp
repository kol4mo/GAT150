#include "Object.h"

namespace hop {
	bool Object::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, name)
		return true;
	}
}