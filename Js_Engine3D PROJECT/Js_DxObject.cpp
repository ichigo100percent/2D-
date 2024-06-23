#include "Js_DxObject.h"
#include "Js_Input.h"
#include "Js_Time.h"

namespace Js
{
	DxObject::DxObject(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context, const std::wstring& _name) :
		Entity(_name),
		m_Device(_device), 
		m_Context(_context)
	{
	}
	DxObject::~DxObject()
	{
	}

	void DxObject::Init(const std::wstring& _texName)
	{
		m_Geometry = std::make_shared<Geometry<VertexTextureData>>();
		GeometryHelper::CreateRectangle(m_Geometry);

		m_VertexBuffer = std::make_shared<VertexBuffer>(m_Device);
		m_VertexBuffer->Create(m_Geometry->GetVertices());

		m_IndexBuffer = std::make_shared<IndexBuffer>(m_Device);
		m_IndexBuffer->Create(m_Geometry->GetIndices());

		m_VertexShader = std::make_shared<VertexShader>(m_Device);
		m_VertexShader->Create(L"Default.hlsl", "VS", "vs_5_0");

		m_InputLayout = std::make_shared<InputLayout>(m_Device);
		m_InputLayout->Create(VertexTextureData::descs, m_VertexShader->GetBlob());

		m_PixelShader = std::make_shared<PixelShader>(m_Device);
		m_PixelShader->Create(L"Default.hlsl", "PS", "ps_5_0");

		m_ConstantBuffer = std::make_shared<ConstantBuffer<TransformData>>(m_Device, m_Context);
		m_ConstantBuffer->Create();

		m_RasterizerState = std::make_shared<RasterizerState>(m_Device);
		m_RasterizerState->Create();

		m_ShaderResourceView = std::make_shared<Texture>(m_Device);
		m_ShaderResourceView->Create(_texName);

		m_SamplerState = std::make_shared<SamplerState>(m_Device);
		m_SamplerState->Create();
		
		m_BlendState = std::make_shared<BlendState>(m_Device);
		m_BlendState->Create();
	}

	void DxObject::Render(std::shared_ptr<Pipeline> _pipeline)
	{
		PipelineInfo info;
		info.inputLayout = m_InputLayout;
		info.vertexShader = m_VertexShader;
		info.pixelShader = m_PixelShader;
		info.rasterizerState = m_RasterizerState;
		info.blendState = m_BlendState;
		_pipeline->UpdatePipeline(info);

		_pipeline->SetVertexBuffer(m_VertexBuffer);
		_pipeline->SetIndexBuffer(m_IndexBuffer);
		_pipeline->SetConstantBuffer(0, SS_VertexShader, m_ConstantBuffer);
		_pipeline->SetTexture(0, SS_PixelShader, m_ShaderResourceView);
		_pipeline->SetSamplerState(0, SS_PixelShader, m_SamplerState);
		_pipeline->DrawIndexed(m_Geometry->GetIndexCount(), 0, 0);
	}
	void DxObject::Update()
	{
		float speed = 0.5 * Time::DeltaTime();
		auto position = m_Transform->GetPosition();
		// Scale Rotation Translation
		if (Input::KeyCheck('W') == KeyState::KEY_HOLD)
		{
			//m_LocalPosition.y += speed;
			position.y += speed;
		}
		if (Input::KeyCheck('S') == KeyState::KEY_HOLD)
		{
			//m_LocalPosition.y -= speed;
			position.y -= speed;
		}
		if (Input::KeyCheck('A') == KeyState::KEY_HOLD)
		{
			//m_LocalPosition.x -= speed;
			position.x -= speed;
		}
		if (Input::KeyCheck('D') == KeyState::KEY_HOLD)
		{
			//m_LocalPosition.x += speed;
			position.x += speed;
		}
		m_Transform->SetPosition(position);
		//Matrix matScale = Matrix::CreateScale(m_LocalScale);
		//Matrix matRotation = Matrix::CreateRotationX(m_LocalRotation.x);
		//matRotation *= Matrix::CreateRotationY(m_LocalRotation.y);
		//matRotation *= Matrix::CreateRotationZ(m_LocalRotation.z);
		//Matrix matTranslation = Matrix::CreateTranslation(m_LocalPosition);

		//Matrix matWorld = matScale * matRotation * matTranslation; // SRT
		//m_TransformData.matWorld = matWorld;

		//// AABB 업데이트
		//m_Rt.left = m_LocalPosition.x - m_LocalScale.x;
		//m_Rt.right = m_LocalPosition.x + m_LocalScale.x;
		//m_Rt.top = m_LocalPosition.y + m_LocalScale.y;
		//m_Rt.bottom = m_LocalPosition.y - m_LocalScale.y;
		m_TransformData.matWorld = m_Transform->GetWorldMatrix();
		m_ConstantBuffer->CopyData(m_TransformData);


		//std::string pos; 
		//pos += "position : " + std::to_string(m_LocalPosition.x) + " " + std::to_string(m_LocalPosition.y) + '\n';
		//OutputDebugStringA(pos.c_str());

		//std::string rt;
		//rt += std::to_string(m_Rt.left) + " " + std::to_string(m_Rt.right) + '\n';
		//OutputDebugStringA(rt.c_str());
	}
	void DxObject::Release()
	{
	}

}