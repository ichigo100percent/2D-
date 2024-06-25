#pragma once
#include "Js_Component.h"

namespace Js
{
	class MeshRenderer : public Component
	{
	public:
		MeshRenderer();
		virtual ~MeshRenderer();

		virtual void Init() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
		virtual void Release() override;

	private:

	};
}
