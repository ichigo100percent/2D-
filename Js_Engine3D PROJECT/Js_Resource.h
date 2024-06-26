#pragma once
#include "std.h"

namespace Js
{
	enum class ResourceType
	{
		None = -1,
		Mesh,
		Shader,
		Texture,
		Material,
		Animation,
		Sound,

		End
	};

	enum
	{
		RESOURCE_TYPE_COUNT = static_cast<UINT>(ResourceType::End)
	};

	class BaseResource : public std::enable_shared_from_this<BaseResource>, public Entity
	{
	public:
		BaseResource(ResourceType _type, const std::wstring& _name = {});
		virtual ~BaseResource();

		ResourceType GetType() { return m_Type; }

	protected:
		virtual void Load(const std::wstring& _path) {}
		virtual void Save(const std::wstring& _path) {}

	protected:
		ResourceType m_Type = ResourceType::None;
		std::wstring m_Path;
	};
}
