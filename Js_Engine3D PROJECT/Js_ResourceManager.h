#pragma once
#include "Js_Resource.h"
#include "Js_Texture.h"


namespace Js
{
	class ResourceManager
	{
	public:
		ResourceManager(ComPtr<ID3D11Device> _device);

		void Init();

		template <typename T>
		ResourceType GetResourceType()
		{
			//if (std::is_same_v<T, Mesh>)
			//	return ResourceType::Mesh;
			//if (std::is_same_v<T, Shader>)
			//	return ResourceType::Shader;
			if (std::is_same_v<T, Texture>)
				return ResourceType::Texture;

			assert(false);
			return ResourceType::None;
		}

		template <typename T>
		std::shared_ptr<T> Load(const std::wstring& _key, const std::wstring& _path)
		{
			auto type = GetResourceType<T>();
			resourceList& list = m_Resources[static_cast<UINT>(type)];

			auto find = list.find(_key);
			if (find != list.end())
				return static_cast<T>(find->second);

			std::shared_ptr<T> object = std::make_shared<T>();
			object->Load(_path);
			list[_key] = object;

			return object;
		}

		template <typename T>
		bool Add(const std::wstring& _key, std::shared_ptr<T> _object)
		{
			auto type = GetResourceType<T>();
			resourceList& list = m_Resources[static_cast<UINT>(type)];

			auto find = list.find(_key);
			if (find != list.end())
				return false;

			list[_key] = _object;
			return true;
		}

		template <typename T>
		std::shared_ptr<T> Get(const std::wstring& _key)
		{
			auto type = GetResourceType<T>();
			resourceList& list = m_Resources[static_cast<UINT>(type)];

			auto find = list.find(_key);
			if (find != list.end())
				return std::static_pointer_cast<T>(find->second);
			
			return nullptr;
		}

	private:
		void createDefaultMesh();
		void createDefaultShader();
		void createDefaultTexture();
		void createDefaultMaterial();
		void createDefaultAnimation();
		void createDefaultSound();

	private:
		ComPtr<ID3D11Device> m_Device;
		using resourceList = std::map<std::wstring, std::shared_ptr<BaseResource>>;
		std::array<resourceList, RESOURCE_TYPE_COUNT> m_Resources;
	};
}
