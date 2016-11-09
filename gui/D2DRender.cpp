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
	cached = false;
}

bool D2DRender::renderScence()
{

	RECT rc;
	view->GetClientRect(&rc);

	CguiDoc* pDoc = view->GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return false;

	if (!pDoc->inited)
		return false;


	ID2D1HwndRenderTarget* pRT = NULL;
	HRESULT hr = pD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			view->GetSafeHwnd(),
			D2D1::SizeU(
				rc.right - rc.left,
				rc.bottom - rc.top)
		),
		&pRT
	);

	ID2D1SolidColorBrush* pGrayBrush = NULL;
	pRT->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Gray),
		&pGrayBrush
	);


	ID2D1StrokeStyle * style = NULL;
	pD2DFactory->CreateStrokeStyle(
		D2D1::StrokeStyleProperties(
			D2D1_CAP_STYLE_ROUND,
			D2D1_CAP_STYLE_ROUND,
			D2D1_CAP_STYLE_ROUND
		),
		0, 0, &style
	);


	ID2D1SolidColorBrush* pRedBrush = NULL;
	pRT->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Red),
		&pRedBrush
	);


	ID2D1SolidColorBrush* pWhiteBrush = NULL;
	pRT->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::White),
		&pWhiteBrush
	);



	ID2D1SolidColorBrush* pGreenBrush = NULL;
	pRT->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Green),
		&pGreenBrush
	);


	ASSERT(pDoc != nullptr);
	ASSERT(pDoc->cameras.find(pDoc->currentCamera) != pDoc->cameras.end());
	GraphicCamera * camera = pDoc->cameras[pDoc->currentCamera].get();

	pRT->BeginDraw();
	pRT->Clear();
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
	std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
	int fps = (int)(1000000.0 / (std::chrono::duration_cast<std::chrono::microseconds>(now - lastFrame).count()));
	lastFrame = now;
	CString fpsStr;
	fpsStr.Format(L"FPS:%d ", fps);
	pRT->DrawTextW(fpsStr, fpsStr.GetLength(), pTextFormat, D2D1::RectF(0, 0, 1000, 30), pGreenBrush);
	hr = pRT->EndDraw();

	SafeRelease(&pRT);
	SafeRelease(&pGrayBrush);
	SafeRelease(&pGreenBrush);
	SafeRelease(&pRedBrush);
	SafeRelease(&pWhiteBrush);
	SafeRelease(&style);


	return true;
}

inline void D2DRender::renderGraphicFast(Graphic* g, GraphicCamera * camera, ID2D1HwndRenderTarget* pRT, ID2D1SolidColorBrush * brush, ID2D1StrokeStyle * style)
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
