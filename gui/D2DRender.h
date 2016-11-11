#pragma once

class CguiDoc;
class CguiView;
class Graphic;
class GraphicCamera;
#include <chrono>
#include <mutex>

class D2DRender
{
	CguiView * view = nullptr;

	bool cached = false;
	bool busy = false;
	RECT cachedRC;
	std::mutex mu;
	std::mutex mu2;
	
	ID2D1Factory* pD2DFactory = NULL;
	IDWriteTextFormat * pTextFormat = NULL;
	IDWriteFactory * pDWriteFactory = NULL;
	IWICBitmap * pCachedBmp = NULL;
	IWICImagingFactory * m_pIWICFactory;

	std::chrono::steady_clock::time_point lastFrame;

	inline void D2DRender::renderGraphicFast(Graphic* g, GraphicCamera * camera, ID2D1RenderTarget* pRT, ID2D1SolidColorBrush * brush, ID2D1StrokeStyle * style);
	void renderCache(CguiDoc* pDoc);
public:
	D2DRender(CguiView * view);
	~D2DRender();
	void flush();
	bool isBusy();
	HRESULT renderScence();
};