#pragma once

class CguiDoc;
class CguiView;
class Graphic;
class GraphicCamera;
#include <chrono>

class D2DRender
{
	CguiView * view = nullptr;

	bool cached = false;
	RECT cachedRC;
	
	ID2D1Factory* pD2DFactory = NULL;
	IDWriteTextFormat * pTextFormat = NULL;
	IDWriteFactory * pDWriteFactory = NULL;
	ID2D1Bitmap * pCachedBmp = NULL;

	std::chrono::steady_clock::time_point lastFrame;

	inline void D2DRender::renderGraphicFast(Graphic* g, GraphicCamera * camera, ID2D1RenderTarget* pRT, ID2D1SolidColorBrush * brush, ID2D1StrokeStyle * style);
	HRESULT renderCache(ID2D1BitmapRenderTarget * pCRT);
public:
	D2DRender(CguiView * view);
	~D2DRender();
	void flush();
	HRESULT renderScence();
};