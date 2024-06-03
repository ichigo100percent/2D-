#pragma once
#include <string>


namespace Js
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(const std::wstring& _name) : m_Name(_name) {}

		void SetName(const std::wstring& _name) { m_Name = _name; }
		std::wstring GetName() const { return m_Name; }

	private:
		std::wstring m_Name;
	};

}