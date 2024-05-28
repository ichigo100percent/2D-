#pragma once

namespace Js
{
	class WriterFont : public BaseCore
	{
	public:
		WriterFont();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render() override;
		virtual void Release() override;

		void ResetDevice(IDXGISurface* dxgiSurface);
		void DrawText(std::wstring msg, POINT pos);

	private:
		//Microsoft::WRL::ComPtr<ID2D1Factory> m_pd2dFactory = nullptr;
		//Microsoft::WRL::ComPtr<ID2D1RenderTarget> m_pd2dRT = nullptr;
		//Microsoft::WRL::ComPtr<IDWriteFactory> m_pWriteFactory = nullptr;
		//Microsoft::WRL::ComPtr<IDWriteTextFormat> m_pWriteTF30 = nullptr;
		//Microsoft::WRL::ComPtr<IDWriteTextFormat> m_pWriteTF50 = nullptr;
		//Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> m_pDefaultColor = nullptr;
		ID2D1Factory* m_pd2dFactory = nullptr;
		ID2D1RenderTarget* m_pd2dRT = nullptr;
		IDWriteFactory* m_pWriteFactory = nullptr;
		IDWriteTextFormat* m_pWriteTF30 = nullptr;
		IDWriteTextFormat* m_pWriteTF50 = nullptr;
		ID2D1SolidColorBrush* m_pDefaultColor = nullptr;
	};
}