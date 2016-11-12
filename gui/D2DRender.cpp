#include "stdafx.h"
#include "D2DRender.h"
#include "guiDoc.h"
#include "guiView.h"
#include <d2d1.h>
#include <d3d11_1.h>


D2DRender::D2DRender(CguiView * view)
{
	this->view = view;

	// init d2d 

	HRESULT hr = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED,
		&pD2DFactory
	);
	if (hr != S_OK)throw hr;


	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(pDWriteFactory),
		reinterpret_cast<IUnknown **>(&pDWriteFactory)
	);
	if (hr != S_OK)throw hr;

	hr = pDWriteFactory->CreateTextFormat(
		L"Verdana",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		12,
		L"", //locale
		&pTextFormat
	);
	if (hr != S_OK)throw hr;

	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&m_pIWICFactory)
	);
	if (hr != S_OK)throw hr;

	lastFrame = std::chrono::steady_clock::now();
}

D2DRender::~D2DRender()
{
	SafeRelease(&pD2DFactory);
	SafeRelease(&pDWriteFactory);
	SafeRelease(&pTextFormat);
}

void D2DRender::flush()
{
	mu.lock();
	cached = false;
	release();
	mu.unlock();
}

bool D2DRender::isBusy()
{
	return busy;
}

HRESULT D2DRender::renderScence()
{
	HRESULT hr = 0;
	RECT rc;
	CString fpsStr;

	ID2D1HwndRenderTarget* pRT = NULL;
	ID2D1SolidColorBrush* pGrayBrush = NULL;
	ID2D1SolidColorBrush* pGreenBrush = NULL;
	ID2D1SolidColorBrush* pRedBrush = NULL;
	ID2D1SolidColorBrush* pWhiteBrush = NULL;
	ID2D1StrokeStyle * style = NULL;
	ID2D1Bitmap * bmp = NULL;

	std::chrono::steady_clock::time_point now;

	view->GetClientRect(&rc);

	//regular size
	if (rc.right % 4)
	{
		rc.right = (rc.right / 4 + 1) * 4;
	}
	if (rc.bottom % 4)
	{
		rc.bottom = (rc.bottom / 4 + 1) * 4;
	}

	mu2.lock();

	if (rc != cachedRC)
	{
		mu.lock();
		cachedRC = rc;
		cached = false;
		release();
		mu.unlock();
	}

	CguiDoc* pDoc = view->GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		goto error;

	if (!pDoc->inited)
		goto error;

	hr = pD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			view->GetSafeHwnd(),
			D2D1::SizeU(
				rc.right - rc.left,
				rc.bottom - rc.top)
		),
		&pRT
	);
	if (hr)goto error;
	
	if (!cached)
	{
		release();

		int height = rc.right - rc.left;
		int width = rc.bottom - rc.top;

		hr = m_pIWICFactory->CreateBitmap(
			height,
			width,
			GUID_WICPixelFormat32bppBGR,
			WICBitmapCacheOnDemand,
			&pCachedBmp
		);
		if (hr)goto error;

		std::thread t(std::bind(&D2DRender::renderCache,this,pDoc));
		t.detach();
		mu2.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
		mu2.lock();
	}

	
	hr = pRT->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Gray),
		&pGrayBrush
	);
	if (hr)goto error;

	
	hr = pD2DFactory->CreateStrokeStyle(
		D2D1::StrokeStyleProperties(
			D2D1_CAP_STYLE_ROUND,
			D2D1_CAP_STYLE_ROUND,
			D2D1_CAP_STYLE_ROUND
		),
		0, 0, &style
	);
	if (hr)goto error;

	
	hr = pRT->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Red),
		&pRedBrush
	);
	if (hr)goto error;

	
	hr = pRT->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::White),
		&pWhiteBrush
	);
	if (hr)goto error;

	
	hr = pRT->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Green),
		&pGreenBrush
	);
	if (hr)goto error;

	if (cached && !busy)
	{
		hr = pRT->CreateBitmapFromWicBitmap(
			pCachedBmp,
			nullptr,
			&bmp
		);
		if (hr)goto error;
	}
	else if (pCachedBmpBack != nullptr)
	{
		hr = pRT->CreateBitmapFromWicBitmap(
			pCachedBmpBack,
			nullptr,
			&bmp
		);
		if (hr)goto error;
	}
	

	ASSERT(pDoc != nullptr);
	ASSERT(pDoc->cameras.find(pDoc->currentCamera) != pDoc->cameras.end());
	GraphicCamera * camera = pDoc->cameras[pDoc->currentCamera].get();

	pRT->BeginDraw();
	pRT->Clear();
	if (bmp!=nullptr)
	{
		pRT->DrawBitmap(bmp);
	}
		
	// begin draw

	if (view->selectMode == GUI_SELECT_MODE_OBJECT)
	{
		for (auto & guid : view->selectedGraphic)
		{
			ASSERT(pDoc->graphics.find(guid) != pDoc->graphics.end());
			ASSERT(pDoc->graphics[guid].get() != nullptr);

			Graphic * g = pDoc->graphics[guid].get();
			renderGraphicFast(g, camera, pRT, pWhiteBrush, style);
		}

	}
	else if (view->selectMode == GUI_SELECT_MODE_VERTEX)
	{
		for (auto & pt : view->selectedPoint)
		{

		}
	}

	if (view->creating)
		renderGraphicFast(view->creating, camera, pRT, pWhiteBrush, style);


	// end draw
	now = std::chrono::steady_clock::now();
	int fps = (int)(1000000.0 / (std::chrono::duration_cast<std::chrono::microseconds>(now - lastFrame).count()));
	lastFrame = now;
	fpsStr.Format(L"FPS:%d ", fps);
	pRT->DrawTextW(fpsStr, fpsStr.GetLength(), pTextFormat, D2D1::RectF(0, 0, 1000, 30), pGreenBrush);
	hr = pRT->EndDraw();
	if (hr) goto error;

