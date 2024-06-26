#include "Js_Resource.h"

namespace Js
{
	BaseResource::BaseResource(ResourceType _type, const std::wstring& _name)
		: Entity(_name)
		, m_Type(_type)
	{
	}
	BaseResource::~BaseResource()
	{
	}
}