#pragma once
#include "Js_Resource.h"
#include "Js_Mesh.h"
#include "Js_Shader.h"
#include "Js_Texture.h"
#include "Js_Material.h"
#include "Js_Animation.h"

namespace Js
{

	class Sound {};

	class ResourceManager
	{
	public:
		ResourceManager(ComPtr<ID3D11Device> _device);

		void Init();

		template <typename T>
		static ResourceType GetResourceType()
		{
			if (std::is_same_v<T, Mesh>)
				return ResourceType::Mesh;
			if (std::is_same_v<T, Shader>)
				return ResourceType::Shader;
			if (std::is_same_v<T, Texture>)
				return ResourceType::Texture;
			if (std::is_same_v<T, Material>)
				return ResourceType::Material;
			if (std::is_same_v<T, Animation>)
				return ResourceType::Animation;
			if (std::is_same_v<T, Sound>)
				return ResourceType::Sound;

			assert(false);
			return ResourceType::None;
		}

		template <typename T>
		static std::shared_ptr<T> Load(const std::wstring& _key, const std::wstring& _path)
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
		static bool Add(const std::wstring& _key, std::shared_ptr<T> _object)
		{
			auto type = GetResourceType<T>();
			auto& list = m_Resources[static_cast<UINT>(type)];

			auto find = list.find(_key);
			if (find != list.end())
				return false;

			list[_key] = _object;
			auto a = m_Resources[static_cast<UINT>(type)];
			return true;
		}

		template <typename T>
		static std::shared_ptr<T> Get(const std::wstring& _key)
		{
			auto type = GetResourceType<T>();
			auto& list = m_Resources[static_cast<UINT>(type)];

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
		static std::array<resourceList, RESOURCE_TYPE_COUNT> m_Resources;
	};
}