error:
	mu2.unlock();
	SafeRelease(&pRT);
	SafeRelease(&pGrayBrush);
	SafeRelease(&pGreenBrush);
	SafeRelease(&pRedBrush);
	SafeRelease(&pWhiteBrush);
	SafeRelease(&style);
	SafeRelease(&bmp);

	return hr;
}

inline void D2DRender::renderGraphicFast(Graphic* g, GraphicCamera * camera, ID2D1RenderTarget* pRT, ID2D1SolidColorBrush * brush, ID2D1StrokeStyle * style)
{
	switch (g->type)
	{
	case GRA_POLYGON:
	{
		// try to render polygon here
		ASSERT(g->graphicPolygon.get() != nullptr);
		auto polygon = g->graphicPolygon.get();
		auto ptList = polygon->atFrame(view->frame);
		if (ptList.size() < 2)
			return;
		auto lastPoint = ptList.begin();
		for (auto i = ptList.begin() + 1; i < ptList.end(); ++i)
		{
			auto pt1 = camera->toCameraView(lastPoint->x, lastPoint->y);
			auto pt2 = camera->toCameraView(i->x, i->y);
			brush->SetColor(D2D1::ColorF(lastPoint->color));

			pRT->DrawLine(pt1, pt2, brush, (i->width + lastPoint->width) / 2, style);

			lastPoint = i;
		}
	}
	break;
	case GRA_CIRCLE:
	{
		// try to render circle here
		ASSERT(g->graphicCircle.get() != nullptr);
		auto circle = g->graphicCircle.get();
		auto pt = camera->toCameraView(circle->x.atFrame(view->frame), circle->y.atFrame(view->frame));
		auto r = camera->scale * circle->r.atFrame(view->frame);
		D2D1_ELLIPSE eclipse;
		eclipse.point = pt;
		eclipse.radiusX = r;
		eclipse.radiusY = r;
		brush->SetColor(D2D1::ColorF(circle->color.atFrame(view->frame)));
		pRT->DrawEllipse(eclipse, brush, circle->width.atFrame(view->frame), style);
	}
	break;
	case GRA_BEZIER:
	{
		// try to render bezier here
		auto ptList = g->graphicBezier->atFrame(view->frame);
		if (ptList.size() < 2)
			return;
		auto lastPoint = ptList.begin();
		for (auto i = ptList.begin() + 1; i < ptList.end(); ++i)
		{
			auto pt1 = camera->toCameraView(lastPoint->x, lastPoint->y);
			auto pt2 = camera->toCameraView(i->x, i->y);
			brush->SetColor(D2D1::ColorF(lastPoint->color));
			pRT->DrawLine(pt1, pt2, brush, (i->width + lastPoint->width) / 2, style);

			lastPoint = i;
		}
	}
	break;
	case GRA_NONE:
		break;
	default:
		throw "unkown type";
	}
}

void D2DRender::renderCache(CguiDoc* pDoc)
{
	mu.lock();
	mu2.lock();
	busy = true;
	mu2.unlock();
	HRESULT hr;

	ID2D1RenderTarget * pCRT = nullptr;
	ID2D1StrokeStyle * style = NULL;
	ID2D1SolidColorBrush * brush = NULL;

	ASSERT(pDoc != nullptr);
	ASSERT(pDoc->cameras.find(pDoc->currentCamera) != pDoc->cameras.end());
	GraphicCamera * camera = pDoc->cameras[pDoc->currentCamera].get();

	hr = pD2DFactory->CreateWicBitmapRenderTarget(
		pCachedBmp,
		D2D1::RenderTargetProperties(
			D2D1_RENDER_TARGET_TYPE_DEFAULT,
			D2D1::PixelFormat(
				DXGI_FORMAT_B8G8R8A8_UNORM,
				D2D1_ALPHA_MODE_IGNORE
			),
			0,
			0,
			D2D1_RENDER_TARGET_USAGE_NONE,
			D2D1_FEATURE_LEVEL_DEFAULT
		),
		&pCRT
	);
	if (hr)goto error;

	hr = pCRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &brush);
	if (hr)goto error;

	hr = pD2DFactory->CreateStrokeStyle(
		D2D1::StrokeStyleProperties(
			D2D1_CAP_STYLE_ROUND,
			D2D1_CAP_STYLE_ROUND,
			D2D1_CAP_STYLE_ROUND
		),
		0, 0, &style
	);
	if (hr)goto error;

	pCRT->BeginDraw();
	pCRT->Clear();

	for (auto & guid : pDoc->layer)
	{
		if (view->selectedGraphic.find(guid) != view->selectedGraphic.end())
			continue;

		Graphic * g = pDoc->graphics[guid].get();
		renderGraphicFast(g, camera, pCRT, brush, style);
	}
	

	hr = pCRT->EndDraw();
	if (hr)goto error;

	cached = true;

error:
	ASSERT(hr == S_OK);
	SafeRelease(&style);
	SafeRelease(&brush);
	SafeRelease(&pCRT);

	mu2.lock();
	busy = false;
	mu2.unlock();
	mu.unlock();
}

void D2DRender::release()
{
	if (pCachedBmp)
	{
		SafeRelease(&pCachedBmpBack);
		pCachedBmpBack = pCachedBmp;
		pCachedBmp = nullptr;
	}
	else if(!pCachedBmpBack)
	{
		pCachedBmpBack = pCachedBmp;
		pCachedBmp = nullptr;
	}
}
