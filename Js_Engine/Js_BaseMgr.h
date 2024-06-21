#pragma once
#include "std.h"
#include <tchar.h>

namespace Js
{

	template <typename T>
	class Singleton
	{
	public:
		static T& Instance()
		{
			static T mgr;
			return mgr;
		}
	};

	class Resource
	{
	public:
		std::wstring m_csName = L"none";
	public:
		virtual void Set(ComPtr<ID3D11Device> _device) {}
		virtual void Release() {}
		virtual bool Load(const std::wstring& _fileName) = 0;
	};

	template <typename T, typename S>
	class BaseManager : public Singleton<S>
	{
	public:
		void Set(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context)
		{
			m_Device = _device;
			m_Context = _context;
		}
		std::shared_ptr<T> GetPtr(const std::wstring _name)
		{
			auto iter = m_List.find(_name);
			if (iter != m_List.end())
				return (*iter).second;

			return nullptr;
		}
		
		virtual std::shared_ptr<T> Load(const std::wstring& _fileName)
		{
			// 파일명+확장자 검출
			std::wstring name = splitpath(_fileName, L"");

			// 중복 검증
			auto findData = GetPtr(name);
			if (findData != nullptr)
				return findData;

			return CreateObject(_fileName, name);
		}

		virtual std::shared_ptr<T>  CreateObject(std::wstring _path, std::wstring _name)
		{
			std::shared_ptr<T> newData = std::make_shared<T>();
			newData->Set(m_Device);
			newData->m_csName = _name;
			if (newData->Load(_path) == false)
			{
				newData.reset();
				return nullptr;
			}
			m_List.insert(std::make_pair(newData->m_csName, newData));
			return newData;
		}

		std::wstring splitpath(std::wstring _path, std::wstring _fileName)
		{
			wchar_t  szDrive[MAX_PATH] = { 0, };
			wchar_t  szDir[MAX_PATH] = { 0, };
			wchar_t  szFileName[MAX_PATH] = { 0, };
			wchar_t  szFileExt[MAX_PATH] = { 0, };
			//#include <tchar.h>
			_tsplitpath_s(_path.c_str(), szDrive, szDir, szFileName, szFileExt);
			std::wstring name = szFileName;
			name += szFileExt;
			if (_fileName.empty() == false)
			{
				name += _fileName;
			}
			return name;
		}

		void Release()
		{
			for (auto& data : m_List)
			{
				auto deleteData = data.second;
				deleteData->Release();
			}
			m_List.clear();
		}

	public:
		BaseManager() {}
		virtual ~BaseManager() {}


	protected:
		ComPtr<ID3D11Device>			m_Device;
		ComPtr<ID3D11DeviceContext>		m_Context;
		std::wstring					m_csName = L"none";
		std::map<std::wstring, std::shared_ptr<T>> m_List;
	};
}
